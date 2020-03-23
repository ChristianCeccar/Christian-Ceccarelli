#include "ShaderProgram.h"

#include <fstream>
#include <iostream>
#include <vector>

ShaderProgram::ShaderProgram() {

}
ShaderProgram::~ShaderProgram() {
	if (loaded) {
		unLoad();
	}
}

//loads vertex shader and fragment shader
bool ShaderProgram::load(const std::string &vertFile, const std::string &fragFile) {
	//create shader and program objects
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	program = glCreateProgram();
	//load source code
	std::string source = readFile(vertFile);
	const GLchar *temp = static_cast<const GLchar *>(source.c_str());
	glShaderSource(vertexShader, 1, &temp, NULL);

	source = readFile(fragFile);
	temp = static_cast<const GLchar *>(source.c_str());
	glShaderSource(fragShader, 1, &temp, NULL);

	//Compile the code
	if (!compileShader(vertexShader)) {
		std::cout << "Vertex shader failed to compile" << std::endl;

		outputShaderLog(vertexShader);
		unLoad();
		return false;
	}
	if (!compileShader(fragShader)) {
		std::cout << "frag shader failed to compile" << std::endl;

		outputShaderLog(fragShader);
		unLoad();
		return false;
	}

	//setup our program object
	glAttachShader(program, vertexShader);
	glAttachShader(program, fragShader);

	if (!linkProgram()) {
		std::cout << "Shader program failed to link" << std::endl;
		outputProgramLog();
		unLoad();
		return false;
	}
	loaded = true;
	return true;
}
bool ShaderProgram::isLoaded()const {
	return loaded;
}
//clear all data from OpenGl
void ShaderProgram::unLoad() {
	if (vertexShader != 0) {
		glDetachShader(program, vertexShader);
		glDeleteShader(vertexShader);
		vertexShader = 0;

	}
	if (fragShader != 0) {
		glDetachShader(program, fragShader);
		glDeleteShader(fragShader);
		fragShader = 0;

	}

	if (program != 0) {
		glDeleteProgram(program);
		program = 0;

	}
	loaded = false;
}

bool ShaderProgram::linkProgram() {
	glLinkProgram(program);

	GLint success;
	glGetProgramiv(program, GL_LINK_STATUS, &success);

	return success == GL_TRUE;

}
//use the shader
void ShaderProgram::bind()const {
	glUseProgram(program);
}
//detach the shader from usess
void ShaderProgram::unBind() {
	glUseProgram(GL_NONE);
}
//requires a relink before opengl will register the change
void ShaderProgram::addAttribute(unsigned int index, const std::string &attribName) {
	glBindAttribLocation(program, index, attribName.c_str());
}
//return -1 if attribute doesnt exist
int ShaderProgram::getAttributeLocation(const std::string &name) {
	return glGetAttribLocation(program, name.c_str());
}
//return -1 if uniform doesnt exist
int ShaderProgram::getUniformLocation(const std::string &uniformName) {
	return glGetUniformLocation(program, uniformName.c_str());
}
//send data to the shaders
void ShaderProgram::sendUniform(const std::string &uniformName, int integer) {

	GLint location = getUniformLocation(uniformName);
	glUniform1i(location, integer);
}
void ShaderProgram::sendUniform(const std::string &uniformName, unsigned int unsignedInteger) {

	GLint location = getUniformLocation(uniformName);
	glUniform1ui(location, unsignedInteger);
}
void ShaderProgram::sendUniform(const std::string &uniformName, float scalar) {
	GLint location = getUniformLocation(uniformName);
	glUniform1f(location, scalar);
}
void ShaderProgram::sendUniform(const std::string &uniformName, const glm::vec2 &vector) {
	GLint location = getUniformLocation(uniformName);
	glUniform2f(location, vector.x, vector.y);
}
void ShaderProgram::sendUniform(const std::string &uniformName, const glm::vec3 &vector) {
	GLint location = getUniformLocation(uniformName);
	glUniform3f(location, vector.x, vector.y, vector.z);
}
void ShaderProgram::sendUniform(const std::string &uniformName, const glm::vec4 &vector) {
	GLint location = getUniformLocation(uniformName);
	glUniform4f(location, vector.x, vector.y, vector.z, vector.w);
}
void ShaderProgram::sendUniformMat3(const std::string &name, float* matrix, bool transpose) {
	GLint location = getUniformLocation(name);
	glUniformMatrix3fv(location, 1, transpose, matrix);
}
void ShaderProgram::sendUniformMat4(const std::string &name, float* matrix, bool transpose) {
	GLint location = getUniformLocation(name);
	glUniformMatrix4fv(location, 1, transpose, matrix);
}

std::string ShaderProgram::readFile(const std::string &fileName) {
	std::ifstream input(fileName);
	if (!input) {
		std::cout << "shader file not found" << fileName << std::endl;
		return "";
	}
	std::string data(std::istreambuf_iterator<char>(input), (std::istreambuf_iterator<char>()));
	return data;

}

bool ShaderProgram::compileShader(GLuint shader)const {
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
	return success == GL_TRUE;
}

void ShaderProgram::outputShaderLog(GLuint shader)const {
	std::string infoLog;
	GLint infoLen;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);


	infoLog.resize(infoLen);

	glGetShaderInfoLog(shader, infoLen, &infoLen, &infoLog[0]);
	std::cout << infoLog << std::endl;

}

void ShaderProgram::outputProgramLog()const {
	std::string infoLog;
	GLint infoLen;
	glGetProgramiv(program, GL_INFO_LOG_LENGTH, &infoLen);


	infoLog.resize(infoLen);

	glGetProgramInfoLog(program, infoLen, &infoLen, &infoLog[0]);
	std::cout << infoLog << std::endl;
}