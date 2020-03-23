#pragma once
#include <string>
#include <GL\glew.h>

class Mesh {
public:
	Mesh();
	~Mesh();

	//load a mesh
	bool loadFromFile(const std::string &file);


	// release data from opengl (vram)
	void unload();

	unsigned int getNumFaces() const;
	unsigned int getNumVertices() const;

	//opengl buffers and objects
	GLuint vboVertices = 0;
	GLuint vboUVs = 0;
	GLuint vboNormals = 0;
	GLuint vao = 0;

private:
	unsigned int numFaces = 0;
	unsigned int numVertices = 0;
};