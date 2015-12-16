#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Button
{
private:
	int size;
	glm::vec3* pos;
	int texId;
	int objId;
	glm::mat4 worldMatrix;

public:
	Button();
	Button(int size, glm::vec3* positions, int* texId, int objId);
	~Button();

	void setWorldMatirx();
	glm::mat4 returnWorldMatrix();
	glm::vec3* returnPositions();
	
	void changeTexUsed();

	void scalePositions(int scale);

};

#endif