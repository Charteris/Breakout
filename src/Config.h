#ifndef CONFIG_H
#define CONFIG_H

#include <glad/glad.h>
#include <glfw/glfw3.h>

#include <exception>
#include <iostream>
#include <random>

#include "Game.h"
#include "Logs.h"

namespace breakout {

extern const unsigned int SCREEN_WIDTH;
extern const unsigned int SCREEN_HEIGHT;

extern Game Breakout;

/**
 * Provides a frame buffer size callback to resize the window
 * @param window The GLFW window being resized by the user
 * @param width The new width of the window in pixels after resize
 * @param height The new height of the window in pixels after resize
 */
void framebufferSizeCallback(GLFWwindow* window, int width, int height);

/**
 * Provides a key callback to be called whenever the user presses a key
 * @param window The GLFW window currently in focus
 * @param key The key pressed by the user
 * @param scancode The scancode of the key pressed by the user
 * @param action The action describing whether the key was pressed, repeated or released
 * @param mode The mode of the key pressed by the user
 */
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mode);

/**
 * Initialises the GLFW window including assigning callback functions and graphical settings
 * @return The GLFW window instantiated by this function
 */
GLFWwindow* initialiseOpenGL();

/**
 * Generates a unique UUID for identifying entities
 * Note this is not truly unique but there is an incredibly low chance of duplicates
 * @return The generated UUID
 */
std::string generateUuid();

}  // namespace breakout

#endif