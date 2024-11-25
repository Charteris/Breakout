#include "Texture.h"

namespace breakout::util {

Texture::Texture()
    : width(0),
      height(0),
      internalFormat(GL_RGB),
      imageFormat(GL_RGB),
      wrapS(GL_REPEAT),
      wrapT(GL_REPEAT),
      filterMin(GL_LINEAR),
      filterMax(GL_LINEAR) {
  glGenTextures(1, &textureId);
}

void Texture::generate(unsigned int textureWidth, unsigned int textureHeight, unsigned char* data) {
  width = textureWidth;
  height = textureHeight;

  // create Texture
  glBindTexture(GL_TEXTURE_2D, textureId);
  glTexImage2D(GL_TEXTURE_2D, 0, internalFormat, width, height, 0, imageFormat, GL_UNSIGNED_BYTE,
               data);

  // set Texture wrap and filter modes
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, wrapS);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, wrapT);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, filterMin);
  glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, filterMax);

  // unbind texture
  glBindTexture(GL_TEXTURE_2D, 0);
}

void Texture::bind() const {
  glActiveTexture(GL_TEXTURE0);
  glBindTexture(GL_TEXTURE_2D, textureId);
}

void Texture::setFormatMode(unsigned int format) {
  internalFormat = format;
  imageFormat = format;
}

void Texture::deleteTexture() {
  glDeleteTextures(1, &textureId);
}

}  // namespace breakout::util