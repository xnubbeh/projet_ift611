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

    scene = Scene::getInstance();

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)) {
        std::cerr << "Failed to initialize OpenGL context" << std::endl;
        glfwTerminate();
        return EXIT_FAILURE;
    }

    // Everything here is a square 
    LoadGeometry();

    glClearColor(0.5, 0.5, 0.5, 1.0);

    scene->LoadScene();

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

    std::for_each(scene->getAllGameObjects().begin(), scene->getAllGameObjects().end(), [](const std::pair<std::string, GameObject*>& pair) {
        pair.second->Render();
    });
}

void GameEngine::Animate(const float elapsedTime)
{
    std::for_each(scene->getAllGameObjects().begin(), scene->getAllGameObjects().end(), [elapsedTime](const std::pair<std::string, GameObject*>& pair) {
        pair.second->Animate(elapsedTime);
    });
}

void GameEngine::LoadGeometry() {
    // configure VAO/VBO
    GLuint VBO;
    GLuint VAO;
    float vertices[] = {
        // pos      // tex
        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f, 1.0f,
        1.0f, 1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f, 0.0f
    };

    glCreateBuffers(1, &VBO);
    glNamedBufferData(VBO, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glCreateVertexArrays(1, &VAO);
    glEnableVertexArrayAttrib(VAO, 0);
    glVertexArrayAttribFormat(VAO, 0, 4, GL_FLOAT, GL_FALSE, 0);
    glVertexArrayVertexBuffer(VAO, 0, VBO, 0, sizeof(float) * 4);

    glVertexArrayAttribBinding(VAO, 0, 0);
    glBindVertexArray(VAO);
}
