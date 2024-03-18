#ifndef CAMERA_H
#define CAMERA_H

#include "../third_party/glm/glm.hpp"
#include "singleton.h"

class Camera : public Singleton<Camera> {
	friend class Singleton<Camera>;
public:
	Camera() = default;
	~Camera() = default;
	glm::mat4& Projection();
	void setDimensions(const unsigned int width, const unsigned int height);
private:
	glm::mat4 projection;
};

#endif // CAMERA_H
