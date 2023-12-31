#ifndef TRIANGLE_LIST_H
#define TRIANGLE_LIST_H

#include <GL/glew.h>
#include <vector>

#include <ogl_dev/ogldev_math_3d.h>

class BaseTerrain;

class TriangleList {
public:
	TriangleList();

	void CreateTriangleList(int Width, int Depth, const BaseTerrain* pTerrain);
 
	void Render();

private:

	struct Vertex {
		Vector3f Pos;
		void InitVertex(const BaseTerrain* pTerrain, int x, int z);
	};

	void CreateGLState();
	void PopulateBuffers(const BaseTerrain* pTerrain);
	void InitVertices(const BaseTerrain* pTerrain, std::vector<Vertex>& Vertices);
	void InitIndices(std::vector<uint>& Indices);

	int m_depth = 0;

	int m_width = 0;

	GLuint m_vao;
	GLuint m_vb;
	GLuint m_ib;
};
#endif
