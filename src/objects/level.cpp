#include "objects/Level.h"

#include "Config.h"

namespace breakout::objects {

Level::Level(util::Shader& shader, const LevelConfig& config) {
  glm::vec2 brickSize{SCREEN_WIDTH / config.width, SCREEN_HEIGHT / (2.0f * config.height)};
  glm::vec2 currentPosition = brickSize * 0.5f;

  std::ifstream level(RELATIVE_LEVEL_PATH.append(config.name));
  std::string line;

  const auto& solidTexture = ResourceManager::GetTexture("solidBlock");
  const auto& blockTexture = ResourceManager::GetTexture("block");

  while (std::getline(level, line)) {
    for (char character : line) {
      if (character == ' ') {
        continue;
      }

      entity::BrickType type = (entity::BrickType)(character - '0');
      auto brick = std::make_shared<entity::Brick>(
          shader, type == entity::BrickType::SOLID ? solidTexture : blockTexture, type,
          currentPosition, brickSize);
      bricks.emplace_back(brick);
      currentPosition.x += brickSize.x;
    }

    currentPosition.y += brickSize.y;
    currentPosition.x = brickSize.x * 0.5f;
  }
}

bool Level::handleCollisions(const std::shared_ptr<entity::Entity>& entity) {
  for (auto& brick : bricks) {
    if (entity->getBounds().intersects(brick->getBounds())) {
      DEBUG(*entity << " collided with " << *brick);
      entity->onCollision(brick);
      brick->onCollision(entity);
      return true;
    }
  }
  return false;
}

void Level::render() {
  for (auto& brick : bricks) {
    brick->render();
  }
}

bool Level::isCompleted() {
  return bricks.empty();
}

}  // namespace breakout::objects