#include "Shaders.h"

#include <fstream>
#include <iostream>
#include <vector>


Shader::Shader()
{
}

Shader::~Shader()
{
	if (loaded)
	{
		unload();
	}
}

bool Shader::Load(const std::string & vertFile, const std::string & fragFile)
{
	//create Shader and program objects
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	fragShader = glCreateShader(GL_FRAGMENT_SHADER);
	Program = glCreateProgram();


	//load sourcecode
	std::string source = readFile(vertFile);
	const GLchar *temp = static_cast<const GLchar *>(source.c_str());
	glShaderSource(vertexShader, 1, &temp, NULL);

	source = readFile(fragFile);
	temp = static_cast<const GLchar *>(source.c_str());
	glShaderSource(fragShader, 1, &temp, NULL);

	//Compile the code
	if (!compileShader(vertexShader))
	{
		std::cout << "vertex shader failed to compile" << std::endl;

		outputShaderLog(vertexShader);
		unload();

		return false;
	}

	if (!compileShader(fragShader))
	{
		std::cout << "Frag shader failed to compile" << std::endl;

		outputShaderLog(fragShader);
		unload();

		return false;
	}
	//setup our program object
	glAttachShader(Program, vertexShader);
	glAttachShader(Program, fragShader);

	if (!linkProgram())
	{
		std::cout << "Shader program failed to link" << std::endl;

		outputProgramLog();
		unload();
		return false;
	}

	loaded = true;
	return true;

}

bool Shader::isLoaded() const
{
	return loaded;
}

void Shader::unload()
{
	if (vertexShader != 0)
	{
		glDetachShader(Program, vertexShader);
		glDeleteShader(vertexShader);
		vertexShader = 0;
	}
	if (fragShader != 0)
	{
		glDetachShader(Program, fragShader);
		glDeleteShader(fragShader);
		fragShader = 0;
	}

	if (Program != 0)
	{
		glDeleteProgram(Program);
		Program = 0;
	}

	loaded = false;

}

bool Shader::linkProgram()
{
	glLinkProgram(Program);

	GLint success;
	glGetProgramiv(Program, GL_LINK_STATUS, &success);

	return success == GL_TRUE;
}

void Shader::bind() const
{
	glUseProgram(Program);
}

void Shader::unbind()
{
	glUseProgram(GL_NONE);
}

void Shader::addAttribute(unsigned int index, const std::string & attribName)
{
	glBindAttribLocation(Program, index, attribName.c_str());
}

int Shader::getAttributeLocation(const std::string & name)
{
	return glGetAttribLocation(Program, name.c_str());
}

int Shader::getUniformLocation(const std::string & uniformName)
{
	return glGetUniformLocation(Program, uniformName.c_str());
}

void Shader::sendUniform(const std::string & name, int integer)
{
	GLint location = getUniformLocation(name);
	glUniform1i(location, integer);
}

void Shader::sendUniform(const std::string & name, unsigned int unsignedInteger)
{
	GLint location = getUniformLocation(name);
	glUniform1ui(location, unsignedInteger);
}

void Shader::sendUniform(const std::string & name, float scalar)
{
	GLint location = getUniformLocation(name);
	glUniform1f(location, scalar);
}

void Shader::sendUniform(const std::string & name, const glm::vec2 & vector)
{
	GLint location = getUniformLocation(name);
	glUniform2f(location, vector.x, vector.y);
}

void Shader::sendUniform(const std::string & name, const glm::vec3 & vector)
{
	GLint location = getUniformLocation(name);
	glUniform3f(location, vector.x, vector.y,vector.z);
}

void Shader::sendUniform(const std::string & name, const glm::vec4 & vector)
{
	GLint location = getUniformLocation(name);
	glUniform4f(location, vector.x, vector.y, vector.z,vector.w);
}

void Shader::sendUniformMat3(const std::string & name, float * matrix, bool transpose)
{
	GLint location = getUniformLocation(name);
	glUniformMatrix3fv(location, 1, transpose, matrix);
}

void Shader::sendUniformMat4(const std::string & name, float* matrix, bool transpose)
{
	GLint location = getUniformLocation(name);
	glUniformMatrix4fv(location, 1, transpose, matrix);
}

std::string Shader::readFile(const std::string & filename) const
{
	std::ifstream input(filename);

	if (!input)
	{
		std::cout << "Shader file not found" << filename << std::endl;
		return "";
	}

	std::string data(std::istreambuf_iterator<char>(input), (std::istreambuf_iterator<char>()));
	return data;
}

bool Shader::compileShader(GLuint shader) const
{
	glCompileShader(shader);

	GLint success;
	glGetShaderiv(shader, GL_COMPILE_STATUS, &success);

	return success == GL_TRUE;
}

void Shader::outputShaderLog(GLuint shader) const
{
	std::string infoLog;

	GLint infoLen;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &infoLen);

	infoLog.resize(infoLen);

	glGetShaderInfoLog(shader, infoLen, &infoLen, &infoLog[0]);

	std::cout << infoLog << std::endl;
}

void Shader::outputProgramLog() const
{
	std::string infoLog;

	GLint infoLen;
	glGetProgramiv(Program, GL_INFO_LOG_LENGTH, &infoLen);

	infoLog.resize(infoLen);

	glGetProgramInfoLog(Program, infoLen, &infoLen, &infoLog[0]);

	std::cout << infoLog << std::endl;
}
