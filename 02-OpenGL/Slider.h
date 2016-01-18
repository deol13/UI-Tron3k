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


	void setWorldMatirx(float x, float y);
	glm::mat4 returnWorldMatrix();

	int calcSound();

	bool checkCollision(glm::vec2 pos);
};

#endif

//Sätt button direkt dit spelaren klickade.