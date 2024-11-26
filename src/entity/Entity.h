#ifndef ENTITY_H
#define ENTITY_H

#define GLFW_INCLUDE_GLCOREARB

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "ResourceManager.h"
#include "util/Shader.h"
#include "util/Texture.h"

namespace breakout::entity {

class Entity {
 public:
  Entity(util::Shader& shader_, const util::Texture& texture_);
  Entity(util::Shader& shader_, const util::Texture& texture_, const glm::vec2& position_,
         const glm::vec2& size_, float rotation_, const glm::vec3& color_);
  ~Entity();

  void render();

 protected:
  util::Shader shader;
  const util::Texture& texture;

  glm::vec2 position = glm::vec2(0.0f, 0.0f);
  glm::vec2 size = glm::vec2(10.0f, 10.0f);
  glm::vec3 color = glm::vec3(1.0f);
  float rotation = 0.0f;

  unsigned int vertexArrayObject;

  /**
   * Configures the vertex array object and all vertex buffer objects 
   */
  void initRenderData();
};

}  // namespace breakout::entity

#endif