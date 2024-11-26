#include "Entity.h"

namespace breakout::entity {

Entity::Entity(util::Shader& shader_, const util::Texture& texture_)
    : shader(shader_), texture(texture_) {
  initRenderData();
}

Entity::Entity(util::Shader& shader_, const util::Texture& texture_, const glm::vec2& position_,
               const glm::vec2& size_, float rotation_, const glm::vec3& color_)
    : shader(shader_),
      texture(texture_),
      position(position_),
      size(size_),
      rotation(rotation_),
      color(color_) {
  initRenderData();
}

Entity::~Entity() {
  glDeleteVertexArrays(1, &vertexArrayObject);
}

void Entity::initRenderData() {
  unsigned int vertexBufferObjects;
  float vertices[] = {                         // pos.x, pos.y, tex.x, tex.y
                      0.0f, 1.0f, 0.0f, 1.0f,  //
                      1.0f, 0.0f, 1.0f, 0.0f,  //
                      0.0f, 0.0f, 0.0f, 0.0f,  //

                      0.0f, 1.0f, 0.0f, 1.0f,  //
                      1.0f, 1.0f, 1.0f, 1.0f,  //
                      1.0f, 0.0f, 1.0f, 0.0f};

  glGenVertexArrays(1, &vertexArrayObject);
  glGenBuffers(1, &vertexBufferObjects);

  glBindBuffer(GL_ARRAY_BUFFER, vertexBufferObjects);
  glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

  glBindVertexArray(vertexArrayObject);
  glEnableVertexAttribArray(0);
  glVertexAttribPointer(0, 4, GL_FLOAT, GL_FALSE, 4 * sizeof(float), (void*)0);
  glBindBuffer(GL_ARRAY_BUFFER, 0);
  glBindVertexArray(0);
}

void Entity::render() {
  shader.use();
  glm::mat4 model = glm::mat4(1.0f);

  model = glm::translate(model, glm::vec3(position - size * 0.5f, 0.0f));
  model = glm::rotate(model, glm::radians(rotation), glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::scale(model, glm::vec3(size, 1.0f));

  shader.setMatrix4("model", model);
  shader.setVector3f("spriteColor", color);

  texture.bind();

  glBindVertexArray(vertexArrayObject);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

}  // namespace breakout::entity