#ifndef VAO_HEADER
#define VAO_HEADER

enum _MeshType {
	MESH_2D,
	MESH_3D,
};
typedef enum _MeshType MeshType;

struct _Mesh {
	unsigned int vao;
	unsigned int vbo;
	unsigned int ebo;
};
typedef struct _Mesh Mesh;

Mesh mesh_new(MeshType type, float *verts, int verts_sz,
	unsigned int *idxs, int idxs_sz);
void mesh_release(Mesh *mesh);

#endif
