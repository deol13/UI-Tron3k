#include "UI.h"

UI::UI() 
{
	buttons = nullptr;
	sliders = nullptr;
	staticText = nullptr;
	//dynamicTextBoxes = nullptr;
	//inputBoxes = nullptr;

	objIdList = nullptr;

	nrOfbuttons = 0;
	nrOfsliders = 0;
	nrOfstaticText = 0;
	nrOfdynamicTextBoxes = 0;
	nrOfinputBoxes = 0;

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

	nrOfObjects = 0;
	menuId = 0;
}
void UI::changeMenuId()
{
	menuId--;
}

bool UI::loadUI(std::string fileName) 
{
	std::ifstream myfile;
	myfile.open("Resource/" + fileName);
	
	if (myfile.is_open())
	{
		//Variables for the while loop
		std::string inputString;
		int convertedResult = -1;
		int x, y, u, v, tex1, tex2, scale, counter, uniqueKey, counterButtons, counterSliders, counterStaticText, counterDynamicBox, counterInputBoxes = 0;

		//Number of objects
		getline(myfile, inputString);
		nrOfObjects = std::stoi(inputString); //Convert

		//Which menu
		getline(myfile, inputString);
		menuId = std::stoi(inputString);

		getline(myfile, inputString);
		nrOfbuttons = std::stoi(inputString);
		getline(myfile, inputString);
		nrOfsliders = std::stoi(inputString);
		getline(myfile, inputString);
		nrOfstaticText = std::stoi(inputString);
		getline(myfile, inputString);
		nrOfdynamicTextBoxes = std::stoi(inputString);
		getline(myfile, inputString);
		nrOfinputBoxes = std::stoi(inputString);

		if (nrOfbuttons > 0)
			buttons = new Button[nrOfbuttons];
		if (nrOfsliders)
			sliders = new Slider[nrOfsliders];
		if (nrOfstaticText)
			staticText = new StaticBox[nrOfstaticText];
		//if (nrOfdynamicTextBoxes)
		//	dynamicTextBoxes = new DynamicTextBox[nrOfdynamicTextBoxes];
		//if (nrOfinputBoxes)
		//	inputBoxes = new InputBox[nrOfinputBoxes];

		//Allocate memory
		objIdList = new int[nrOfObjects];
		
		while (myfile.eof) //Looping through the file until there is nothing left to read.
		{
			getline(myfile, inputString); //Get the class key to see which class object that needs to be created.
			convertedResult = std::stoi(inputString);


			if (convertedResult == 0 || convertedResult == 1) //Button or Slider class
			{
				std::string temp;
				glm::vec2 xy[4];
				glm::vec2 uv[4];

				for (int i = 0; i < 4; i++)
				{
					getline(myfile, inputString); //X, Y
					std::stringstream ss(inputString);
					ss >> temp;
					x = std::stoi(temp);
					ss >> temp;
					y = std::stoi(temp);

					getline(myfile, inputString); //U, V
					std::stringstream ss(inputString);
					ss >> temp;
					u = std::stoi(temp);
					ss >> temp;
					v = std::stoi(temp);

					xy[i] = glm::vec2(x, y);
					uv[i] = glm::vec2(u, v);
				}

					getline(myfile, inputString); //tex1
					tex1 = std::stoi(inputString);
					getline(myfile, inputString); //tex2
					tex2 = std::stoi(inputString);
					getline(myfile, inputString); //uniqueKey
					uniqueKey = std::stoi(inputString);
					getline(myfile, inputString); //scale
					scale = std::stoi(inputString);

				if (convertedResult == 0)
				{
					buttons[counterButtons] = Button(xy, uv, tex1, tex2, counter, uniqueKey);
					objIdList[counter] = counterButtons;
					counterButtons++;
				}
				else
				{
					//SLider
					sliders[counterSliders] = Slider(xy, uv, tex1, tex2, counter, uniqueKey);
					objIdList[counter] = counterSliders;
					counterSliders++;
				}
			}
			else if (convertedResult == 2) //StaticText class
			{
				std::string temp;
				glm::vec2 xy[4];
				glm::vec2 uv[4];

				for (int i = 0; i < 4; i++)
				{
					getline(myfile, inputString); //X, Y
					std::stringstream ss(inputString);
					ss >> temp;
					x = std::stoi(temp);
					ss >> temp;
					y = std::stoi(temp);

					getline(myfile, inputString); //U, V
					std::stringstream ss(inputString);
					ss >> temp;
					u = std::stoi(temp);
					ss >> temp;
					v = std::stoi(temp);

					xy[i] = glm::vec2(x, y);
					uv[i] = glm::vec2(u, v);
				}

				getline(myfile, inputString); //tex1
				tex1 = std::stoi(inputString);

				getline(myfile, inputString); //scale
				scale = std::stoi(inputString);

				staticText[counterStaticText] = StaticBox(xy, uv, tex1, counter);
				objIdList[counter] = counterStaticText;
				counterStaticText++;
			}
			else if (convertedResult == 3) //DynamicTextBox class
			{

				objIdList[counter] = counterDynamicBox;
				counterDynamicBox++;
			}
			else if (convertedResult == 4) //InputBox class
			{

				objIdList[counter] = counterInputBoxes;
				counterInputBoxes++;
			}
			else //Error message.
			{
				//std::cout << "Error: Invalid class key" << endl;
			}

			counter++;
		}
	}
	else
		//std::cout << "Error: File could not be opened." << std::endl;

	myfile.close();
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