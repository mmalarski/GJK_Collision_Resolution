#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 color;

out vec3 vertexColor;

uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * vec4(position, 1.0);
	vertexColor = color;
}

#shader fragment
#version 330 core

in vec3 vertexColor;

out vec4 color;

void main()
{
	color = vec4(vertexColor, 1.0);
}
