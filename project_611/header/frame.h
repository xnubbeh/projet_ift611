#ifndef FRAME_H
#define FRAME_H

#include "glm.hpp"
#include <vector>

class Frame
{
public:
	Frame() = default;
	Frame(const glm::mat4& mat, Frame* parent);
	~Frame() = default;

	// sets matrix to identity
	void LoadIdentity();

	void SetMatrix(glm::mat4& mat);

	glm::mat4* GetMatrix();

	glm::mat4 CopyMatrix();

	// returns the transformation matrix from this frame space to the scene root space
	glm::mat4 GetModelMatrix();

	void SetParent(Frame* frame);

	void RemoveChild(Frame* frame);

	void AddChild(Frame* frame);

	// rotate *angle* radians
	void Rotate(float angle);

	void Translate(glm::vec2 translation);

	void Scale(glm::vec2 scaleFactor);

private:
	// ownership of the children is not here
	std::vector<Frame*> children;
	glm::mat4 matrix;
	// ownership of this pointer is not here
	Frame* parent;
};

#endif // FRAME_H
