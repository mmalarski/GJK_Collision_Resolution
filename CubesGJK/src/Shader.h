#pragma once

#include <GL/glew.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>
#include <glm/glm.hpp>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:
	Shader(const std::string& path);
	~Shader();
	unsigned int ParseSourceAndCreateShader(const std::string& shaderPath);
	unsigned int CreateShader(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc);
	ShaderProgramSource ParseShader(const std::string& filepath);
	Shader& Use();
	Shader& SetUniform(const std::string& name, const glm::vec4& value);
private:
	GLuint id;
	unsigned int CompileShader(unsigned int type, const std::string& source);
};

