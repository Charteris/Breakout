#ifndef GAME_H
#define GAME_H

#include <iostream>

#include "ResourceManager.h"

namespace breakout {

enum GameState { ACTIVE, MENU, WIN };

class Game {
 private:
  GameState state;
  bool keys[1024];
  unsigned int screenWidth, screenHeight;

 public:
  Game(unsigned int width, unsigned int height);
  ~Game();

  void init();
  void processInput(float deltaTime);
  void update(float deltaTime);
  void render();
};

}  // namespace breakout

#endif