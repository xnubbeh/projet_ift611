#include "game.h"


sprite_render *Renderer;

Game::Game(unsigned int width, unsigned int height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height) {

}

Game::~Game() {
	delete Renderer;
}

void Game::Init()
{
	resource_manager::LoadShader("shaders/sprite.vs","shaders/sprite.frag",NULL,"sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    resource_manager::GetShader("sprite").Use().SetInteger("image", 0);
    resource_manager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    Shader rat_shader = resource_manager::GetShader("sprite");
    Renderer = new sprite_render(rat_shader);
    // load textures
    resource_manager::LoadTexture("textures/rat.png", true, "rat");
}

void Game::ProcessInput(float)
{
}

void Game::Update(float)
{
}

void Game::Render()
{
    Texture rat_texture = resource_manager::GetTexture("rat");
    Renderer->DrawSprite(rat_texture, glm::vec2(200.0f, 200.0f), glm::vec2(300.0f, 400.0f), 45.0f, glm::vec3(0.0f, 1.0f, 0.0f));
}


