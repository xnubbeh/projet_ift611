#include <algorithm>
#include <chrono>
#include <thread>

#include "../header/game_engine.h"
#include "../header/input_manager.h"
#include "../header/utils.h"
#include "../header/performance_tracker.h"


int GameEngine::Init() {

    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);
    glfwWindowHint(GLFW_RESIZABLE, false); //save the trouble of resizing for now
    
    Camera::getInstance()->setDimensions(screenWidth, screenHeight);

    window = glfwCreateWindow(screenWidth, screenHeight, "game pre-alpha v0.01", glfwGetPrimaryMonitor(), NULL);
    glfwMakeContextCurrent(window);


    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    scene = Scene::getInstance();
    scene->LoadScene();

    Sprite::getInstance()->Init();
    PerformanceTracker::getInstance()->Start();

    // TODO : THIS IS A TEST PLEASE REMOVE ME
    glfwSwapInterval(1);

    return EXIT_SUCCESS;
}

void GameEngine::MainLoop()
{
    std::chrono::time_point<std::chrono::high_resolution_clock> previous_time, current_time;
    current_time = std::chrono::high_resolution_clock::now();

    // just to initialize the previousTimestamp

    while (!glfwWindowShouldClose(window)) {

        auto currentTime = std::chrono::high_resolution_clock::now();

        int renderTime = [&]() {
            auto before = std::chrono::high_resolution_clock::now();
            Render();
            auto after = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<std::chrono::microseconds>(after - before).count();
        }();

        int animateTime = [&]() {
            auto before = std::chrono::high_resolution_clock::now();
            Animate(std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - previous_time).count());
            auto after = std::chrono::high_resolution_clock::now();
            return std::chrono::duration_cast<std::chrono::microseconds>(after - before).count();
        }();
       
        previous_time = currentTime;
        PerformanceTracker::getInstance()->AddTimeMessage(TimeMessage{ animateTime, renderTime });
        long int timeDifference = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - std::chrono::high_resolution_clock::now()).count();

        if (timeDifference < 16) { // this is so that the game polls inputs at approx 60fps
            std::this_thread::sleep_for(std::chrono::milliseconds(15 - timeDifference));
        }

        glfwSwapBuffers(window);
    }

    PerformanceTracker::getInstance()->Stop();
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

    scene->Animate(elapsedTime);
}



