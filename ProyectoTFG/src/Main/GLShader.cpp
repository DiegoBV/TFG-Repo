#if defined (GL_DEBUG) || defined (GL_RELEASE)
#include "GLShader.h"
#include <glad/glad.h>
#include "FileHandler.h"
#include "ShaderInclude.h"
#include <iostream>

GLShader::GLShader()
{
}

GLShader::~GLShader()
{
}

void GLShader::init(const char * vertexPath, const char * fragmentPath)
{
	std::string vertexCode = ShaderInclude::InterpretShader(vertexPath, "#include");
	std::string fragmentCode = ShaderInclude::InterpretShader(fragmentPath, "#include");

	const char* vShaderCode = vertexCode.c_str();
	const char * fShaderCode = fragmentCode.c_str();
	// COMPILE SHADERS
	unsigned int vertex, fragment;
	// vertex shader
	vertex = compileShader(GL_VERTEX_SHADER, vShaderCode);
	checkCompileErrors(vertex, "VERTEX");
	// fragment Shader
	fragment = compileShader(GL_FRAGMENT_SHADER, fShaderCode);
	checkCompileErrors(fragment, "FRAGMENT");
	// shader Program
	ID = createGLProgram(vertex, fragment);
	checkCompileErrors(ID, "PROGRAM");

	// delete the shaders as they're linked into our program now and no longer necessary
	glDeleteShader(vertex);
	glDeleteShader(fragment);
}

unsigned int GLShader::compileShader(unsigned int type, const char* source)
{
	unsigned int shader;
	shader = glCreateShader(type);
	glShaderSource(shader, 1, &source, NULL);
	glCompileShader(shader);

	return shader;
}

unsigned int GLShader::createGLProgram(unsigned int vertexShader, unsigned int fragmentShader)
{
	unsigned int programID = glCreateProgram();
	glAttachShader(programID, vertexShader);
	glAttachShader(programID, fragmentShader);
	glLinkProgram(programID);

	return programID;
}

void GLShader::use()
{
	glUseProgram(ID);
}

void GLShader::setBool(const std::string & name, bool value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), (int)value);
}

void GLShader::setInt(const std::string & name, int value) const
{
	glUniform1i(glGetUniformLocation(ID, name.c_str()), value);
}

void GLShader::setFloat(const std::string & name, float value) const
{
	glUniform1f(glGetUniformLocation(ID, name.c_str()), value);
}

void GLShader::setVec2(const std::string & name, const glm::vec2 & value) const
{
	glUniform2fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void GLShader::setVec2(const std::string & name, float x, float y) const
{
	glUniform2f(glGetUniformLocation(ID, name.c_str()), x, y);
}

void GLShader::setVec3(const std::string & name, const glm::vec3 & value) const
{
	glUniform3fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void GLShader::setVec3(const std::string & name, float x, float y, float z) const
{
	glUniform3f(glGetUniformLocation(ID, name.c_str()), x, y, z);
}

void GLShader::setVec4(const std::string & name, const glm::vec4 & value) const
{
	glUniform4fv(glGetUniformLocation(ID, name.c_str()), 1, &value[0]);
}

void GLShader::setVec4(const std::string & name, float x, float y, float z, float w)
{
	glUniform4f(glGetUniformLocation(ID, name.c_str()), x, y, z, w);
}

void GLShader::setMat2(const std::string & name, const glm::mat2 & mat) const
{
	glUniformMatrix2fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void GLShader::setMat3(const std::string & name, const glm::mat3 & mat) const
{
	glUniformMatrix3fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void GLShader::setMat4(const std::string & name, const glm::mat4 & mat) const
{
	glUniformMatrix4fv(glGetUniformLocation(ID, name.c_str()), 1, GL_FALSE, &mat[0][0]);
}

void GLShader::checkCompileErrors(unsigned int shader, std::string type)
{
	int success;
	char infoLog[1024];
	if (type != "PROGRAM")
	{
		glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
		if (!success)
		{
			glGetShaderInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::SHADER_COMPILATION_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
	else
	{
		glGetProgramiv(shader, GL_LINK_STATUS, &success);
		if (!success)
		{
			glGetProgramInfoLog(shader, 1024, NULL, infoLog);
			std::cout << "ERROR::PROGRAM_LINKING_ERROR of type: " << type << "\n" << infoLog << "\n -- --------------------------------------------------- -- " << std::endl;
		}
	}
}
#endif