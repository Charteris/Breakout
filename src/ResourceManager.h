#ifndef RESOURCE_MANAGER_H
#define RESOURCE_MANAGER_H

#include <fstream>
#include <iostream>
#include <map>
#include <sstream>
#include <string>

#include <glad/glad.h>

#include "stb_image.h"

#include "util/Shader.h"
#include "util/Texture.h"

#define BUFFER_SIZE 200
#define RELATIVE_SHADER_PATH std::string("../res/shaders/")
#define RELATIVE_TEXTURE_PATH std::string("../res/textures/")

namespace breakout {

/**
 * Singleton to manage and cache all shaders and textures used throughout the game
 */
class ResourceManager {
 public:
  /**
   * Loads and caches a Shader from its constituent files
   * @param vertexShaderFilename The name of the GLSL vertex shader code file
   * @param fragmentShaderFilename The name of the GLSL fragment shader code file
   * @param geometryShaderFilename The name of the GLSL geometry shader code file
   * @return A copy of the newly created Shader
   */
  static util::Shader& LoadShader(std::string shaderName, const char* vertexShaderFilename,
                                  const char* fragmentShaderFilename,
                                  const char* geometryShaderFilename = nullptr);

  /**
   * Returns a cached Shader instance
   * @param shaderName The name of the Shader being accessed
   * @return A copy of the cached Shader instance
   */
  static util::Shader& GetShader(std::string shaderName);

  /**
   * Loads and caches a Texture from its file
   * @param filename The name of the texture file
   * @param alpha True if the texture should contain alpha values, otherwise false
   * @return A const reference to the newly created Texture
   */
  static const util::Texture& LoadTexture(std::string textureName, const char* textureFile,
                                          bool alpha);

  /**
   * Returns a cached Texture instance
   * @param textureName The name of the Texture being accessed
   * @return A const reference to the cached Texture instance
   */
  static const util::Texture& GetTexture(std::string textureName);

  /**
   * Deletes all Shaders and Textures from the cache
   */
  static void ClearResources();

 private:
  static std::map<std::string, util::Shader> Shaders;
  static std::map<std::string, util::Texture> Textures;

  /**
   * Private constructor to instantiate static Resource Manager instance
   */
  ResourceManager() {};

  /**
   * Reads a complete GLSL shader code file constituent
   * @param filename The name of the shader file being opened
   * @return A string capturing the contents of the GLSL shader code
   */
  static std::string readShaderCode(const char* filename);

  /**
   * Loads a Shader from its constituent files
   * @param vertexShaderFilename The name of the GLSL vertex shader code file
   * @param fragmentShaderFilename The name of the GLSL fragment shader code file
   * @param geometryShaderFilename The name of the GLSL geometry shader code file
   * @return A newly created Shader
   */
  static util::Shader loadShaderFromFile(const char* vertexShaderFilename,
                                         const char* fragmentShaderFilename,
                                         const char* geometryShaderFilename = nullptr);

  /**
   * Loads a Texture from its file
   * @param filename The name of the texture file
   * @param alpha True if the texture should contain alpha values, otherwise false
   * @return A newly created Texture
   */
  static util::Texture loadTextureFromFile(const char* filename, bool alpha);
};

}  // namespace breakout

#endif