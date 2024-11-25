#include "Shader.h"

namespace breakout::util {

void Shader::validateShader(GLuint shader, GLenum status) const {
  int success;
  char infoLog[512];
  glGetShaderiv(shader, status, &success);
  if (!success) {
    glGetShaderInfoLog(shader, 512, NULL, infoLog);
    std::string errorMessage{"Shader failed to initialise with error:\n"};
    errorMessage = errorMessage.append(infoLog);
    ERROR(errorMessage);
    throw std::logic_error(errorMessage);
  }
}

unsigned int Shader::createShader(GLenum shaderType, const char* source) const {
  unsigned int shaderPart = glCreateShader(shaderType);
  glShaderSource(shaderPart, 1, &source, NULL);
  glCompileShader(shaderPart);
  validateShader(shaderPart);
  return shaderPart;
}

Shader::Shader(const char* vertexSource, const char* fragmentSource, const char* geometrySource) {
  compile(vertexSource, fragmentSource, geometrySource);
}

Shader& Shader::use() {
  glUseProgram(shaderId);
  return *this;
}

void Shader::compile(const char* vertexSource, const char* fragmentSource,
                     const char* geometrySource) {
  unsigned int vertexShader, fragmentShader, geometryShader;
  vertexShader = createShader(GL_VERTEX_SHADER, vertexSource);
  fragmentShader = createShader(GL_FRAGMENT_SHADER, fragmentSource);
  if (geometrySource != nullptr) {
    geometryShader = createShader(GL_GEOMETRY_SHADER, geometrySource);
  }
  DEBUG("Shader constituents initialised");

  shaderId = glCreateProgram();
  glAttachShader(shaderId, vertexShader);
  glAttachShader(shaderId, fragmentShader);
  if (geometrySource != nullptr) {
    glAttachShader(shaderId, geometryShader);
  }
  glLinkProgram(shaderId);
  validateShader(shaderId, GL_LINK_STATUS);
  DEBUG("Shader program initialised");

  glDeleteShader(vertexShader);
  glDeleteShader(fragmentShader);
  if (geometrySource != nullptr) {
    glDeleteShader(geometryShader);
  }
}

void Shader::setInteger(const char* varName, int value) {
  glUniform1f(glGetUniformLocation(shaderId, varName), value);
}

void Shader::setFloat(const char* varName, float value) {
  glUniform1f(glGetUniformLocation(shaderId, varName), value);
}

void Shader::setVector2f(const char* varName, const glm::vec2& value) {
  glUniform2fv(glGetUniformLocation(shaderId, varName), 1, glm::value_ptr(value));
}

void Shader::setVector3f(const char* varName, const glm::vec3& value) {
  glUniform3fv(glGetUniformLocation(shaderId, varName), 1, glm::value_ptr(value));
}

void Shader::setVector4f(const char* varName, const glm::vec4& value) {
  glUniform4fv(glGetUniformLocation(shaderId, varName), 1, glm::value_ptr(value));
}

void Shader::setMatrix4(const char* varName, const glm::mat4& value) {
  glUniformMatrix4fv(glGetUniformLocation(shaderId, varName), 1, false, glm::value_ptr(value));
}

void Shader::deleteShader() {
  glDeleteProgram(shaderId);
}

}  // namespace breakout::util