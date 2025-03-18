#ifndef VAO_HEADER
#define VAO_HEADER

struct _Mesh {
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
};
typedef struct _Mesh Mesh;

Mesh mesh_new(float *verts, int verts_sz, unsigned int *idxs, int idxs_sz);

#endif
