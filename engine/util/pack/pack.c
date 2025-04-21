/* Engine */
#include <gf_version.h>
#include <gf_resource.h>

/* External library */

/* Standard */
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/stat.h>
#ifdef _WIN32
#include <windows.h>
#define gf_stat _stat
#else
#include <dirent.h>
#define gf_stat stat
#endif

char* out  = NULL;
char* base = ".";

int add_all(gf_resource_t* resource, char* path) {
#ifdef _WIN32
#else
	DIR*	       dir;
	struct dirent* d;
#endif
	int   st = 0;
	char* op = malloc(strlen(base) + 1 + strlen(path) + 1);
	op[0]	 = 0;
	strcat(op, base);
	strcat(op, "/");
	strcat(op, path);

#ifdef _WIN32
	st = -1;
#else
	dir = opendir(op);
	if(dir == NULL) {
		free(op);
		fprintf(stderr, "Could not open directory\n");
		return -1;
	}
	while((d = readdir(dir)) != NULL) {
		if(strcmp(d->d_name, ".") != 0 && strcmp(d->d_name, "..") != 0) {
			char*	       p  = malloc(strlen(base) + 1 + strlen(path) + strlen(d->d_name) + 1);
			char*	       np = malloc(strlen(path) + strlen(d->d_name) + 1 + 1);
			struct gf_stat s;
			p[0] = 0;
			strcat(p, base);
			strcat(p, "/");
			strcat(p, path);
			strcat(p, d->d_name);

			np[0] = 0;
			strcat(np, path);
			strcat(np, d->d_name);

			gf_stat(p, &s);

			if(S_ISDIR(s.st_mode)) {
				strcat(np, "/");
				gf_resource_add(resource, np, NULL, 0, 1);
				if((st = add_all(resource, np)) != 0) {
					free(np);
					break;
				}
			} else {
				FILE* f = fopen(p, "rb");
				if(f != NULL) {
					unsigned int   sz;
					unsigned char* data;
					fseek(f, 0, SEEK_END);
					sz = ftell(f);
					fseek(f, 0, SEEK_SET);

					data = malloc(sz);
					fread(data, sz, 1, f);
					fclose(f);

					gf_resource_add(resource, np, data, sz, 0);

					free(data);
				}
			}
			free(np);

			free(p);
		}
	}
	closedir(dir);
#endif
	free(op);
	return st;
}

int main(int argc, char** argv) {
	gf_version_t   version;
	gf_resource_t* resource;
	int	       i;
	int	       st = 0;

	gf_version_get(&version);
	printf("GoldFish Engine Resource Packer %s\n", version.full);
	for(i = 1; i < argc; i++) {
		if(argv[i][0] == '-') {
			if(strcmp(argv[i], "-d") == 0) {
				base = argv[++i];
			} else {
				fprintf(stderr, "Invalid flag: %s\n", argv[i]);
				return 1;
			}
		} else {
			out = argv[i];
		}
	}

	if(out == NULL || base == NULL) {
		fprintf(stderr, "Usage: %s [-d basedir] output\n", argv[0]);
		return 1;
	}

	resource = gf_resource_create(NULL, NULL);
	if(resource != NULL) {
		if(add_all(resource, "") != 0) {
			st = 1;
		}
		gf_resource_write(resource, out);
		gf_resource_destroy(resource);
	}
	return st;
}
