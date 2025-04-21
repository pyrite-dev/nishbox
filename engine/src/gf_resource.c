#define GF_EXPOSE_RESOURCE

#include <gf_pre.h>

/* External library */
#include <stb_ds.h>
#include <zlib.h>

/* Interface */
#include <gf_resource.h>

/* Engine */
#include <gf_core.h>
#include <gf_log.h>

/* Standard */
#include <string.h>
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

#define CHUNK 32767

#pragma pack(1)

/**
 * @brief tar header
 * @warning Used internally, never exported
 */
struct tar_header {
	char filename[100];
	char mode[8];
	char uid[8];
	char gid[8];
	char size[12];
	char mtime[12];
	char chksum[8];
	char typeflag[1];
	char linkname[100];
	char ustar[6];
	char ustarv[2];
	char username[32];
	char grpname[32];
	char devmajor[8];
	char devminor[8];
	char prefix[155];
};

#pragma pack()

unsigned int tar_getsize(const char* input) {
	int	     i;
	unsigned int r = 0;
	for(i = 0; i < 11; i++) {
		r = r << 3;
		r = r | (input[i] - '0');
	}
	return r;
}

void* gf_resource_allocate(gf_resource_t* resource, size_t size) {
	unsigned int base = resource->size;
	if(resource->data == NULL) {
		resource->data = malloc(size);
	} else {
		unsigned char* old = resource->data;
		resource->data	   = malloc(base + size);
		memcpy(resource->data, old, base);
		free(old);
	}
	resource->size += size;
	memset(resource->data + base, 0, size);
	return resource->data + base;
}

gf_resource_t* gf_resource_create(gf_engine_t* engine, const char* path) {
	struct tar_header* th;
	int		   i;
	unsigned int	   cmpsize = 0;
	unsigned int	   cursize = 0;
	unsigned int	   curseek = 0;
	z_stream	   stream;
	int		   ret;
	FILE*		   f;
	gf_resource_t*	   resource = malloc(sizeof(*resource));

	memset(resource, 0, sizeof(*resource));
	resource->engine  = engine;
	resource->entries = NULL;
	resource->data	  = NULL;
	resource->size	  = 0;
	sh_new_strdup(resource->entries);

	if(path == NULL) {
		gf_log_function(engine, "Created empty resource", "");
		return resource;
	}
	f = fopen(path, "rb");

	if(f == NULL) {
		gf_log_function(engine, "Failed to create resource", "");
		gf_resource_destroy(resource);
		return NULL;
	}

	fseek(f, 0, SEEK_END);
	cmpsize = ftell(f);
	fseek(f, 0, SEEK_SET);

	stream.zalloc	= Z_NULL;
	stream.zfree	= Z_NULL;
	stream.opaque	= Z_NULL;
	stream.avail_in = 0;
	stream.next_in	= Z_NULL;

	if(inflateInit(&stream) != Z_OK) {
		gf_log_function(engine, "Failed to initialize zlib", "");
		gf_resource_destroy(resource);
		return NULL;
	}

	gf_log_function(engine, "Created resource", "");

	do {
		unsigned char in[CHUNK];
		unsigned char out[CHUNK];
		stream.avail_in = fread(in, 1, sizeof(in), f);
		if(stream.avail_in == 0) break;
		stream.next_in = in;

		do {
			int have;
			stream.avail_out = sizeof(out);
			stream.next_out	 = out;
			ret		 = inflate(&stream, Z_NO_FLUSH);
			if(ret == Z_NEED_DICT || ret == Z_DATA_ERROR || ret == Z_MEM_ERROR) {
				inflateEnd(&stream);
				gf_log_function(engine, "Failed to decompress", "");
				gf_resource_destroy(resource);
				return NULL;
			}
			have = sizeof(out) - stream.avail_out;
			memcpy(gf_resource_allocate(resource, have), out, have);
			cursize += have;
		} while(stream.avail_out == 0);
	} while(ret != Z_STREAM_END);
	inflateEnd(&stream);

	fclose(f);

	gf_log_function(engine, "Compression rate: %.2f%%", (double)cursize / cmpsize * 100);

	for(i = 0;; i++) {
		unsigned int	    sz;
		gf_resource_entry_t entry;
		th = (struct tar_header*)(resource->data + curseek);
		if(th->filename[0] == 0) break;

		curseek += 512;

		if(memcmp(th->ustar, "ustar", 6) != 0) {
			gf_log_function(engine, "Not USTAR", "");
			gf_resource_destroy(resource);
			resource = NULL;
			break;
		}

		sz = tar_getsize(&th->size[0]);

		gf_log_function(engine, "%s: %u bytes", th->filename, sz);

		entry.key     = th->filename;
		entry.address = curseek;
		entry.size    = sz;
		shputs(resource->entries, entry);

		if(sz != 0) curseek += ((sz / 512) + 1) * 512;
	}

	return resource;
}

