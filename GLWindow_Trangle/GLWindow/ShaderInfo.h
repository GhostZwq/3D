#ifndef SHADER_INFO
#define SHADER_INFO

char* vertex_shader = {
	"#version 330 core                           \n"
	"layout (location = 0) in vec3 aPos;         \n"
	"layout (location = 1) in vec3 aColor;       \n"
	"                                            \n"
	"out vec3 ourColor;                           \n"
	"                                            \n"
	"void main()                                 \n"
	"{                                           \n"
	"    gl_Position = vec4(aPos, 1.0);          \n"
	"    ourColor = aColor;                      \n"
	"}                                           \n"
};

char* fragment_shader = {
	"#version 330 core                           \n"
	"out vec4 FragColor;                         \n"
	"in vec3 ourColor;                           \n"
	"void main()                                 \n"
	"{                                           \n"
	"    FragColor = vec4(ourColor, 1.0);        \n"
	"}"
};

char* vertex_shader_yellow = {
	"#version 330 core                           \n"
	"layout (location = 0) in vec3 position;     \n"
	"                                            \n"
	"void main()                                 \n"
	"{                                           \n"
	"    gl_Position = vec4(position.x, position.y, position.z, 1.0); \n"
	"}                                           \n"
};

char* fragment_shader_yellow = {
	"#version 330 core                           \n"
	"out vec4 color;                             \n"
	"void main()                                 \n"
	"{                                           \n"
	"    color = vec4(1.0f, 1.0f, 0.0f, 1.0f);   \n"
	"}"
};

#endif