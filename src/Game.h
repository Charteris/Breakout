#ifndef GAME_H
#define GAME_H

#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "ResourceManager.h"
#include "entity/Entity.h"
#include "objects/Level.h"

namespace breakout {

enum GameState { ACTIVE, MENU, WIN };

class Game {
 public:
  Game(unsigned int width, unsigned int height);
  ~Game();

  void init();
  void processInput(float deltaTime);
  void update(float deltaTime);
  void render();

 private:
  GameState state;
  bool keys[1024];
  unsigned int screenWidth, screenHeight;
  std::vector<std::shared_ptr<objects::Level>> levels;
  std::map<std::string, std::shared_ptr<entity::Entity>> entityRegister;
};

}  // namespace breakout

#endif