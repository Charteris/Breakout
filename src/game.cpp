#include "Game.h"

namespace breakout {

Game::Game(unsigned int width, unsigned int height)
    : state(ACTIVE), keys(), screenWidth(width), screenHeight(height) {}

Game::~Game() {}

void Game::init() {
  ResourceManager::LoadShader("sprite", "sprite.vs", "sprite.fs");
  glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(screenWidth),
                                    static_cast<float>(screenHeight), 0.0f, -1.0f, 1.0f);

  auto& spriteShader = ResourceManager::GetShader("sprite").use();
  spriteShader.setInteger("image", 0);
  spriteShader.setMatrix4("projection", projection);

  const auto& ballTexture = ResourceManager::LoadTexture("ball", "Ball.png", true);
  const auto& paddleTexture = ResourceManager::LoadTexture("paddle", "Paddle.png", true);
  ResourceManager::LoadTexture("block", "Block.png", false);
  ResourceManager::LoadTexture("solidBlock", "SolidBlock.png", false);

  activeLevel = std::make_shared<objects::Level>(spriteShader, objects::Levels.at(0));

  auto ballTranslation = entity::Translation({screenWidth / 2.0f, screenHeight * 3.0f / 4.0f},
                                             {0.75f, 1.0f}, {25.0f, 25.0f}, 0.0f);
  entityRegister.insert(
      {"ball", std::make_shared<entity::Entity>(spriteShader, ballTexture, ballTranslation,
                                                glm::vec3(0.0f, 1.0f, 0.0f))});

  auto paddleTranslation =
      entity::Translation({screenWidth / 2.0f, screenHeight * 4.5f / 5.0f}, {150.0f, 30.0f});
  entityRegister.insert(
      {"paddle", std::make_shared<entity::Entity>(spriteShader, paddleTexture, paddleTranslation,
                                                  glm::vec3(0.0f, 0.0f, 1.0f))});
}

void Game::update(float deltaTime) {
  std::string prevEntity = "";
  for (auto& [key, entity] : entityRegister) {
    if (activeLevel->handleCollisions(entity)) {
      break;
    }

    if (prevEntity != "" && checkEntityCollision(entity, entityRegister.at(prevEntity))) {
      break;
    }
    prevEntity = key;
  }

  for (auto& [key, entity] : entityRegister) {
    entity->update(deltaTime);
  }
}

void Game::processInput(float deltaTime) {}

void Game::render() {
  activeLevel->render();
  for (auto& [_, entity] : entityRegister) {
    entity->render();
  }
}

bool Game::checkEntityCollision(const std::shared_ptr<entity::Entity>& entityA,
                                const std::shared_ptr<entity::Entity>& entityB) {
  if (entityA->getId() == entityB->getId()) {
    return false;
  }

  if (entityA->getBounds().intersects(entityB->getBounds())) {
    DEBUG(*entityA << " collided with " << *entityB);
    entityA->onCollision(entityB);
    entityB->onCollision(entityA);
    return true;
  }
  return false;
}

}  // namespace breakout