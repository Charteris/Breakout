#ifndef GAME_H
#define GAME_H

#include <glad/glad.h>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <iostream>
#include <map>
#include <memory>
#include <vector>

#include "ResourceManager.h"
#include "entity/Entity.h"
#include "objects/Level.h"

namespace breakout {

enum GameState { ACTIVE, MENU, WIN };

class Game {
 public:
  Game(unsigned int width, unsigned int height);
  ~Game();

  /**
   * Initializes the game object
   */
  void init();

  /**
   * Processes user inputs
   * @param deltaTime The delta time between game frames
   */
  void processInput(float deltaTime);

  /**
   * Updates all game entities
   * @param deltaTime The delta time between game frames
   */
  void update(float deltaTime);

  /**
   * Renders all game entities
   */
  void render();

 private:
  GameState state;
  bool keys[1024];
  unsigned int screenWidth, screenHeight;
  std::shared_ptr<objects::Level> activeLevel;
  std::map<std::string, std::shared_ptr<entity::Entity>> entityRegister;

  /**
   * Checks if two entities collide
   * @param entityA The first entity instance
   * @param entityB The second entity instance
   * @return True if the entities collided, otherwise false
   */
  bool checkEntityCollision(const std::shared_ptr<entity::Entity>& entityA,
                            const std::shared_ptr<entity::Entity>& entityB);
};

}  // namespace breakout

#endif