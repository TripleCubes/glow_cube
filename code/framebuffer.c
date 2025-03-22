#include "framebuffer.h"

#include <glad/glad.h>
#include "result.h"

Result framebuffer_new(Framebuffer *fb, int w, int h) {
	fb->w = w;
	fb->h = h;

	glGenFramebuffers(1, &(fb->fbo));
	glBindFramebuffer(GL_FRAMEBUFFER, fb->fbo);

	glGenTextures(1, &(fb->texture_id));
	glBindTexture(GL_TEXTURE_2D, fb->texture_id);
	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGB,
		w,
		h,
		0,
		GL_RGB,
		GL_UNSIGNED_BYTE,
		NULL
	);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glFramebufferTexture2D(
		GL_FRAMEBUFFER,
		GL_COLOR_ATTACHMENT0,
		GL_TEXTURE_2D,
		fb->texture_id,
		0
	);

	if (glCheckFramebufferStatus(GL_FRAMEBUFFER) != GL_FRAMEBUFFER_COMPLETE) {
		return ERR("framebuffer_new(): can't init framebuffer");
	}

	return OK;
}

void framebuffer_release(Framebuffer *fb) {
	glDeleteTextures(1, &(fb->texture_id));
	glDeleteFramebuffers(1, &(fb->fbo));
}
