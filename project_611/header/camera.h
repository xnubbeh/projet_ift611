#ifndef CAMERA_H
#define CAMERA_H

#include "../third_party/glm/glm.hpp"
#include "singleton.h"

class Camera : public Singleton<Camera> {
	friend class Singleton<Camera>;
public:
	Camera();
	~Camera() = default;
	glm::mat4& Projection();
private:
	glm::mat4 projection;
};

#endif // CAMERA_H
