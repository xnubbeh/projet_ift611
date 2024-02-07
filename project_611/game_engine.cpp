#include <algorithm>

#include "game_engine.h"


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

    scene = Scene::getInstance();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    return EXIT_SUCCESS;
}

void GameEngine::MainLoop()
{
    while (!glfwWindowShouldClose(window)) {
        // Un thread pour lire les inputs pi updater l'etat du modele
        glfwPollEvents();
        // Un thread pour display le modele aka render

        // une place ou on met toute les objets de la scenes

        Render();

        glfwSwapBuffers(window);
        // Un thread pour la journalisation aka logging
            // whatever
    }
}


void GameEngine::Render()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    std::for_each(scene->getAllGameObjects().begin(), scene->getAllGameObjects().end(), [](const std::pair<std::string, GameObject*>& pair) {
            pair.second->Render();
        });

}



