#include "mesh.h"

#include <glad/glad.h>

Mesh mesh_new(float *verts, int verts_sz, unsigned int *idxs, int idxs_sz) {
	Mesh mesh;
	glGenVertexArrays(1, &(mesh.vao));
	glGenBuffers(1, &(mesh.vbo));
	glGenBuffers(1, &(mesh.ebo));

	glBindVertexArray(mesh.vao);

	glBindBuffer(GL_ARRAY_BUFFER, mesh.vbo);
	glBufferData(
		GL_ARRAY_BUFFER,
		verts_sz * sizeof(float),
		verts,
		GL_STATIC_DRAW
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, mesh.ebo);
	glBufferData(
		GL_ELEMENT_ARRAY_BUFFER,
		idxs_sz * sizeof(unsigned int),
		idxs,
		GL_STATIC_DRAW
	);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	return mesh;
}
