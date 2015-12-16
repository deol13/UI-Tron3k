#pragma once
#ifndef STATICBOX_H
#define STATICBOX_H

#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class StaticBox
{
private:
	int size;
	glm::vec3* pos;
	int texId;
	int objId;
public:
	StaticBox();
	StaticBox(int size, glm::vec3* positions, int* texId, int objId);
	~StaticBox();

	glm::vec3* returnPositions();

	void changeTexUsed();

	void scalePositions(int scale);
};

#endif