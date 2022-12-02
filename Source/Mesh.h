#pragma once

#include <vector>
#include "scene.h"
#include "GL/glew.h"

class Mesh
{
public:
	~Mesh();

	static Mesh* LoadMesh(const aiMesh* i_mesh);

	void Draw(const std::vector<GLuint>& i_modelTextures);

private:
	friend class WindowModel3D;

	Mesh();

	void LoadVBO(const aiMesh* i_mesh);
	void LoadEBO(const aiMesh* i_mesh);
	void CreateVAO();

	GLuint m_vbo;
	GLuint m_ebo;
	GLuint m_vao;

	int m_materialIndex;
	int m_numVertices;
	int m_numTriangles;
	int m_numIndices;
};

