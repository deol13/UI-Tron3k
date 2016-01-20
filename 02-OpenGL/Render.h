#pragma once
#ifndef RENDER_H
#define RENDER_H

#include "UIShader.h"
#include "Vertex.h"
#include <string>
#include <vector>
#include "VertexBufferUI.h"
#include "UIManager.h"
//Test
#include "TestClass.h"
#include "stb_image.h"

#include <gl/glew.h>
#include <gl/GL.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>


#define BUFFER_OFFSET(i) ((char *)nullptr + (i))

class Render
{
private:
	UIShader* uiShader;
	GLuint gShaderUI = 0;

	std::vector<GLuint> textureList;
	int textureCount;

	VertexBuffers* vertexRenderBuffers;

	TestClass tester[5];

	int currentMenu; //Which menu should be rendered
	int nrOfButtons; //How many "buttons" the current menu have
	int nrOfMenus; //Total of menus open att the moment

	UIManager manager;

	std::string* txtFileName;
	int txtFileCount;

	int changeTexCounter = 0;
	bool changeMenu = false;
public:
	Render();
	~Render();

	void init(TestClass tester[]);

	void newBuffers(int objCount, int textureIdList[]);
	void cleanUp(int id);

	void update();
	void uiRenderPass();

	void createBuffers(int id);

	void createTexture(const char* filename);
	void loadTextures();

	int mouseClick(float mx, float my);
	int mouseHoverCheck(float mx, float my);

	void changeTex(int texListIndex, int whichButton);

	void removeMenu();
};

#endif