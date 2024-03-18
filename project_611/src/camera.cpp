#include "../header/camera.h"
#include "../third_party/glm/gtc/matrix_transform.hpp"
#include "../header/game_engine.h"


glm::mat4& Camera::Projection()
{
	return projection;
}

void Camera::setDimensions(const unsigned int width, const unsigned int height) {
	projection = glm::ortho(0.0, static_cast<double>(width), 0.0, static_cast<double>(height));
}
