#ifndef ENTITY_H
#define ENTITY_H

#define GLFW_INCLUDE_GLCOREARB

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

#include <cmath>
#include <memory>

#include "ResourceManager.h"
#include "entity/Structures.h"
#include "util/Shader.h"
#include "util/Texture.h"

namespace breakout::entity {

/**
 * Creates a renderable and translational game entity
 */
class Entity {
 public:
  Entity(util::Shader& shader_, const util::Texture& tex);

  /**
   * Constructs a new entity
   * @param shader_ The shader used to render the entity
   * @param tex The texture to be rendered for the entity
   * @param trans The initial translational data for the entity
   * @param col The colour tint applied to the entity. Default: WHITE
   */
  Entity(util::Shader& shader_, const util::Texture& tex, const Translation& trans,
         const glm::vec3& col = glm::vec3(1.0f, 1.0f, 1.0f));

  /**
   * Default destructor - deletes the vertex array
   */
  ~Entity();

  /**
   * Gets the entities unique identifier
   * @return A const reference the entities ID
   */
  const std::string& getId() const { return id; }

  /**
   * Gets the bounding rectangle of the entity
   * @return A const reference to the entities bounds
   */
  const BoundingRectangle& getBounds() const { return bounds; }

  /**
   * Gets the current position of the entity
   * @return A const reference to the entities position
   */
  const glm::vec2& getPosition() const { return translation.position; }

  /**
   * Gets the current size of the entity
   * @return A const reference to the entities size
   */
  const glm::vec2& getSize() const { return translation.size; }

  /**
   * Gets the 2D normal vector of the Entities bounding rectangle from a surface
   * @return A const reference to the entities normal vector from a surface
   */
  glm::vec2 getNormalVector(const glm::vec2& relativePosition) const;

  /**
   * Performs certain actions when this entity collides with another
   * @param other A shared pointer to the other entity that this collided against
   */
  void onCollision(const std::shared_ptr<Entity>& other);

  /**
   * Updates the entity
   * @param deltaTime The delta time between frames in seconds
   */
  void update(float deltaTime);

  /**
   * Renders the entity
   */
  void render();

  /**
   * Overloads the stream operator to log debug information for the entity
   * @param stream The output stream being written to
   * @param entity The entity being logged
   * @return The stream used to print the entity information
   */
  inline friend std::ostream& operator<<(std::ostream& stream, const Entity& entity) {
    return stream << "<" << entity.id.substr(0, 8) << entity.translation << ">";
  }

 protected:
  std::string id;
  util::Shader shader;
  const util::Texture& texture;

  Translation translation;
  BoundingRectangle bounds;

  glm::vec3 color = glm::vec3(1.0f);
  unsigned int vertexArrayObject;

  /**
   * Configures the vertex array object and all vertex buffer objects 
   */
  void initRenderData();
};

}  // namespace breakout::entity

#endif