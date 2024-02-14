#include "../header/camera.h"
#include "../third_party/glm/gtc/matrix_transform.hpp"
#include "../header/game_engine.h"
Camera::Camera() {
	projection = glm::ortho(0.0, 800.0, 0.0, 600.0);
}

glm::mat4& Camera::Projection()
{
	return projection;
}
