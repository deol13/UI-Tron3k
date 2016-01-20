#pragma once
#ifndef UIMANAGER_H
#define UIMANAGER_H

#include "UI.h"
#include <string>
#include <iostream>

class UIManager
{
private:
	UI* menus;
	int nrOfMenus;
	int maxMenus;
	int currentMenu;

	std::string* fileNamesList;
	int nrOfFileNames;

public:
	UIManager();
	~UIManager();

	void init(std::string* fileNames, int nrOfFiles);

	//Add and remove menus
	bool addMenu(int fileId);
	bool removeMenu(int menuId);
	void removeAllMenus();

	int collisionCheck(glm::vec2 pos, int whichMenu);

	int returnObjCount();
	Vertex* returnPosAUv(int id);
	int* returnTextureList();
	glm::mat4 returnWorldMatrix(int id);

	int changeTex(int objId);
};

#endif