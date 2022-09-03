#include "Shader.h"

unsigned int Shader::LoadSourceAndCreateShader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath)
{
	const std::string vertexShaderSource = LoadSourceFromFile(vertexShaderPath);
	const std::string fragmentShaderSource = LoadSourceFromFile(fragmentShaderPath);

	unsigned int shader = CreateShader(vertexShaderSource, fragmentShaderSource);

	return shader;
}

unsigned int Shader::ParseSourceAndCreateShader(const std::string& shaderPath)
{
	ShaderProgramSource programSource = ParseShader(shaderPath);
	unsigned int shader = CreateShader(programSource.VertexSource, programSource.FragmentSource);

	return shader;
}

unsigned int Shader::CreateShader(const std::string& vertexShaderSrc, const std::string& fragmentShaderSrc)
{
	unsigned int program = glCreateProgram();
	unsigned int vs = CompileShader(GL_VERTEX_SHADER, vertexShaderSrc);
	unsigned int fs = CompileShader(GL_FRAGMENT_SHADER, fragmentShaderSrc);

	glAttachShader(program, vs);
	glAttachShader(program, fs);
	glLinkProgram(program);
	glValidateProgram(program);

	glDeleteShader(vs);
	glDeleteShader(fs);

	return program;
}

const std::string Shader::LoadSourceFromFile(const std::string& path)
{
	std::string text;
	std::ifstream fileStream(path, std::ios::in);

	if (fileStream.is_open() == false)
	{
		std::cout << "Could not read file with path: \"" << path << "\"." << std::endl;
		return "";
	}

	std::string line = "";
	while (fileStream.eof() == false)
	{
		std::getline(fileStream, line);
		text.append(line + "\n");
	}

	fileStream.close();
	return text;
}

ShaderProgramSource Shader::ParseShader(const std::string& filepath)
{
	std::ifstream stream(filepath);

	enum ShaderType
	{
		NONE = -1,
		VERTEX = 0,
		FRAGMENT = 1
	};

	std::string line;
	std::stringstream ss[2];
	ShaderType type = ShaderType::NONE;
	while (getline(stream, line))
	{
		if (line.find("#shader") != std::string::npos)
		{
			if (line.find("vertex") != std::string::npos)
			{
				type = ShaderType::VERTEX;
			}
			else if (line.find("fragment") != std::string::npos)
			{
				type = ShaderType::FRAGMENT;
			}
		}
		else
		{
			ss[(int)type] << line << '\n';
		}
	}

	return { ss[0].str(), ss[1].str() };
}

unsigned int Shader::CompileShader(unsigned int type, const std::string& source)
{
	unsigned int id = glCreateShader(type);
	const char* src = source.c_str();
	glShaderSource(id, 1, &src, nullptr);
	glCompileShader(id);

	int result;
	glGetShaderiv(id, GL_COMPILE_STATUS, &result);
	if (result == GL_FALSE)
	{
		int length;
		glGetShaderiv(id, GL_INFO_LOG_LENGTH, &length);
		char* message = (char*)alloca(length * sizeof(char));
		glGetShaderInfoLog(id, length, &length, message);
		std::cout << "Failed to compile" <<
			(type == GL_VERTEX_SHADER ? " vertex " : " fragment ")
			<< "shader." << std::endl;
		std::cout << message << std::endl;
		glDeleteShader(id);
		return 0;
	}

	return id;
}
