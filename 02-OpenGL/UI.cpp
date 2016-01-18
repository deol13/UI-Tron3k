#include "UI.h"

UI::UI() 
{
	buttons = nullptr;
	sliders = nullptr;
	staticText = nullptr;
	//dynamicTextBoxes = nullptr;
	//inputBoxes = nullptr;

	objIdList = nullptr;
	texIdList = nullptr;

	nrOfObjects = 0;
	menuId = 0;
}
UI::~UI() 
{
	clean();
}

void UI::clean()
{
	if (buttons != nullptr)
		delete [] buttons;
	if (sliders != nullptr)
		delete [] sliders;
	if (staticText != nullptr)
		delete [] staticText;
	//if (dynamicTextBoxes != nullptr)
	//	delete [] dynamicTextBoxes;
	//if (inputBoxes != nullptr)
	//	delete [] inputBoxes;
	if (objIdList != nullptr)
		delete [] objIdList;
	if (texIdList != nullptr)
		delete [] texIdList;

	nrOfObjects = 0;
	menuId = 0;
}
void UI::changeMenuId()
{
	menuId--;
}

bool UI::loadUI(std::string fileName) 
{

}
int UI::mouseCollission(glm::vec2 pos) 
{
	int hit = -1;
	int result = -1;

	for (int i = 0; i < nrOfbuttons && hit != -1; i++)
	{
		hit = buttons[i].checkCollision(pos);
	}
	for (int i = 0; i < nrOfsliders && hit != -1; i++)
	{
		hit = sliders[i].checkCollision(pos);
	}
	//for (int i = 0; i < nrOfdynamicTextBoxes && hit != -1; i++)
	//{
	//	hit = dynamicTextBoxes[i].checkCollision(pos);
	//}

	if (hit != -1)
		result = collisionEvent(hit);

	return result;
}

//Continue adding on buttons events
int UI::collisionEvent(int UniqueKey) //Every button in every menu have a unique key
{
	int result = -1;

	//Texture change is suppose to be changed to tex 1
	switch (UniqueKey)
	{
	case(4) : //IP
		//Här ska det sättas så man kan skriva in en IP
		break;
	//case(0) : //Roam 0
	//case(1) : //Play 1
	//case(2) : //Settings 2
	//case(3) : //Exit 3
	//case(5) : //Connect 5
	//case(6) : //Back 6
	default: //Everthing that needs to go back to UIManager is defaulted with returning their unique key.
		result = UniqueKey;
		break;
	}
}

glm::vec2 UI::fileCoordToScreenSpace(glm::vec2 pos)
{
	glm::vec2 newVec2;

	newVec2.x = pos.x * 2 - 1;
	newVec2.y = pos.y * 2 - 1;

	return newVec2;
}

void UI::setWorldMatrix(float x, float y, int objId)
{
	sliders[objIdList[objId]].setWorldMatirx(x, y);
}
glm::mat4 UI::returnWorldMatrix(int objId)
{
	return sliders[objIdList[objId]].returnWorldMatrix();
}