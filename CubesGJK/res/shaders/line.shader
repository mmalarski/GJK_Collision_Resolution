#shader vertex
#version 330 core

layout(location = 0) in vec3 position;

out vec3 fragmentPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	fragmentPosition = vec3(model * vec4(position, 1.0f));
}

#shader fragment
#version 330 core

in vec3 fragmentPosition;

out vec4 color;

uniform vec4 u_Color;

void main()
{
	color = u_Color;
}
