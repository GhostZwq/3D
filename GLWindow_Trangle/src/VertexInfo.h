
#ifndef VERTEX_INFO_H
#define VERTEX_INFO_H

#include <gl\glew.h>

float vertices_texture[] = {
	// 位置               颜色                 纹理坐标
	 0.5f,  0.5f, 0.0f, 1.0f, 0.0f, 0.0f, 0.55f, 0.55f,  // 右上 
	 0.5f, -0.5f, 0.0f, 0.0f, 1.0f, 0.0f, 0.55f, 0.45f,  // 右下
	-0.5f, -0.5f, 0.0f, 0.0f, 0.0f, 1.0f, 0.45f, 0.45f,  // 左下
	-0.5f,  0.5f, 0.0f, 1.0f, 1.0f, 0.0f, 0.45f, 0.55f   // 左上
};

unsigned int indices_texture[] = {
	0, 1, 3,
	1, 2, 3
};


#endif