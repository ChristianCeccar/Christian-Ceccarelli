#pragma once

#include <GL\glew.h>
#include <glm\glm.hpp>
#include <string>

class Shader
{
public:
	Shader();
	~Shader();

	// Loads a vertex shader and a fragment shader
	// places them in a program

	bool Load(const std::string &vertFile, const std::string &fragFile);
	bool isLoaded() const;

	// Clear all data from OpenGL
	void unload();

	bool linkProgram();

	//use the shader
	void bind() const;
	// detach the shader from the usess
	void unbind();

	// requires a re-link for openGL to register the change
	void addAttribute(unsigned int index, const std::string &attribName);

	//returns -1 if the attribute does not exist
	int getAttributeLocation(const std::string &name);

	//returns -1 if uniform does not exist
	int getUniformLocation(const std::string &uniformName);

	//send data to the shaders
	void sendUniform(const std::string &name, int integer);
	void sendUniform(const std::string &name, unsigned int unsignedInteger);
	void sendUniform(const std::string &name, float scalar);
	void sendUniform(const std::string &name, const glm::vec2 &vector);
	void sendUniform(const std::string &name, const glm::vec3 &vector);
	void sendUniform(const std::string &name, const glm::vec4 &vector);
	void sendUniformMat3(const std::string &name, float *matrix, bool transpose);
	void sendUniformMat4(const std::string &name, float *matrix, bool transpose);

private:
	bool loaded = false;

	GLuint vertexShader = 0;
	GLuint fragShader = 0;
	GLuint Program = 0;

	std::string readFile(const std::string &filename) const;

	bool compileShader(GLuint shader) const;

	void outputShaderLog(GLuint shader) const;

	void outputProgramLog() const;



};