int gf_resource_get(gf_resource_t* resource, const char* name, void** data, size_t* size) {
	if(resource->entries != NULL && shgeti(resource->entries, name) != -1) {
		gf_resource_entry_t e = shgets(resource->entries, name);
		*size		      = e.size;
		*data		      = malloc(e.size);
		memcpy(*data, resource->data + e.address, e.size);
		return 0;
	}
	return -1;
}

void gf_resource_add(gf_resource_t* resource, const char* name, void* data, size_t size, int dir) {
	gf_resource_entry_t e;
	struct tar_header*  th;
	unsigned char*	    d;
	size_t		    t;
	int		    i;

	d  = gf_resource_allocate(resource, 512);
	th = (struct tar_header*)&d[0];

	strcpy(th->filename, name);
	strcpy(th->ustar, "ustar");
	memcpy(th->ustarv, "00", 2);
	strcpy(th->mode, dir ? "0000755" : "0000644");
	th->typeflag[0] = dir ? '5' : '0';

	t = size;
	for(i = 10; i >= 0; i--) {
		th->size[i] = '0' + (t % 8);
		t /= 8;
	}

	t = time(NULL);
	for(i = 10; i >= 0; i--) {
		th->mtime[i] = '0' + (t % 8);
		t /= 8;
	}

	t = ' ' * sizeof(th->chksum);
	for(i = 0; i < sizeof(struct tar_header); i++) {
		t += d[i];
	}
	for(i = 6; i >= 0; i--) {
		th->chksum[i] = '0' + (t % 8);
		t /= 8;
	}

	e.key	  = (char*)name;
	e.address = resource->size;
	e.size	  = size;
	shputs(resource->entries, e);

	if(size != 0) {
		d = gf_resource_allocate(resource, ((size / 512) + 1) * 512);
		memcpy(d, data, size);
	}
}

void gf_resource_write(gf_resource_t* resource, const char* path, int progress) {
	unsigned char out[CHUNK];
	z_stream      stream;
	int	      i;
	FILE*	      f;
	stream.zalloc	= Z_NULL;
	stream.zfree	= Z_NULL;
	stream.opaque	= Z_NULL;
	stream.avail_in = 0;
	stream.next_in	= Z_NULL;

	if(deflateInit(&stream, Z_DEFAULT_COMPRESSION) != Z_OK) {
		return;
	}

	f = fopen(path, "wb");
	if(f != NULL) {
		unsigned int   totalog	= 0;
		unsigned int   totalcmp = 0;
		unsigned char* in;
		for(i = 0; i < shlen(resource->entries); i++) {
			unsigned int sz = resource->entries[i].size == 0 ? 0 : (((resource->entries[i].size / 512) + 1) * 512);
			in		= malloc(512 + sz);
			memcpy(in, resource->data + resource->entries[i].address - 512, 512 + sz);
			stream.avail_in = 512 + sz;
			stream.next_in	= in;

			totalog += 512 + sz;

			if(progress) {
				printf("%s", resource->entries[i].key);
				fflush(stdout);
			}

			do {
				unsigned int have;
				stream.avail_out = CHUNK;
				stream.next_out	 = out;
				deflate(&stream, Z_NO_FLUSH);
				have = CHUNK - stream.avail_out;
				fwrite(out, have, 1, f);
				if(progress) {
					printf(".");
					fflush(stdout);
				}
				totalcmp += have;
			} while(stream.avail_out == 0);

			if(progress) {
				printf("\n");
			}

			free(in);
		}

		in = malloc(512);
		memset(in, 0, 512);
		stream.avail_in = 512;
		stream.next_in	= in;
		totalog += 512;

		do {
			unsigned int have;
			stream.avail_out = CHUNK;
			stream.next_out	 = out;
			deflate(&stream, Z_FINISH);
			have = CHUNK - stream.avail_out;
			fwrite(out, have, 1, f);
			totalcmp += have;
		} while(stream.avail_out == 0);

		free(in);
		fclose(f);

		if(progress) {
			printf("Compression rate: %.2f%%\n", (double)totalog / totalcmp * 100);
		}
		gf_log_function(resource->engine, "Compression rate: %.2f%%\n", (double)totalog / totalcmp * 100);
	}
	deflateEnd(&stream);
}

void gf_resource_destroy(gf_resource_t* resource) {
	if(resource->entries != NULL) {
		shfree(resource->entries);
	}
	if(resource->data != NULL) {
		free(resource->data);
	}
	gf_log_function(resource->engine, "Destroyed resource", "");
	free(resource);
}
