#include <algorithm>
#include <chrono>
#include <thread>

#include "../header/game_engine.h"


GameEngine::GameEngine() {
   
}

GameEngine::~GameEngine() {
    
}

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

        Render();

        Animate();

        long int timeDifference = std::chrono::duration_cast<std::chrono::milliseconds>(currentTime - std::chrono::system_clock::now()).count();

        if (timeDifference < 16) { // this is so that the game polls inputs at approx 60fps
            std::this_thread::sleep_for(std::chrono::milliseconds(16 - timeDifference));
        }


        glfwSwapBuffers(window);
        // Un thread pour la journalisation aka logging
            // whatever
    }
}


void GameEngine::Render()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    Sprite::getInstance()->RenderAll();
}

void GameEngine::Animate()
{
    ProcessInput(window);
    glfwPollEvents();

    // THE CODE BELOW MIGHT BE DEADCODE TODO
    //std::for_each(scene->getAllGameObjects().begin(), scene->getAllGameObjects().end(), [elapsedTime](const std::pair<std::string, GameObject*>& pair) {
    //    pair.second->Animate(elapsedTime);
    //    });
}

void GameEngine::ProcessInput(GLFWwindow *window) {
    //maybe add a delay since this updates REALLY fast
    glm::vec2 playerPos = scene->getPlayerPos();
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        //get sprite position and move it +y
        if (playerPos.y < SCREEN_HEIGHT && playerPos.y > 0){
            scene->movePlayerPos(glm::vec2(0, 1));
            std::cout << scene->getPlayerPos().x << "    " << scene->getPlayerPos().y << std::endl;
        }
        else {
            std::cout << "bravo champion t'es sortie de l'ecran" << std::endl;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        //get sprite position and move it -y
        if (playerPos.y < SCREEN_HEIGHT && playerPos.y > 0) {
            scene->movePlayerPos(glm::vec2(0, -1));
            std::cout << scene->getPlayerPos().x << "    " << scene->getPlayerPos().y << std::endl;
        }
        else {
            std::cout << "bravo champion t'es sortie de l'ecran" << std::endl;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        //get sprite position and move it -x
        if (playerPos.x < SCREEN_WIDTH && playerPos.x > 0) {
            scene->movePlayerPos(glm::vec2(-1, 0));
            std::cout << scene->getPlayerPos().x << "    " << scene->getPlayerPos().y << std::endl;
        }
        else {
            std::cout << "bravo champion t'es sortie de l'ecran" << std::endl;
        }
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        //get sprite position and move it +x
        if (playerPos.x < SCREEN_WIDTH && playerPos.x > 0) {
            scene->movePlayerPos(glm::vec2(1, 0));
            std::cout << scene->getPlayerPos().x << "    " << scene->getPlayerPos().y << std::endl;
        }
        else {
            std::cout << "bravo champion t'es sortie de l'ecran" << std::endl;
        }
    }
}



