#ifndef STRUCTURES_H
#define STRUCTURES_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/trigonometric.hpp>

namespace breakout::entity {

/**
 * Overloads the stream operator to log debug information for a 2D vector
 * @param stream The output stream being written to
 * @param entity The entity being logged
 * @return The stream used to print the vector information
 */
inline std::ostream& operator<<(std::ostream& stream, const glm::vec2& vector) {
  return stream << "(" << vector.x << ", " << vector.y << ")";
}

/**
 * Provides a simple struct for storing translational information on an entity
 */
struct Translation {
  glm::vec2 position{0.0f, 0.0f}, velocity{0.0f, 0.0f}, size{1.0f, 1.0f};
  float rotation = 0.0f;
  float speed = 5.0f;

  Translation() {};
  Translation(const glm::vec2& pos, const glm::vec2& s) : position(pos), size(s) {};
  Translation(const glm::vec2& pos, const glm::vec2& vel, const glm::vec2& s, float rot)
      : position(pos), velocity(glm::normalize(vel)), size(s), rotation(rot) {};

  /**
   * Overloads the stream operator to log debug information for Translation info
   * @param stream The output stream being written to
   * @param translation The translation being logged
   * @return The stream used to print the translation information
   */
  inline friend std::ostream& operator<<(std::ostream& stream, const Translation& translation) {
    return stream << "[pos" << translation.position << ", size" << translation.size << "]";
  }
};

/**
 * Provides a simple struct for storing the rectangular bounds of an entity
 */
struct BoundingRectangle {
  glm::vec2 upperBounds{0.0f, 0.0f}, lowerBounds{0.0f, 0.0f};

  BoundingRectangle() {};
  BoundingRectangle(const glm::vec2& upper, const glm::vec2& lower)
      : upperBounds(upper), lowerBounds(lower) {};

  /**
   * Checks if the other rectangle intersects with this rectangle
   * @param other The other rectangle being bounds checked
   * @return True if the other rectangle intersects with this rectangle, false otherwise
   */
  bool intersects(const BoundingRectangle& other) const {
    return (lowerBounds.x <= other.lowerBounds.x && other.lowerBounds.x <= upperBounds.x &&
            lowerBounds.y <= other.lowerBounds.y && other.lowerBounds.y <= upperBounds.y) ||
           (lowerBounds.x <= other.upperBounds.x && other.lowerBounds.x <= upperBounds.x &&
            lowerBounds.y <= other.upperBounds.y && other.lowerBounds.y <= upperBounds.y);
  }

  /**
   * Overloads the stream operator to log debug information for a rectangle
   * @param stream The output stream being written to
   * @param rectangle The rectangle being logged
   * @return The stream used to print the rectangle information
   */
  inline friend std::ostream& operator<<(std::ostream& stream, const BoundingRectangle& rectangle) {
    return stream << "[lower" << rectangle.lowerBounds << " -> upper" << rectangle.upperBounds
                  << "]";
  }
};

}  // namespace breakout::entity

#endif