#include "texture.h"

#include <glad/glad.h>
#include <stb_image.h>
#include "result.h"

Result texture_new(Texture *texture, const char* path) {
	int data_w, data_h, num_color_channels;
	unsigned char *data = stbi_load(
		path,
		&data_w,
		&data_h,
		&num_color_channels,
		0
	);
	if (data == NULL) {
		return ERR("texture_new(): stbi_load() err");
	}

	texture->w = data_w;
	texture->h = data_h;

	glGenTextures(1, &(texture->id));
	glBindTexture(GL_TEXTURE_2D, texture->id);

	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_BORDER);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	glTexImage2D(
		GL_TEXTURE_2D,
		0,
		GL_RGBA,
		data_w,
		data_h,
		0,
		GL_RGBA,
		GL_UNSIGNED_BYTE,
		data
	);

	stbi_image_free(data);

	return OK;
}
