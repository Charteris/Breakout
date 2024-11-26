#ifndef BRICK_H
#define BRICK_H

#include <vector>

#include "entity/Entity.h"

#define RELATIVE_LEVEL_PATH std::string("../res/levels/")

namespace breakout::entity {

enum BrickType { SOLID, BLUE, GREEN, YELLOW, ORANGE, RED };

const static std::map<BrickType, glm::vec3> BrickColor{
    {BrickType::SOLID, glm::vec3(1.0f, 1.0f, 1.0f)},
    {BrickType::BLUE, glm::vec3(0.0f, 0.0f, 0.75f)},
    {BrickType::GREEN, glm::vec3(0.0f, 0.75f, 0.0f)},
    {BrickType::YELLOW, glm::vec3(0.5f, 0.5f, 0.0f)},
    {BrickType::ORANGE, glm::vec3(0.75f, 0.25f, 0.0f)},
    {BrickType::RED, glm::vec3(0.75f, 0.0f, 0.0f)}};

class Brick : public Entity {
 public:
  Brick(util::Shader& shader_, const util::Texture& texture_, const BrickType& brickType,
        const glm::vec2& position_, const glm::vec2& size_);

 private:
  BrickType type;
};

}  // namespace breakout::entity

#endif