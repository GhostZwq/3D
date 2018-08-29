
#ifndef VERTEX_INFO_H
#define VERTEX_INFO_H

#include <gl\glew.h>

GLfloat vertices_1[] = {
	-0.5f, -0.5f, 0.0f,
	0.5f, -0.5f, 0.0f,
	0.0f, 0.5f, 0.0f
};

GLfloat vertices_two_triangle[] = {
	-0.3f, 0.2f, 0.0f,
	0.0f, -0.4f, 0.0f,
	0.0f, 0.2f, 0.0f,
	0.0f, -0.4f, 0.0f,
	0.0f, 0.2f, 0.0f,
	0.8f, -0.2f, 0.0f
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

float vertices[] = {
	// 位置            // 颜色
	0.5f, -0.5f, 0.0f, 1.0f, 0.0f, 0.0f,       // 右下
	-0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f,      // 左下 
	0.0f, 0.5f, 0.0f, 0.0f, 0.0f, 1.0f         // 顶部
};


#endif