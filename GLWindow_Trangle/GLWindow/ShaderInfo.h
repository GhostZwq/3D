#ifndef SHADER_INFO
#define SHADER_INFO

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
	"out vec4 FragColor;                         \n"
	"uniform vec4 ourColor;                      \n"
	"void main()                                 \n"
	"{                                           \n"
	"    FragColor = ourColor;                   \n"
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