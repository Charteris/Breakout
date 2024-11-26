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

  levels.emplace_back(std::make_shared<objects::Level>(spriteShader, "Level1.csv", 10, 10));

  entityRegister.insert({"ball", std::make_shared<entity::Entity>(
                                     spriteShader, ballTexture,
                                     glm::vec2(screenWidth / 2.0f, screenHeight * 3.0f / 4.0f),
                                     glm::vec2(25.0f, 25.0f), 0.0f, glm::vec3(0.0f, 1.0f, 0.0f))});
  entityRegister.insert(
      {"paddle",
       std::make_shared<entity::Entity>(
           spriteShader, paddleTexture, glm::vec2(screenWidth / 2.0f, screenHeight * 4.5f / 5.0f),
           glm::vec2(150.0f, 30.0f), 0.0f, glm::vec3(0.0f, 0.0f, 1.0f))});
}

void Game::update(float deltaTime) {}

void Game::processInput(float deltaTime) {}

void Game::render() {
  for (auto& level : levels) {
    level->render();
  }

  for (auto& [_, entity] : entityRegister) {
    entity->render();
  }
}

}  // namespace breakout