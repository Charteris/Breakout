#include "Game.h"

namespace breakout {

Game::Game(unsigned int width, unsigned int height)
    : state(ACTIVE), keys(), screenWidth(width), screenHeight(height) {}

Game::~Game() {}

void Game::init() {}

void Game::update(float dt) {}

void Game::processInput(float dt) {}

void Game::render() {}

}  // namespace breakout