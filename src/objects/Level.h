#ifndef LEVEL_H
#define LEVEL_H

#include <map>
#include <vector>

#include "entity/Brick.h"

#define RELATIVE_LEVEL_PATH std::string("../res/levels/")

namespace breakout::objects {

struct LevelConfig {
  std::string name;
  int width, height;
  LevelConfig(const std::string& levelName, int w, int h) : name(levelName), width(w), height(h) {};
};

const static std::vector<LevelConfig> Levels{LevelConfig("Level1.csv", 10, 10),
                                             LevelConfig("Level2.csv", 10, 10)};

class Level {
 public:
  Level(util::Shader& shader, const LevelConfig& config);

  bool handleCollisions(const std::shared_ptr<entity::Entity>& entity);
  void render();
  bool isCompleted();

 private:
  std::vector<std::shared_ptr<entity::Brick>> bricks;
  util::Shader shader;
};

}  // namespace breakout::objects

#endif