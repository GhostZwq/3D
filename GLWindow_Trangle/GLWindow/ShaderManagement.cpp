
#include "ShaderManagement.h"

#include <memory>
#include <iostream>

ShaderManagement::ShaderManagement()
	: m_chVertex_Shader(nullptr)
	, m_chFragment_Shader(nullptr)
	, m_iVertex_Shader(0)
	, m_iFragment_Shader(0)
	, m_iShaderProgram(0)
	, m_hasCompiled(false)
{
	m_chVertex_Shader = new char[1024];
	m_chFragment_Shader = new char[1024];
	memset(m_chVertex_Shader, '\0', 1024);
	memset(m_chFragment_Shader, '\0', 1024);
}

ShaderManagement::~ShaderManagement()
{
	memset(m_chVertex_Shader, '\0', 1024);
	memset(m_chFragment_Shader, '\0', 1024);

	if (m_chVertex_Shader != nullptr)
	{
		delete[] m_chVertex_Shader;
		m_chVertex_Shader = nullptr;
	}

	if (m_chFragment_Shader != nullptr)
	{
		delete[] m_chFragment_Shader;
		m_chFragment_Shader = nullptr;
 	}
}

void ShaderManagement::init(char* vertexShader, char* fragShader)
{
	memset(m_chVertex_Shader, '\0', 1024);
	memcpy(m_chVertex_Shader, vertexShader, strlen(vertexShader));
	m_chVertex_Shader[strlen(vertexShader) + 1] = '\0';

	memset(m_chFragment_Shader, '\0', 1024);
	memcpy(m_chFragment_Shader, fragShader, strlen(fragShader));
	m_chFragment_Shader[strlen(fragShader) + 1] = '\0';
}

void ShaderManagement::compileShader()
{
	if (strlen(m_chVertex_Shader) == 0 ||
		strlen(m_chFragment_Shader) == 0)
	{
		return;
	}

	m_iVertex_Shader = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(m_iVertex_Shader, 1, &m_chVertex_Shader, NULL);
	glCompileShader(m_iVertex_Shader);

	// 检测编译是否成功
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(m_iVertex_Shader, GL_COMPILE_STATUS, &success);

	if (!success)
	{
		glGetShaderInfoLog(m_iVertex_Shader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	m_iFragment_Shader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(m_iFragment_Shader, 1, &m_chFragment_Shader, NULL);
	glCompileShader(m_iFragment_Shader);

	m_iShaderProgram = glCreateProgram();

	glAttachShader(m_iShaderProgram, m_iVertex_Shader);
	glAttachShader(m_iShaderProgram, m_iFragment_Shader);
	glLinkProgram(m_iShaderProgram);

	glGetProgramiv(m_iShaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(m_iShaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR: " << infoLog << std::endl;
	}

	// 删除着色器对象，不再需要
	glDeleteShader(m_iVertex_Shader);
	glDeleteShader(m_iFragment_Shader);

	m_hasCompiled = true;
}

void ShaderManagement::useShader()
{
	if (!m_hasCompiled)
	{
		return;
	}

	glUseProgram(m_iShaderProgram);
}

void ShaderManagement::unuseShader()
{
	glUseProgram(0);
}

GLuint ShaderManagement::getShaderProgram() const
{
	return m_iShaderProgram;
}