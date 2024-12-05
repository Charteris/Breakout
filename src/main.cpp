#define STB_IMAGE_IMPLEMENTATION
#define GLFW_INCLUDE_GLCOREARB

#include <cstdlib>

#include "Config.h"
#include "Logs.h"
#include "ResourceManager.h"

int main(int argc, char* argv[]) {
#ifdef USE_LOG_FILES
  logs::openLogs();
#endif

  GLFWwindow* window;
  try {
    window = breakout::initialiseOpenGL();
  } catch (const std::domain_error& error) {
#ifdef USE_LOG_FILES
    logs::closeLogs();
#endif
    return EXIT_FAILURE;
  }

  breakout::Breakout.init();

  float deltaTime = 0.0f;
  float lastFrame = 0.0f;

  while (!glfwWindowShouldClose(window)) {
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;
    glfwPollEvents();

    breakout::Breakout.processInput(deltaTime);
    breakout::Breakout.update(deltaTime);

    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);

    breakout::Breakout.render();

    glfwSwapBuffers(window);
  }

  breakout::ResourceManager::ClearResources();
  glfwTerminate();
#ifdef USE_LOG_FILES
  logs::closeLogs();
#endif
  return EXIT_SUCCESS;
}