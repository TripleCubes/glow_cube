#include "mesh.h"

#include <glad/glad.h>

Mesh mesh_new(MeshType type, float *verts, int verts_sz,
unsigned int *idxs, int idxs_sz) {
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

	if (type == MESH_3D) {
		glVertexAttribPointer(
			0, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float),
			(void*)0
		);
		glEnableVertexAttribArray(0);

		glVertexAttribPointer(
			1, 3, GL_FLOAT, GL_FALSE, 8*sizeof(float),
			(void*)(3 * sizeof(float))
		);
		glEnableVertexAttribArray(1);

		glVertexAttribPointer(
			2, 2, GL_FLOAT, GL_FALSE, 8*sizeof(float),
			(void*)(6 * sizeof(float))
		);
		glEnableVertexAttribArray(2);
	}
	else if (type == MESH_2D) {
		glVertexAttribPointer(
			0, 2, GL_FLOAT, GL_FALSE, 2*sizeof(float), (void*)0
		);
		glEnableVertexAttribArray(0);
	}

	return mesh;
}

void mesh_release(Mesh *mesh) {
	glDeleteVertexArrays(1, &(mesh->vao));
	glDeleteBuffers(1, &(mesh->vbo));
	glDeleteBuffers(1, &(mesh->ebo));
}
