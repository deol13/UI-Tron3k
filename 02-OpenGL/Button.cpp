#include "Button.h"

Button::Button()
{
	pos = nullptr;
	texList[0] = -1;
	texList[1] = -1;
	texInUse = -1;
	objId = 0;
	worldMatrix = { 1, 0, 0, 0,
					0, 1, 0, 0,
					0, 0, 1, 0,
					0, 0, 0, 1
					};
	uniqueKey = -1;
}
Button::Button(glm::vec2 positions[], glm::vec2 uv[], int tex1, int tex2, int objId, int uniqueKey)
{
	pos = new Vertex[4]();
	for (int i = 0; i < 4; i++)
		pos[i] = Vertex(positions[i].x, positions[i].y, uv[i].x, uv[i].y);
	texList[0] = tex1;
	texList[1] = tex2;
	this->objId = objId;
	this->uniqueKey = uniqueKey;
	texInUse = 0;
}
Button::~Button()
{
	if (texList != nullptr)
		delete [] texList;
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

Vertex* Button::returnPosAUv()
{
	return pos;
}

int Button::returnObjId()
{
	return objId;
}

int Button::changeTexUsed(int use) 
{
	texInUse = texList[use];
	return texInUse;
}

void Button::scalePositions(int scale) 
{
	worldMatrix[0].x = scale;
	worldMatrix[1].y = scale;
	worldMatrix[2].z = scale;
}

int Button::checkCollision(glm::vec2 mpos)
{
	int returnValue = -1;
	if (mpos.x >= pos[1].x && mpos.x <= pos[2].x)
	{
		if (mpos.y >= pos[1].y && mpos.y <= pos[2].y)
		{
			returnValue = uniqueKey;
		}
	}

	return returnValue;
}