#pragma once
#include <GL\glew.h>
#include <glm\glm.hpp>
#include <string>

class ShaderProgram {
public:
	ShaderProgram();
	~ShaderProgram();

	//loads vertex shader and fragment shader
	bool load(const std::string &vertFile, const std::string &fragFile);
	bool isLoaded() const;
	//clear all data from OpenGl
	void unLoad();

	bool linkProgram();
	//use the shader
	void bind()const;
	//detach the shader from usess
	void unbind();
	//requires a relink before opengl will register the change
	void addAttribute(unsigned int index, const std::string &attribName);
	//return -1 if attribute doesnt exist
	int getAttributeLocation(const std::string &name);
	//return -1 if uniform doesnt exist
	int getUniformLocation(const std::string &uniformName);
	
	//send data to the shaders
	void sendUniform(const std::string &uniformName, int integer);
	void sendUniform(const std::string &uniformName, unsigned int unsignedInteger);
	void sendUniform(const std::string &uniformName, float scalar);
	void sendUniform(const std::string &uniformName, const glm::vec2 &vector);
	void sendUniform(const std::string &uniformName, const glm::vec3 &vector);
	void sendUniform(const std::string &uniformName, const glm::vec4 &vector);
	void sendUniformMat3(const std::string &name, float* matrix, bool transpose);
	void sendUniformMat4(const std::string &name, float* matrix, bool transpose);
	
private:
	bool loaded = false;

	GLuint vertexShader = 0;
	GLuint fragShader = 0;
	GLuint program = 0;

	std::string readFile(const std::string &fileName);

	bool compileShader(GLuint shader)const;

	void outputShaderLog(GLuint shader)const;

	void outputProgramLog()const;



};