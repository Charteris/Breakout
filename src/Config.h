#ifndef CONFIG_H
#define CONFIG_H

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <exception>
#include <iostream>

#include "Game.h"
#include "Logs.h"

namespace breakout {

extern const unsigned int SCREEN_WIDTH;
extern const unsigned int SCREEN_HEIGHT;

extern Game Breakout;

void framebufferSizeCallback(GLFWwindow* window, int width, int height);
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);
GLFWwindow* initialiseOpenGL();

}  // namespace breakout

#endif