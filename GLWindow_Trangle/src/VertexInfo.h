
#ifndef VERTEX_INFO_H
#define VERTEX_INFO_H

#include <gl\glew.h>

float vertices_texture[] = {
	// λ��               ��ɫ                 ��������
	 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.55f, 0.55f,  // ���� 
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.55f, 0.45f,  // ����
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.45f, 0.45f,  // ����
	-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.45f, 0.55f   // ����
};

unsigned int indices_texture[] = {
	0, 1, 3,
	1, 2, 3
};


#endif