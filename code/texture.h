#ifndef TEXTURE_HEADER
#define TEXTURE_HEADER

typedef struct _Result Result;

struct _Texture {
	unsigned int id;
	int w;
	int h;
};
typedef struct _Texture Texture;

Result texture_new(Texture *texture, const char* path);
void texture_release(Texture *texture);

#endif
