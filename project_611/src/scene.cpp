#include "../header/scene.h"
#include "../header/sprite.h"

void Scene::LoadScene() {

	GameObject* cloppeux = createGameObject("cloppeux");
	RenderData cloppeuxSprite = { glm::vec2(400,350), glm::vec2(50, 50), glm::vec2(0, 0), glm::vec2(16, 16), 0.0 };
	cloppeux->CreateRenderData(cloppeuxSprite);
	Sprite::getInstance()->AddSprite(cloppeuxSprite);

	GameObject* cloppeux2 = createGameObject("cloppeux2");
	RenderData cloppeuxSprite2 = { glm::vec2(10,0), glm::vec2(50, 50), glm::vec2(16, 0), glm::vec2(16, 16), 0.25 };
	cloppeux2->CreateRenderData(cloppeuxSprite2);
	Sprite::getInstance()->AddSprite(cloppeuxSprite2);

	GameObject* cloppeux3 = createGameObject("cloppeux3");
	RenderData cloppeuxSprite3 = { glm::vec2(50,150), glm::vec2(50, 50), glm::vec2(32, 0), glm::vec2(16, 16), 0.75 };
	cloppeux3->CreateRenderData(cloppeuxSprite3);
	Sprite::getInstance()->AddSprite(cloppeuxSprite3);



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


