#include "entity/Brick.h"

namespace breakout::entity {

Brick::Brick(util::Shader& shader_, const util::Texture& texture_, const BrickType& brickType,
             const glm::vec2& position_, const glm::vec2& size_)
    : type(brickType),
      Entity(shader_, texture_, position_, size_, 0.0f, BrickColor.at(brickType)) {}

}  // namespace breakout::entity