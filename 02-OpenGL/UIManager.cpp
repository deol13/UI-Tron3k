#include "UIManager.h"

UIManager::UIManager()
{
	fileNamesList = nullptr;
	menus = nullptr;
	nrOfFileNames = 0;
	nrOfMenus = 0;
	maxMenus = 5;

}
UIManager::~UIManager() 
{
	if ( fileNamesList != nullptr )
		delete [] fileNamesList;
	if ( menus != nullptr )
		delete[] menus;
}

//Start menu
void UIManager::init(std::string* fileNames, int nrOfFiles)
{
	nrOfFileNames = nrOfFiles;
	for (size_t i = 0; i < nrOfFileNames; i++)
		fileNamesList[i] = fileNames[i];

	menus = new UI[maxMenus];
}

//Add and remove menus
void UIManager::addMenu(int id) 
{
	if (nrOfMenus < maxMenus)
	{
		if (id < nrOfFileNames)
		{
			menus[nrOfMenus].loadUI(fileNamesList[id]);

			nrOfMenus++;
		}
		//else
		//	std::cout << "Error: File name id out of range." << std::endl;
	}
	//else
	//	std::cout << "Error: Max menus opened already." << std::endl;

	
}
void UIManager::removeMenu(int menuId) 
{

}
void UIManager::removeAllMenus() 
{

}