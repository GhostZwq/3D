#define GLEW_STATIC
//#include <glad\glad.h>                   // should put in the top of this file, or compiling will be fault.
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>

// Customer File
#include "ShaderManagement.h"
#include "ShaderInfo.h"
#include "VertexInfo.h"
#include "stb_image.h"


bool g_line = false;
float g_definition = 0.0;

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// 用户按下Esc键，我们设置window窗口的windowShouldClose属性为True
	// 关闭应用程序
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
	{
		glfwSetWindowShouldClose(window, GL_TRUE);
	}
	if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
	{
		if (g_line == true)
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
		}
		else
		{
			glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
		}

		g_line = !g_line;
	}
	if (key == GLFW_KEY_UP && action == GLFW_PRESS)
	{
		g_definition += 0.1;
		if (g_definition > 1.0)
		{
			g_definition = 1.0;
		}

	}
	if (key == GLFW_KEY_DOWN && action == GLFW_PRESS)
	{
		g_definition -= 0.1;
		if (g_definition < 0.0)
		{
			g_definition = 0.0;
		}
	}
}

int main()
{

	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);

	GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", nullptr, nullptr);
	if (window == nullptr)
	{
		std::cout << "Failed to create GLFW window" << std::endl;
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window);

	glewExperimental = GL_TRUE;
	if (glewInit() != GLEW_OK)
	{
		std::cout << "Failed to initialize GLEW" << std::endl;
		return -1;
	}

	// 注册回调函数
	glfwSetKeyCallback(window, key_callback);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);

	ShaderManagement shader;
	shader.init("../Shaders/VertexShader.vs", "../Shaders/FragShader.fs");
	shader.compileShader();
	//shader.useShader();                    // 后面setFloat函数要用到shaderprogram函数，所以这里需要先use program
	
	GLuint VBO;
	glGenBuffers(1, &VBO);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	GLuint EBO;
	glGenBuffers(1, &EBO);

	// 绑定VAO, 其后所有VBO操作都会存储到这个VAO中，供后续使用
	glBindVertexArray(VAO);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_texture), vertices_texture, GL_STATIC_DRAW);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices_texture), indices_texture, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);

	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);

	glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
	glEnableVertexAttribArray(2);

	// 解绑VAO
	glBindVertexArray(0);
	
	// Texture Operation	
	unsigned int texture1, texture2;
	glGenTextures(1, &texture1);
	glGenTextures(1, &texture2);

	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, texture1);

	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	// 加载并生成纹理
	int i_Width, i_Height, nrChannels;
	// 反转图片Y轴，使之与OpenGL坐标系匹配。
	stbi_set_flip_vertically_on_load(true);
	unsigned char* data = stbi_load("../Resource/Bitmap/container.jpg", &i_Width, &i_Height, &nrChannels, 0);
	if (data)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, i_Width, i_Height, 0, GL_RGB, GL_UNSIGNED_BYTE, data);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	// 释放图片内存
	stbi_image_free(data);
	//glBindTexture(GL_TEXTURE_2D, 0);

	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, texture2);

	// 为当前绑定的纹理对象设置环绕、过滤方式
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);

	
	// 加载并生成纹理
	unsigned char* dataFace = stbi_load("../Resource/Bitmap/awesomeface.png", &i_Width, &i_Height, &nrChannels, 0);
	if (dataFace)
	{
		glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, i_Width, i_Height, 0, GL_RGBA, GL_UNSIGNED_BYTE, dataFace);
		glGenerateMipmap(GL_TEXTURE_2D);
	}
	else
	{
		std::cout << "Failed to load texture" << std::endl;
	}
	// 释放图片内存
	stbi_image_free(dataFace);
	// Texture Done

	// 要放在getShaderProgram前面，否则无效
	shader.useShader();

	// 改变清晰度

	// 把纹理赋值给片段着色器的采样器
	glBindTexture(GL_TEXTURE_2D, texture1);
	glBindTexture(GL_TEXTURE_2D, texture2);
	glUniform1i(glGetUniformLocation(shader.getShaderProgram(), "texture1"), 0);
	//glUniform1i(glGetUniformLocation(shader.getShaderProgram(), "texture2"), 1);
	shader.setInt("texture2", 1);
	glBindVertexArray(VAO);


	while (!glfwWindowShouldClose(window))
	{
		// 检查事件
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);


		glUniform1f(glGetUniformLocation(shader.getShaderProgram(), "definition"), g_definition);

		//glDrawArrays(GL_TRIANGLES, 0, 6);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);


		// 交换缓冲
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}