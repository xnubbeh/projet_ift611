#include <algorithm>
#include <chrono>

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

    while (!glfwWindowShouldClose(window)) {
        // Calculate time
        previous_time = current_time;
        current_time = std::chrono::high_resolution_clock::now();
        auto elapsed_Time = current_time - previous_time;
        float elapsed_milli = std::chrono::duration_cast<std::chrono::duration<float, std::milli>>(elapsed_Time).count();

        ProcessInput(window);
        // Un thread pour lire les inputs pi updater l'etat du modele
        glfwPollEvents();
        
        Render();

        Animate (elapsed_milli); //NOT SURE THIS BELONGS HERE
        // Un thread pour display le modele aka render

        // une place ou on met toute les objets de la scenes

        glfwSwapBuffers(window);
        // Un thread pour la journalisation aka logging
            // whatever
    }
}


void GameEngine::Render()
{
    glEnable(GL_DEPTH_TEST);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        
    // SI JAMAIS ON UTILISE UN DRAW CALL POUR TOUS LES OBJETS C CA QUI FAUT FAIRE

    Sprite::getInstance()->RenderAll();

    // SI JAMAIS ON UTILISE UN DRAW CALL PAR OBJET, C CA QUI FAUT FAIRE
    //std::for_each(scene->getAllGameObjects().begin(), scene->getAllGameObjects().end(), [](const std::pair<std::string, GameObject*>& pair) {
    //    pair.second->Render();
    //});
}

void GameEngine::Animate(const float elapsedTime)
{
    std::for_each(scene->getAllGameObjects().begin(), scene->getAllGameObjects().end(), [elapsedTime](const std::pair<std::string, GameObject*>& pair) {
        pair.second->Animate(elapsedTime);
    });
}

void GameEngine::ProcessInput(GLFWwindow *window) {
    glm::vec2 playerPos = scene->getPlayerPos();
    if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS) {
        //get sprite position and move it +y
        scene->setPlayerPos(glm::vec2(0,10));

        std::cout << scene->getPlayerPos().x << "    " << scene->getPlayerPos().y << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS) {
        //get sprite position and move it -y
        std::cout << "S" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS) {
        //get sprite position and move it -x
        std::cout << "A" << std::endl;
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS) {
        //get sprite position and move it +x
        std::cout << "D" << std::endl;
    }
}
