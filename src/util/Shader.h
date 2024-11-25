#ifndef SHADER_H
#define SHADER_H

#include <exception>
#include <string>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Logs.h"

namespace breakout::util {

/**
 * A simple Shader class which instantiates OpenGL Shaders from GLSL source code
 */
class Shader {
 public:
  /**
   * Default constructor
   */
  Shader() {};

  /**
   * Constructs a Shader whilst compiling its shader program
   * @param vertexSource The GLSL source code for the vertex shader
   * @param fragmentSource The GLSL source code for the fragment shader
   * @param geometrySource The GLSL source code for the geometry shader
   */
  Shader(const char* vertexSource, const char* fragmentSource,
         const char* geometrySource = nullptr);

  /**
   * Instructs OpenGL to use the shader program referenced by this object
   * @return A reference to the current shader object instance being used
   */
  Shader& use();

  /**
   * Compiles a shader program on the current Shader based on provided GLSL source code
   * @param vertexSource The GLSL source code for the vertex shader
   * @param fragmentSource The GLSL source code for the fragment shader
   * @param geometrySource The GLSL source code for the geometry shader
   */
  void compile(const char* vertexSource, const char* fragmentSource,
               const char* geometrySource = nullptr);

  /**
   * Sets a uniform int variable in the current shader program defined through the GLSL source code
   * @param varName The name of the uniform int variable being updated
   * @param value The value to assign to the uniform int variable
   */
  void setInteger(const char* varName, int value);

  /**
   * Sets a uniform float variable in the current shader program defined through the GLSL source code
   * @param varName The name of the uniform float variable being updated
   * @param value The value to assign to the uniform float variable
   */
  void setFloat(const char* varName, float value);

  /**
   * Sets a uniform 2D vector variable in the current shader program defined through the GLSL source code
   * @param varName The name of the uniform 2D vector variable being updated
   * @param value The value to assign to the uniform 2D vector variable
   */
  void setVector2f(const char* varName, const glm::vec2& value);

  /**
   * Sets a uniform 3D vector variable in the current shader program defined through the GLSL source code
   * @param varName The name of the uniform 3D vector variable being updated
   * @param value The value to assign to the uniform 3D vector variable
   */
  void setVector3f(const char* varName, const glm::vec3& value);

  /**
   * Sets a uniform 4D vector variable in the current shader program defined through the GLSL source code
   * @param varName The name of the uniform 4D vector variable being updated
   * @param value The value to assign to the uniform 4D vector variable
   */
  void setVector4f(const char* varName, const glm::vec4& value);

  /**
   * Sets a uniform 4D matrix variable in the current shader program defined through the GLSL source code
   * @param varName The name of the uniform  4D matrix variable being updated
   * @param value The value to assign to the uniform  4D matrix variable
   */
  void setMatrix4(const char* varName, const glm::mat4& value);

  /**
   * Deletes the current shader program
   */
  void deleteShader();

 private:
  unsigned int shaderId;

  /**
   * Validates whether a shader has been successfully instantiated without errors
   * @param shader The OpenGL Shader to be validated against
   * @param status The OpenGL status expected for the applicable Shader.
   * Expects GL_COMPILE_STATUS for shader constituents or GL_LINK_STATUS for the linked shader program.
   * Defaults to GL_COMPILE_STATUS.
   * @throw std::logic_error if the Shader failed to initialise properly
   */
  void validateShader(GLuint shader, GLenum status = GL_COMPILE_STATUS) const;

  /**
   * @brief Creates an OpenGL Shader constituent of a given type
   * @param shaderType The type of shader being created. Expects GL_VERTEX_SHADER, 
   * GL_FRAGMENT_SHADER or GL_GEOMETRY_SHADER respectively.
   * @param source The GLSL source code for the given shader being instantiated
   * @return An ID to reference the instantiated OpenGL shader
   */
  unsigned int createShader(GLenum shaderType, const char* source) const;
};

}  // namespace breakout::util

#endif