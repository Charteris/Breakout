#include "Entity.h"

#include "Config.h"
#include "Constants.h"

namespace breakout::entity {

Entity::Entity(util::Shader& shader_, const util::Texture& tex) : shader(shader_), texture(tex) {
  initRenderData();
}

Entity::Entity(util::Shader& shader_, const util::Texture& tex, const Translation& trans,
               const glm::vec3& col)
    : shader(shader_), texture(tex), translation(trans), color(col) {
  initRenderData();
}

Entity::~Entity() {
  glDeleteVertexArrays(1, &vertexArrayObject);
}

glm::vec2 Entity::getNormalVector(const glm::vec2& relativePosition) const {
  glm::vec2 relativeDirection = relativePosition - translation.position, bestNormal;
  float max = 0.0f;
  for (unsigned int i = 0; i < 4; i++) {
    auto rotation = (translation.rotation + 90.0f * i) * DEGREES_TO_RADIANS;
    auto vector = glm::vec2(std::sin(rotation), std::cos(rotation));
    float dot_product = glm::dot(glm::normalize(relativeDirection), vector);

    DEBUG(vector << " " << dot_product << " " << max);
    if (dot_product > max) {
      max = dot_product;
      bestNormal = vector;
    }
  }
  return bestNormal;
}

void Entity::onCollision(const std::shared_ptr<Entity>& other) {
  if (translation.velocity.x != 0.0f || translation.velocity.y != 0.0f) {
    auto normalVector = other->getNormalVector(translation.position);
    auto surfaceVector = glm::normalize(translation.velocity + normalVector);
    translation.velocity = -glm::normalize(surfaceVector - normalVector);
    DEBUG(normalVector << " " << surfaceVector);
  }
}

void Entity::update(float deltaTime) {
  if (translation.velocity.x != 0.0f || translation.velocity.y != 0.0f) {
    if (bounds.lowerBounds.x < 0.0f || bounds.upperBounds.x > SCREEN_WIDTH) {
      translation.velocity.x *= -1;
    }

    if (bounds.lowerBounds.y < 0.0f || bounds.upperBounds.y > SCREEN_HEIGHT) {
      translation.velocity.y *= -1;
    }

    translation.position += translation.velocity * translation.speed * (deltaTime * 100.0f);
    bounds.lowerBounds = translation.position - translation.size * 0.5f;
    bounds.upperBounds = translation.position + translation.size * 0.5f;
  }
}

void Entity::render() {
  shader.use();
  glm::mat4 model = glm::mat4(1.0f);

  model = glm::translate(model, glm::vec3(translation.position - translation.size * 0.5f, 0.0f));
  model = glm::rotate(model, glm::radians(translation.rotation), glm::vec3(0.0f, 0.0f, 1.0f));
  model = glm::scale(model, glm::vec3(translation.size, 1.0f));

  shader.setMatrix4("model", model);
  shader.setVector3f("spriteColor", color);

  texture.bind();

  glBindVertexArray(vertexArrayObject);
  glDrawArrays(GL_TRIANGLES, 0, 6);
  glBindVertexArray(0);
}

void Entity::initRenderData() {
  id = generateUuid();
  bounds.lowerBounds = translation.position - translation.size * 0.5f;
  bounds.upperBounds = translation.position + translation.size * 0.5f;

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

}  // namespace breakout::entity