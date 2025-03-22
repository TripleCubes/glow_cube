#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

typedef struct _Result Result;

struct _Framebuffer {
	int w;
	int h;
	unsigned int fbo;
	unsigned int texture_id;
};
typedef struct _Framebuffer Framebuffer;

Result framebuffer_new(Framebuffer *fb, int w, int h);
void framebuffer_release(Framebuffer *fb);

#endif
