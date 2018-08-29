
#ifndef SHADER_MANAGEMENT_H
#define SHADER_MANAGEMENT_H

#include <gl\glew.h>
#include <string>

class ShaderManagement
{
public:
	ShaderManagement();
	~ShaderManagement();

public:
	void init(const char* vertexShaderPath, const char* fragShaderPath);
	void compileShader();
	void useShader();
	void unuseShader();

public:
	GLuint getShaderProgram() const;

	// uniform¹¤¾ßº¯Êý
	void setBool(const std::string& name, bool value) const;
	void setInt(const std::string& name, int value) const;
	void setFloat(const std::string& name, float value) const;

private:
	char* m_chVertex_Shader;
	char* m_chFragment_Shader;
	GLuint m_iVertex_Shader;
	GLuint m_iFragment_Shader;
	GLuint m_iShaderProgram;
	bool   m_hasCompiled;
};



#endif