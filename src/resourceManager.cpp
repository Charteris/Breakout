#include "ResourceManager.h"

namespace breakout {

std::map<std::string, util::Shader> ResourceManager::Shaders;
std::map<std::string, util::Texture> ResourceManager::Textures;

std::string ResourceManager::readShaderCode(const char* filename) {
  std::string resourcePath = RELATIVE_SHADER_PATH.append(filename);
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
  bool usingGeometryShader = (geometryShaderFilename != nullptr);

  try {
    vertexCode = readShaderCode(vertexShaderFilename);
    fragmentCode = readShaderCode(fragmentShaderFilename);
    if (usingGeometryShader) {
      geometryCode = readShaderCode(geometryShaderFilename);
    }

  } catch (std::ifstream::failure e) {
    ERROR("Failed to read shader program(s): " << vertexShaderFilename << ", "
                                               << fragmentShaderFilename << ", "
                                               << geometryShaderFilename);
  }

  util::Shader shader;
  shader.compile(vertexCode.c_str(), fragmentCode.c_str(),
                 usingGeometryShader ? geometryCode.c_str() : nullptr);
  return shader;
}

util::Texture ResourceManager::loadTextureFromFile(const char* filename, bool alpha) {
  util::Texture texture;
  if (alpha) {
    texture.setFormatMode(GL_RGBA);
  }

  int width, height, channels;
  std::string texturePath = RELATIVE_TEXTURE_PATH.append(filename);
  unsigned char* data = stbi_load(texturePath.c_str(), &width, &height, &channels, 0);

  if (data == NULL) {
    std::string stbiError = std::string("STBI failed to load texture").append(texturePath);
    ERROR(stbiError);
    throw std::domain_error(stbiError);
  }

  DEBUG("Loaded texture " << texturePath << ": " << width << " " << height << " " << channels);
  texture.generate(width, height, data);
  stbi_image_free(data);
  return texture;
}

util::Shader ResourceManager::LoadShader(std::string shaderName, const char* vertexShaderFilename,
                                         const char* fragmentShaderFilename,
                                         const char* geometryShaderFilename) {
  Shaders[shaderName] =
      loadShaderFromFile(vertexShaderFilename, fragmentShaderFilename, geometryShaderFilename);
  return Shaders[shaderName];
}

util::Shader ResourceManager::GetShader(std::string shaderName) {
  return Shaders[shaderName];
}

const util::Texture& ResourceManager::LoadTexture(std::string textureName, const char* textureFile,
                                                  bool alpha) {
  Textures[textureName] = loadTextureFromFile(textureFile, alpha);
  return Textures[textureName];
}

const util::Texture& ResourceManager::GetTexture(std::string textureName) {
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