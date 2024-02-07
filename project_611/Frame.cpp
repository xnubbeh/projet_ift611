#include "frame.h"
#include "gtc/matrix_transform.hpp"

Frame::Frame(const glm::mat4& mat, Frame* parent) : matrix{mat}, parent{parent} {}


// sets matrix to identity
void Frame::LoadIdentity() {
	matrix = glm::mat4{ 1.0 };
}

void Frame::SetMatrix(glm::mat4& mat) {
	matrix = mat;
}

glm::mat4* Frame::GetMatrix() {
	return &matrix;
}

glm::mat4 Frame::CopyMatrix() {
	return glm::mat4{ matrix };
}

// returns the transformation matrix from this frame space to the scene root space
glm::mat4 Frame::GetModelMatrix() {
	if (parent == nullptr) {
		return matrix;
	}
	else {
		return parent->GetModelMatrix() * matrix;
	}
}

void Frame::SetParent(Frame* frame) {
	parent = frame;
}

void Frame::RemoveChild(Frame* frame) {
	std::remove(children.begin(), children.end(), frame);
}

void Frame::AddChild(Frame* frame) {
	children.push_back(frame);
}

void Frame::Rotate(float angle) {
	matrix = glm::rotate(std::move(matrix), angle, glm::vec3(0.0,0.0, 1.0));
}

void Frame::Translate(glm::vec2 translation) {
	matrix = glm::translate(std::move(matrix), glm::vec3(translation, 0.0));
}

void Frame::Scale(glm::vec2 scaleFactor) {
	matrix = glm::scale(std::move(matrix), glm::vec3(scaleFactor, 1.0));
}