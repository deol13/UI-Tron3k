#include "Button.h"

Button::Button()
{
	size = 0;
	pos = nullptr;
	texList = nullptr;
	texInUse = -1;
	objId = 0;
	worldMatrix = { 1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1
					};
	uniqueKey = -1;
}
Button::Button(int size, glm::vec2 positions, glm::vec2 uv,  int* texList, int objId, int uniqueKey)
{
	this->size = size;
	pos = Vertex(positions.x, positions.y, uv.x, uv.y);
	this->texList = texList;
	this->objId = objId;
	this->uniqueKey = uniqueKey;
	texInUse = 0;
}
Button::~Button()
{
	if (pos != nullptr)
		delete [] pos;
}

void Button::setWorldMatrix(float x, float y) 
{
	worldMatrix[0].w = x;
	worldMatrix[1].w = y;
}

glm::mat4 Button::returnWorldMatrix() 
{
	return worldMatrix;
}

void Button::changeTexUsed(int use) 
{
	texInUse = texList[use];
}

void Button::scalePositions(int scaleX, int scaleY) 
{
	worldMatrix[0].x = scaleX;
	worldMatrix[1].y = scaleY;
}

int Button::checkCollision(glm::vec2 mpos)
{
	int returnValue = -1;
	if (mpos.x >= pos[0].x && mpos.x <= pos[3].x)
	{
		if (mpos.y <= pos[0].x && mpos.y >= pos[3].y)
		{
			returnValue = uniqueKey;
		}
	}

	return returnValue;
}