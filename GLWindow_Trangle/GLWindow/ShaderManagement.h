
#ifndef SHADER_MANAGEMENT_H
#define SHADER_MANAGEMENT_H

#include <gl\glew.h>

class ShaderManagement
{
public:
	ShaderManagement();
	~ShaderManagement();

public:
	void init(char* vertexShader, char* fragShader);
	void compileShader();
	void useShader();
	void unuseShader();

public:
	GLuint getShaderProgram() const;

private:
	char* m_chVertex_Shader;
	char* m_chFragment_Shader;
	GLuint m_iVertex_Shader;
	GLuint m_iFragment_Shader;
	GLuint m_iShaderProgram;
	bool   m_hasCompiled;
};



#endif