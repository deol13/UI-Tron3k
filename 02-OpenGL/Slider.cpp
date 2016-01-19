#include "Slider.h"

Slider::Slider() {}
Slider::Slider(glm::vec2 positions[], glm::vec2 uv[], int tex1, int tex2, int objId, int uniqueKey){}
Slider::~Slider() {}

void Slider::setWorldMatirx(float x, float y) {}
glm::mat4 Slider::returnWorldMatrix(int objId) 
{ 
	glm::mat4 result;
	if (objId == backGround.returnObjId())
		result = backGround.returnWorldMatrix();
	else
		result = pointer.returnWorldMatrix();

	return result;
}


int Slider::calcSound() { return 0;  }

bool Slider::checkCollision(glm::vec2 pos) { return false; }