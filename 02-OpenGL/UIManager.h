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

	std::string* fileNamesList;
	int nrOfFileNames;

public:
	UIManager();
	~UIManager();

	void init(std::string* fileNames, int nrOfFiles);

	//Add and remove menus
	void addMenu(int id);
	void removeMenu(int menuId);
	void removeAllMenus();
};

#endif