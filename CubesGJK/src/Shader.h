#pragma once

#include <GL/glew.h>
#include <string>
#include <sstream>
#include <fstream>
#include <iostream>

struct ShaderProgramSource
{
	std::string VertexSource;
	std::string FragmentSource;
};

class Shader
{
public:
	static unsigned int LoadSourceAndCreateShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
	static unsigned int ParseSourceAndCreateShader(const std::string& shaderPath);
	static unsigned int CreateShader(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc);
	static const std::string LoadSourceFromFile(const std::string& path);
	static ShaderProgramSource ParseShader(const std::string& filepath);
private:
	static unsigned int CompileShader(unsigned int type, const std::string& source);
};

