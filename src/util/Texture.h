#ifndef TEXTURE_H
#define TEXTURE_H

#include <glad/glad.h>

#include "Logs.h"

namespace breakout::util {

/**
 * A simple Texture class to store the texture width, height, image format, and other details
 */
class Texture {
 public:
  /**
   * Default Texture constructor defining a linearly repeating RGB texture
   */
  Texture();

  /**
   * Generates the OpenGL Texture from an image of a defined width and height
   * @param textureWidth The width of the generated texture
   * @param textureHeight The height of the generated texture
   * @param data The image data being loaded into the texture
   */
  void generate(unsigned int textureWidth, unsigned int textureHeight, unsigned char* data);

  /**
   * Binds the texture to the current OpenGL instance
   */
  void bind() const;

  /**
   * Assigns a new format mode for the internal and image formats
   * @param format The new format to override the original. Expects a variation of GL_RGB or GL_RGBA.
   */
  void setFormatMode(unsigned int format);

  /**
   * Deletes the current texture
   */
  void deleteTexture();

 private:
  unsigned int textureId;
  unsigned int width, height;
  unsigned int internalFormat, imageFormat;
  unsigned int wrapS, wrapT;
  unsigned int filterMin, filterMax;
};

}  // namespace breakout::util

#endif