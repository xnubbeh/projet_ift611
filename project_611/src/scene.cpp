#include "../header/scene.h"
#include "../header/sprite.h"

void Scene::LoadScene() {

	GameObject* cloppeux = createGameObject("cloppeux");
	RenderData cloppeuxSprite = { glm::vec2(750,0), glm::vec2(50, 50), glm::ivec2(48, 0), glm::ivec2(16, 16), 0.0 };
	cloppeux->CreateRenderData(cloppeuxSprite);
	Sprite::getInstance()->AddSprite(cloppeuxSprite);


}


GameObject* Scene::GetRoot()
{
	return root;
}

Camera* Scene::GetCamera()
{
	return camera;
}

GameObject* Scene::getGameObject(const std::string& name)
{
	return gameObjects.find(name) == gameObjects.end() ? nullptr : gameObjects.find(name)->second;
}

GameObject* Scene::createGameObject(const std::string& name)
{
	GameObject* gameObject = getGameObject(name);

	if (gameObject == nullptr)
	{
		gameObject = new GameObject(name);
		gameObjects.insert(std::pair<std::string, GameObject*>(name, gameObject));
	}

	return gameObject;
}

std::map<std::string, GameObject*>& Scene::getAllGameObjects()
{
	return gameObjects;
}


