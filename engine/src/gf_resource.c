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

#pragma pack(1)

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
		unsigned char in[32767];
		unsigned char out[32767];
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
			if(resource->data == NULL) {
				resource->data = malloc(have);
				memcpy(resource->data, out, have);
			} else {
				unsigned char* old = resource->data;
				resource->data	   = malloc(cursize + have);
				memcpy(resource->data, old, cursize);
				memcpy(resource->data + cursize, out, have);
				free(old);
			}
			cursize += have;
		} while(stream.avail_out == 0);
	} while(ret != Z_STREAM_END);
	inflateEnd(&stream);

	fclose(f);

	gf_log_function(engine, "Compression made the file size %.2f%%", (double)cmpsize / cursize * 100);

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
