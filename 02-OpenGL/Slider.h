#pragma once
#ifndef SLIDER_H
#define SLIDER_H

#include "Button.h"
#include "staticBox.h"

class Slider
{
private:
	Button theSlider;
	StaticBox valueBoxes[2];
	//Dynamic value box.

	glm::mat4 worldMatrix;

public:
	Slider();
	~Slider();

	void addBox(int size, glm::vec3* positions, int* texId, int objId);


	void setWorldMatirx();
	glm::vec3 returnPositions();
	glm::mat4 returnWorldMatrix();

	int calcSound();
};

#endif