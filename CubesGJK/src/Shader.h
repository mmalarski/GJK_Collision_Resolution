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
  Shader(const std::string &path);
  ~Shader();
  GLuint parseSourceAndCreateShader(const std::string &shaderPath);
  GLuint createShader(const std::string &vertexShaderSrc, const std::string &fragmentShaderSrc);
  ShaderProgramSource ParseShader(const std::string &filepath);
  Shader &use();
  Shader &setUniform(const std::string &name, const glm::vec3 &value);
  Shader &setUniform(const std::string &name, const glm::vec4 &value);
  Shader &setUniform(const std::string &name, const glm::mat4 &value);
  static void setViewAndProjection(const glm::mat4 &view, const glm::mat4 &projection);
  static const glm::mat4 getViewMatrix();
  static const glm::mat4 getProjectionMatrix();

private:
  GLuint id;
  static glm::mat4 view;
  static glm::mat4 projection;
  GLuint compileShader(unsigned int type, const std::string &source);
};
