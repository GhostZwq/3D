
#ifndef VERTEX_INFO_H
#define VERTEX_INFO_H

#include <gl\glew.h>

GLfloat vertices[] = {
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


#endif