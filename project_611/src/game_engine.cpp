#include <algorithm>
#include <chrono>
#include <thread>

#include "../header/game_engine.h"
#include "../header/input_manager.h"
#include "../header/utils.h"


int GameEngine::Init() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);

    glfwWindowHint(GLFW_RESIZABLE, false); //save the trouble of resizing for now

    window = glfwCreateWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "game pre-alpha v0.01", NULL, NULL);
    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    scene = Scene::getInstance();
    scene->LoadScene();

    Sprite::getInstance()->Init();

    // TODO : THIS IS A TEST PLEASE REMOVE ME
    glfwSwapInterval(0);

    return EXIT_SUCCESS;
}

void GameEngine::MainLoop()
{
    std::chrono::time_point<std::chrono::high_resolution_clock> previous_time, current_time;
    current_time = std::chrono::high_resolution_clock::now();

    // just to initialize the previousTimestamp

    while (!glfwWindowShouldClose(window)) {

        auto currentTime = std::chrono::system_clock::now();

        int renderTime = [&]() {
            auto before = std::chrono::high_resolution_clock::now();
            Render();
            auto after = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<std::chrono::microseconds>(after - before).count();
        }();

        int animateTime = [&]() {
            auto before = std::chrono::high_resolution_clock::now();
            // TODO : do not call this with PI
            Animate(3.14159f);
            auto after = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<std::chrono::microseconds>(after - before).count();
        }();

        std::cout << "AnimateTime " << animateTime << "us" << std::endl;
        std::cout << "RenderTime " << renderTime << "us" << std::endl;

        long int timeDifference = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - std::chrono::system_clock::now()).count();

        if (timeDifference < 16) { // this is so that the game polls inputs at approx 60fps
            std::this_thread::sleep_for(std::chrono::milliseconds(16 - timeDifference));
        }

        glfwSwapBuffers(window);
    }
}


void GameEngine::Render()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Sprite::getInstance()->RenderAll();
}

void GameEngine::Animate(const float elapsedTime)
{
    InputManager::getInstance()->ProcessInput(window);
    glfwPollEvents();

    std::for_each(scene->getAllGameObjects().begin(), scene->getAllGameObjects().end(), [elapsedTime](const std::pair<std::string, GameObject*>& pair) {
        pair.second->Animate(elapsedTime);
        });
}



