#shader vertex
#version 330 core

layout(location = 0) in vec3 position;
layout(location = 1) in vec3 normal;

out vec3 normal_;
out vec3 fragmentPosition;

uniform mat4 model;
uniform mat4 view;
uniform mat4 projection;

void main()
{
	gl_Position = projection * view * model * vec4(position, 1.0);
	normal_ = normal;
	fragmentPosition = vec3(model * vec4(position, 1.0f));
}

#shader fragment
#version 330 core

in vec3 normal_;
in vec3 fragmentPosition;

out vec4 color;

uniform vec4 u_Color;

#define NR_POINT_LIGHTS 2
uniform vec3 pointLights[NR_POINT_LIGHTS];

void main()
{
	vec4 result = vec4(0.0);
	for (int i = 0; i < NR_POINT_LIGHTS; i++)
	{
		vec3 norm = normalize(normal_);
		vec3 lightDirection = normalize(pointLights[i] - fragmentPosition);
		float diffuse = max(dot(norm, lightDirection), 0.3);
		result += u_Color * diffuse;
	}
	color = result;
}
