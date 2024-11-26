#include "objects/Level.h"

#include "Config.h"

namespace breakout::objects {

Level::Level(util::Shader& shader, const char* filename, unsigned int levelWidth,
             unsigned int levelHeight) {
  glm::vec2 brickSize{SCREEN_WIDTH / levelWidth, SCREEN_HEIGHT / (2.0f * levelHeight)};
  glm::vec2 currentPosition = brickSize * 0.5f;

  std::ifstream level(RELATIVE_LEVEL_PATH.append(filename));
  std::string line;

  const auto& solidTexture = ResourceManager::GetTexture("solidBlock");
  const auto& blockTexture = ResourceManager::GetTexture("block");

  while (std::getline(level, line)) {
    for (char character : line) {
      if (character == ' ') {
        continue;
      }

      DEBUG("Position: " << currentPosition.x << ", " << currentPosition.y);
      entity::BrickType type = (entity::BrickType)(character - '0');
      entity::Brick brick{shader, type == entity::BrickType::SOLID ? solidTexture : blockTexture,
                          type, currentPosition, brickSize};
      bricks.emplace_back(brick);
      currentPosition.x += brickSize.x;
    }

    currentPosition.y += brickSize.y;
    currentPosition.x = brickSize.x * 0.5f;
  }
}

void Level::render() {
  for (auto& brick : bricks) {
    brick.render();
  }
}

bool Level::isCompleted() {
  return bricks.empty();
}

}  // namespace breakout::objects