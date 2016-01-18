#pragma once
#ifndef UI_H
#define UI_H

#include "Button.h"
#include "Slider.h"
#include "staticBox.h"
#include "InputBox.h"
#include "DynamicTextBox.h"

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
	//DynamicTextBox* dynamicTextBoxes;
	//InputBox* inputBoxes;

	int* objIdList; //Used to change from the renders list to UI's list of objects.
	int* texIdList;

	int nrOfbuttons;
	int nrOfsliders;
	int nrOfstaticText;
	//int nrOfdynamicTextBoxes;
	//int nrOfinputBoxes;
	int nrOfObjects;
	int menuId;

public:
	UI();
	~UI();

	void clean();
	void changeMenuId();

	bool loadUI(std::string fileName);
	int mouseCollission(glm::vec2 pos);
	int collisionEvent(int UniqueKey);
	glm::vec2 fileCoordToScreenSpace(glm::vec2 pos);

	void setWorldMatrix(float x, float y, int objId);
	glm::mat4 returnWorldMatrix(int objId);

};

#endif