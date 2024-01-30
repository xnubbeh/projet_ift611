#include "game.h"


sprite_render *Renderer;

Game::Game(unsigned int width, unsigned int height) : State(GAME_ACTIVE), Keys(), Width(width), Height(height) {

}

Game::~Game() {
	delete Renderer;
}

void Game::Init()
{
	resource_manager::LoadShader("sprite.vs","sprite.frag",NULL,"sprite");
    glm::mat4 projection = glm::ortho(0.0f, static_cast<float>(this->Width),static_cast<float>(this->Height), 0.0f, -1.0f, 1.0f);
    resource_manager::GetShader("sprite").Use().SetInteger("image", 0);
    resource_manager::GetShader("sprite").SetMatrix4("projection", projection);
    // set render-specific controls
    Shader rat_shader = resource_manager::GetShader("sprite");
    Renderer = new sprite_render(rat_shader);
    // load textures
    resource_manager::LoadTexture("rat.png", true, "rat");
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
    Renderer->DrawSprite(rat_texture, glm::vec2(400.0, 300.0), glm::vec2(20.0,20.0), 45.0f);
}


