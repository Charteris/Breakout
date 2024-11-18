#include "ResourceManager.h"

namespace breakout {

std::map<std::string, util::Shader> ResourceManager::Shaders;
std::map<std::string, util::Texture> ResourceManager::Textures;

std::string ResourceManager::readShaderCode(const char* filename) {
  char resourcePath[BUFFER_SIZE] = "";
  sprintf(resourcePath, "%S%s\0", RELATIVE_SHADER_PATH, filename);
  std::ifstream resourceStream(resourcePath);
  resourceStream.exceptions(std::ifstream::failbit | std::ifstream::badbit);

  std::stringstream shaderStream;
  shaderStream << resourceStream.rdbuf();
  resourceStream.close();
  return shaderStream.str();
}

util::Shader ResourceManager::loadShaderFromFile(const char* vertexShaderFilename,
                                                 const char* fragmentShaderFilename,
                                                 const char* geometryShaderFilename) {
  std::string vertexCode, fragmentCode, geometryCode;
  bool isLoadedWithGeometryShader = (geometryShaderFilename != nullptr);

  try {
    vertexCode = readShaderCode(vertexShaderFilename);
    fragmentCode = readShaderCode(fragmentShaderFilename);
    if (isLoadedWithGeometryShader) {
      geometryCode = readShaderCode(geometryShaderFilename);
    }

  } catch (std::ifstream::failure e) {
    ERROR("Failed to read shader program(s): " << vertexShaderFilename << ", "
                                               << fragmentShaderFilename << ", "
                                               << geometryShaderFilename);
  }

  util::Shader shader;
  shader.compile(vertexCode.c_str(), fragmentCode.c_str(),
                 isLoadedWithGeometryShader ? geometryCode.c_str() : nullptr);
  return shader;
}

util::Texture ResourceManager::loadTextureFromFile(const char* filename, bool alpha) {
  util::Texture texture;
  if (alpha) {
    texture.setFormatMode(GL_RGBA);
  }

  int width, height, channels;
  char texturePath[BUFFER_SIZE] = "";
  sprintf(texturePath, "%S%s\0", RELATIVE_TEXTURE_PATH, filename);
  unsigned char* data = stbi_load(texturePath, &width, &height, &channels, 0);

  texture.generate(width, height, data);
  stbi_image_free(data);
  return texture;
}

util::Shader& ResourceManager::LoadShader(std::string shaderName, const char* vertexShaderFilename,
                                          const char* fragmentShaderFilename,
                                          const char* geometryShaderFilename) {
  Shaders[shaderName] =
      loadShaderFromFile(vertexShaderFilename, fragmentShaderFilename, geometryShaderFilename);
  return Shaders[shaderName];
}

util::Shader& ResourceManager::GetShader(std::string shaderName) {
  return Shaders[shaderName];
}

util::Texture& ResourceManager::LoadTexture(std::string textureName, const char* textureFile,
                                            bool alpha) {
  Textures[textureName] = loadTextureFromFile(textureFile, alpha);
  return Textures[textureName];
}

util::Texture& ResourceManager::GetTexture(std::string textureName) {
  return Textures[textureName];
}

void ResourceManager::ClearResources() {
  for (auto& [_, shader] : Shaders) {
    shader.deleteShader();
  }

  for (auto& [_, texture] : Textures) {
    texture.deleteTexture();
  }
}

}  // namespace breakout