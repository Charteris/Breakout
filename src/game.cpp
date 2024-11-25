#include "Game.h"

namespace breakout {

Game::Game(unsigned int width, unsigned int height)
    : state(ACTIVE), keys(), screenWidth(width), screenHeight(height) {}

Game::~Game() {}

void Game::init() {
  ResourceManager::LoadShader("sprite", "sprite.vs", "sprite.fs");
  glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(screenWidth),
                                    static_cast<float>(screenHeight), 0.0f, -1.0f, 1.0f);

  auto sprite = ResourceManager::GetShader("sprite").use();
  sprite.setInteger("image", 0);
  sprite.setMatrix4("projection", projection);

  const auto& ballTexture = ResourceManager::LoadTexture("ball", "Ball.png", true);
  entityRegister.insert(
      {"ball", std::make_shared<entity::Entity>(sprite, ballTexture, glm::vec2(200.0f, 200.0f),
                                                glm::vec2(300.0f, 400.0f), 45.0f,
                                                glm::vec3(0.0f, 1.0f, 0.0f))});
}

void Game::update(float deltaTime) {}

void Game::processInput(float deltaTime) {}

void Game::render() {
  for (const auto& [_, entity] : entityRegister) {
    entity->render();
  }
}

}  // namespace breakout