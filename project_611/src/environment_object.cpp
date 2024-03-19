#include "../header/environment_object.h"

void EnvironmentObject::SetIsGround() {
	isActualGround = true;
}

bool EnvironmentObject::IsGround() {
	return isActualGround;
}