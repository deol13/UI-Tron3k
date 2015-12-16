#pragma once
#ifndef SLIDER_H
#define SLIDER_H

#include "Button.h"

class Slider
{
private:


public:
	Slider();
	~Slider();

	void setWorldMatirx();
	glm::vec3 returnPositions();
	glm::mat4 returnWorldMatrix();

	int calcSound();
};

#endif