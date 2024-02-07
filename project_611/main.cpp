// main.cpp : This file contains the 'main' function. Program execution begins and ends there.
//


#define STB_IMAGE_IMPLEMENTATION
#include "game_engine.h"

int main()
{
    GameEngine engine{};
    int status = engine.Init();

    if (status  == EXIT_FAILURE)
    {
        return status;
    }

    engine.MainLoop();
    glfwTerminate();

    return EXIT_SUCCESS;
}

