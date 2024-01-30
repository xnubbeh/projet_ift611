// project_611.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#include <glad/glad.h>
#include <glfw3.h>
#include <iostream>

#define STB_IMAGE_IMPLEMENTATION

#include "game.h"
#include "resource_manager.h"

// The Width of the screen
const unsigned int SCREEN_WIDTH = 800;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 600;

int main()
{
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    glfwWindowHint(GLFW_RESIZABLE, false); //save the trouble of resizing for now

    GLFWwindow* window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "game pre-alpha v0.01", NULL, NULL);
    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    Game game{ SCREEN_WIDTH , SCREEN_HEIGHT };
    game.Init();
    glClearColor(0.5, 0.5, 0.5, 1.0);
    glEnable(GL_DEPTH_TEST);

    while (!glfwWindowShouldClose(window)) {
        glfwPollEvents();
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        game.Render();
        glfwSwapBuffers(window);

    }
    
    glfwTerminate();
    return EXIT_SUCCESS;

}

