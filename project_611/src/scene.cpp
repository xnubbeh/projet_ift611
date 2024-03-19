#include "../header/scene.h"
#include "../header/sprite.h"
#include "../header/sprite_index.h"

void Scene::LoadScene() {
	Player* player = createPlayerGameObject(glm::vec2(500, 150));

	// create the bounding box of the screen so the player cant fall out of the map
	OuterScreenBoundingBoxes();
	
	LoadPlatforms();
	
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

Player* Scene::createPlayerGameObject(glm::vec2 playerPos)
{
	GameObject* playerObject = getGameObject("player");
	glm::vec2 hitboxDim = glm::vec2(33, 47);
	glm::vec2 hitboxOffset = glm::vec2(14, 0);
	

	if (playerObject != nullptr) {
		return static_cast<Player*>(playerObject);
	}

	Player* player = new Player("player", 4.0f);
	RenderData playerSprite { playerPos, glm::vec2(64, 64), glm::vec2(0, 0), glm::vec2(32, 32), 1.0 , 0.0};
	player->CreateRenderData(std::move(playerSprite));
	player->setHitboxDim(std::move(hitboxDim));
	player->setHitboxOffset(std::move(hitboxOffset));

	gameObjects.insert(std::pair<std::string, GameObject*>("player", static_cast<GameObject*>(player)));
	addMovableObject(player);

	return player;
}

EnvironmentObject* Scene::getEnvironmentObject(const std::string& name) {
	return environmentObjects.find(name) == environmentObjects.end() ? nullptr : environmentObjects.find(name)->second;
}

EnvironmentObject* Scene::createEnvironmentObject(const std::string& name) {
	EnvironmentObject* environmentObject = getEnvironmentObject(name);

	if (environmentObject == nullptr)
	{
		environmentObject = new EnvironmentObject(name);
		environmentObjects.insert(std::pair<std::string, EnvironmentObject*>(name, environmentObject));
	}

	return environmentObject;
}

std::map<std::string, GameObject*>& Scene::getAllGameObjects()
{
	return gameObjects;
}

void Scene::Animate(const float elapsedTime) {
	
	std::for_each(this->getAllGameObjects().begin(), this->getAllGameObjects().end(), [elapsedTime](const std::pair<std::string, GameObject*>& pair) {
		pair.second->Animate(elapsedTime);
		});
	collider.checkCollision(collidableMovableObjects, collidableImmovableObjects);
}

// screen width/height 1920 : 1080
void Scene::OuterScreenBoundingBoxes() {
	// Create GameObjects
	EnvironmentObject* bottom, * top, * left, * right;
	bottom = createEnvironmentObject("bottomOuterPlatform");
	top = createEnvironmentObject("topOuterPlatform");
	left = createEnvironmentObject("leftOuterPlatform");
	right = createEnvironmentObject("rightOuterPlatform");

	// Assign them some render data, mostly for position and dimensions. Other fields are not required
	RenderData bottomRD{ glm::vec2{-10,-50}, {1940, 50}, SpriteIndex::getInstance()->getSpriteOffset(SpriteType::FloorTiles, 0),  glm::vec2{32, 32}, 0.5, 0.0 };
	RenderData topRD{ glm::vec2{-10,1080}, {1940, 50}, SpriteIndex::getInstance()->getSpriteOffset(SpriteType::FloorTiles, 0),  glm::vec2{32, 32}, 0.5, 0.0 };
	RenderData leftRD{ glm::vec2{-50,0}, {50, 1080}, SpriteIndex::getInstance()->getSpriteOffset(SpriteType::FloorTiles, 0),  glm::vec2{32, 32}, 0.5, 0.0 };
	RenderData rightRD{ glm::vec2{1920,0}, {50, 1080}, SpriteIndex::getInstance()->getSpriteOffset(SpriteType::FloorTiles, 0),  glm::vec2{32, 32}, 0.5, 0.0 };
	bottom->CreateRenderData(bottomRD);
	top->CreateRenderData(topRD);
	left->CreateRenderData(leftRD);
	right->CreateRenderData(rightRD);

	// Assign them a bounding box
	glm::vec2 horizontalBoundingBoxDimensions{1940, 50};
	glm::vec2 verticalBoundingBoxDimensions{50, 1080};
	bottom->setHitboxDim(horizontalBoundingBoxDimensions);
	top->setHitboxDim(horizontalBoundingBoxDimensions);
	left->setHitboxDim(verticalBoundingBoxDimensions);
	right->setHitboxDim(verticalBoundingBoxDimensions);

	addImmovableObject(bottom);
	addImmovableObject(top);
	addImmovableObject(left);
	addImmovableObject(right);
}

void Scene::LoadPlatforms() {
	std::string platform{ "platform" };

	for (int i{ 0 }; i < 4; ++i) {
		std::string level{ std::to_string(i*100) };
		CreatePlatform(platform + level, 30, glm::vec2{ 200, i * 250 + 150 });
	}
}

void Scene::CreatePlatform(std::string uniqueName, int length, glm::vec2 position) {
	std::string platform{ "platform" };
	glm::vec2 platformDimensions{ 50,50 };
	glm::vec2 platformBoundingBoxDimensions{ length*50, 50 };
	glm::vec2 spriteSize{ 32,32 };
	glm::vec2 spriteOffset = SpriteIndex::getInstance()->getSpriteOffset(SpriteType::FloorTiles, 0);
	RenderData renderData{ glm::vec2{}, platformDimensions, spriteOffset, spriteSize, 0.5, 0.0 };

	for (int i{ 0 }; i < length; ++i) {
		EnvironmentObject* currentPlatform = createEnvironmentObject(platform + uniqueName + std::to_string(i));
		glm::vec2 platformPosition{ (i * 50) + position.x, position.y };
		renderData.pos = platformPosition;
		currentPlatform->CreateRenderData(renderData);
		if (i == 0) {
			currentPlatform->setHitboxDim(platformBoundingBoxDimensions);
			currentPlatform->SetIsGround();
			addImmovableObject(currentPlatform);
		}
	}
}

void Scene::CreateWall(std::string uniqueName, int height, glm::vec2 position) {
	std::string wall{ "wall" };
	glm::vec2 spriteScreenDimensions{ 50,50 };
	glm::vec2 wallBoundingBoxDimensions{ 50, height * 50 };
	glm::vec2 spriteSize{ 32,32 };
	glm::vec2 spriteOffset = SpriteIndex::getInstance()->getSpriteOffset(SpriteType::FloorTiles, 0);
	RenderData renderData{ glm::vec2{}, spriteScreenDimensions, spriteOffset, spriteSize, 0.5, 0.0 };

	for (int i{ 0 }; i < height; ++i) {
		EnvironmentObject* currentPlatform = createEnvironmentObject(wall + uniqueName + std::to_string(i));
		glm::vec2 platformPosition{ position.x, position.y + (i * 50)};
		renderData.pos = platformPosition;
		currentPlatform->CreateRenderData(renderData);
		if (i == 0) {
			currentPlatform->setHitboxDim(wallBoundingBoxDimensions);
			currentPlatform->SetIsGround();
			addImmovableObject(currentPlatform);
		}
	}
}

void Scene::addMovableObject(GameObject* obj) {
	if (obj->isCollidable()) {
		collidableMovableObjects.push_back(obj);
	}
}

void Scene::addImmovableObject(EnvironmentObject* obj) {
	if (obj->isCollidable()) {
		collidableImmovableObjects.push_back(obj);
	}
}