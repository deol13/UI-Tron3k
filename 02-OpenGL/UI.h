#pragma once
#ifndef UI_H
#define UI_H

#include "Button.h"
#include "Slider.h"
#include "staticBox.h"

#include <vector>
#include <string>

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class UI
{
private:
	Button* buttons;
	Slider* sliders;
	StaticBox* staticText;

	int* objIdList;
	int* texIdList;
	
	int nrOfObjects;

public:
	UI();
	~UI();

	bool loadUI(std::string fileName);
	bool mouseColission(bool clicked);
	glm::vec3 pixelToScreenSpace(glm::vec3 pos);


};

#endif