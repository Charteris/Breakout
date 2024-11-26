#ifndef LEVEL_H
#define LEVEL_H

#include <map>
#include <vector>

#include "entity/Brick.h"

#define RELATIVE_LEVEL_PATH std::string("../res/levels/")

namespace breakout::objects {

class Level {
 public:
  Level(util::Shader& shader, const char* filename, unsigned int levelWidth,
        unsigned int levelHeight);

  void render();
  bool isCompleted();

 private:
  std::vector<entity::Brick> bricks;
  util::Shader shader;
};

}  // namespace breakout::objects

#endif