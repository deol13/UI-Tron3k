#pragma once
#ifndef BUTTON_H
#define BUTTON_H

#include "Vertex.h"

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class Button
{
private:
	int size;
	Vertex* pos;
	int* texList;
	int texInUse;
	int objId;
	int uniqueKey;
	glm::mat4 worldMatrix;

public:
	Button();
	Button(int size, glm::vec2 positions, glm::vec2 uv, int* texList, int objId, int uniqueKey);
	~Button();

	void setWorldMatrix(float x, float y);
	glm::mat4 returnWorldMatrix();
	
	void changeTexUsed(int use);

	void scalePositions(int scaleX, int scaleY);

	int checkCollision(glm::vec2 pos);
};

#endif