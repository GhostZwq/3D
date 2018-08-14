#define GLEW_STATIC
//#include <glad\glad.h>                   // should put in the top of this file, or compiling will be fault.
#include <gl\glew.h>
#include <GLFW\glfw3.h>
#include <iostream>


bool g_line = false;

GLfloat vertices[] = {
	-0.5f, -0.5f, 0.0f,
	 0.5f, -0.5f, 0.0f,
	 0.0f,  0.5f, 0.0f
};

GLfloat vertices_rect[] = {
	0.5f, 0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	-0.5f, -0.5f, 0.0f,
	-0.5f, 0.5f, 0.0f
};

GLuint indices[] = {
	0, 1, 3,
	1, 2, 3
};

char* vertex_shader = {
	"#version 330 core                           \n"
	"layout (location = 0) in vec3 position;     \n"
	"                                            \n"
	"void main()                                 \n"
	"{                                           \n"
	"    gl_Position = vec4(position.x, position.y, position.z, 1.0); \n"
	"}                                           \n"
};

char* fragment_shader = {
	"#version 330 core                           \n"
	"out vec4 color;                             \n"
	"void main()                                 \n"
	"{                                           \n"
	"    color = vec4(1.0f, 0.5f, 0.2f, 1.0f);   \n"
	"}"
};

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mode)
{
	// �û�����Esc������������window���ڵ�windowShouldClose����ΪTrue
	// �ر�Ӧ�ó���
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

	// ע��ص�����
	glfwSetKeyCallback(window, key_callback);

	int width, height;
	glfwGetFramebufferSize(window, &width, &height);
	glViewport(0, 0, width, height);
	
	GLuint vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);
	
	glShaderSource(vertexShader, 1, &vertex_shader, NULL);
	glCompileShader(vertexShader);

	// �������Ƿ�ɹ�
	GLint success;
	GLchar infoLog[512];
	glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
	
	if (!success)
	{
		glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
		std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
	}

	GLuint fragmentShader;
	fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fragmentShader, 1, &fragment_shader, NULL);
	glCompileShader(fragmentShader);
	
	GLuint shaderProgram;
	shaderProgram = glCreateProgram();
	
	glAttachShader(shaderProgram, vertexShader);
	glAttachShader(shaderProgram, fragmentShader);
	glLinkProgram(shaderProgram);

	glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);
	if (!success)
	{
		glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
		std::cout << "ERROR: " << infoLog << std::endl;
	}

	// ��ʹ��glUseProgram֮��ÿ����ɫ�����ú���Ⱦ����ʹ������������
	glUseProgram(shaderProgram);

	// ɾ����ɫ�����󣬲�����Ҫ
	glDeleteShader(vertexShader);
	glDeleteShader(fragmentShader);
	
	GLuint VBO;
	glGenBuffers(1, &VBO);

	GLuint VBO2;
	glGenBuffers(1, &VBO2);

	GLuint VAO;
	glGenVertexArrays(1, &VAO);

	GLuint VAO2;
	glGenVertexArrays(1, &VAO2);

	GLuint EBO;
	glGenBuffers(1, &EBO);

	// ��VAO, �������VBO��������洢�����VAO�У�������ʹ��
	glBindVertexArray(VAO);

	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	// ��ʹ��λ��Ϊ0�Ķ�������
	glEnableVertexAttribArray(0);

	// ���VAO
	glBindVertexArray(0);

	glBindVertexArray(VAO2);
	
	glBindBuffer(GL_ARRAY_BUFFER, VBO);
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices_rect), vertices_rect, GL_STATIC_DRAW);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);
	glEnableVertexAttribArray(0);

	glBindVertexArray(0);
	

	while (!glfwWindowShouldClose(window))
	{
		// ����¼�
		glfwPollEvents();

		glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
		glClear(GL_COLOR_BUFFER_BIT);
			
		glUseProgram(shaderProgram);
		//glBindVertexArray(VAO);
		//glDrawArrays(GL_TRIANGLES, 0, 3);
		glBindVertexArray(VAO2);
		glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
		glBindVertexArray(0);


		// ��������
		glfwSwapBuffers(window);
	}

	glfwTerminate();
	return 0;
}