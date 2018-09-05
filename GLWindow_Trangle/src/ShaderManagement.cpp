
#include "ShaderManagement.h"

#include <memory>
#include <iostream>

#include <fstream>
#include <sstream>

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

void ShaderManagement::init(const char* vertexShaderPath, const char* fragShaderPath)
{
	std::string vertexCode;
	std::string fragCode;
	std::ifstream vShaderFile;
	std::ifstream fShaderFile;
	
	// 保证ifstream对象可以抛出异常
	vShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	fShaderFile.exceptions(std::ifstream::failbit | std::ifstream::badbit);
	
	try
	{
		// 打开文件
		vShaderFile.open(vertexShaderPath);
		fShaderFile.open(fragShaderPath);
		std::stringstream vShaderStream, fShaderStream;
		// 读取文件的缓冲区内容到数据流中
		vShaderStream << vShaderFile.rdbuf();
		fShaderStream << fShaderFile.rdbuf();
		// 关闭文件处理器
		vShaderFile.close();
		fShaderFile.close();
		// 数据流到string 
		vertexCode = vShaderStream.str();
		fragCode = fShaderStream.str();
	}
	catch (std::ifstream::failure e)
	{
		std::cout << "ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ" << std::endl;
	}
	
	memset(m_chVertex_Shader, '\0', 1024);
	memcpy(m_chVertex_Shader, vertexCode.c_str(), strlen(vertexCode.c_str()));
	m_chVertex_Shader[strlen(vertexCode.c_str()) + 1] = '\0';

	memset(m_chFragment_Shader, '\0', 1024);
	memcpy(m_chFragment_Shader, fragCode.c_str(), strlen(fragCode.c_str()));
	m_chFragment_Shader[strlen(fragCode.c_str()) + 1] = '\0';
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

void ShaderManagement::setBool(const std::string& name, bool value) const
{
	glUniform1i(glGetUniformLocation(m_iShaderProgram, name.c_str()), (int)value);
}

void ShaderManagement::setInt(const std::string &name, int value) const
{
	glUniform1i(glGetUniformLocation(m_iShaderProgram, name.c_str()), value);
}
void ShaderManagement::setFloat(const std::string &name, float value) const
{
	glUniform1f(glGetUniformLocation(m_iShaderProgram, name.c_str()), value);
}