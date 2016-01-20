#include "Render.h"

Render::Render()
{
	//default values
	currentMenu = -1;
	nrOfButtons = 0;
	nrOfMenus = 0;
	textureCount = 0;
	gShaderUI = 0;
	uiShader = nullptr;
	txtFileCount = 1;
	txtFileName = nullptr;

	//Allocate memory
	uiShader = new UIShader(&gShaderUI);

	vertexRenderBuffers = new VertexBuffers[4];
}
Render::~Render()
{
	textureList.clear();

	//deallocate
	for (size_t i = 0; i < nrOfMenus; i++)
		vertexRenderBuffers[i].clean();
	

	delete[] vertexRenderBuffers;
	delete[] txtFileName;
	delete uiShader;
	glDeleteShader(gShaderUI);
}

void Render::init(TestClass tester[])
{
	//Load all the textures
	loadTextures();

	txtFileName = new std::string[txtFileCount];
	txtFileName[0] = std::string("test.txt");

	/*Start Menu*/
	manager.init(txtFileName, txtFileCount);
	manager.addMenu(0);
	newBuffers(manager.returnObjCount(), manager.returnTextureList());
}

void Render::update() {}

void Render::uiRenderPass()
{
	glUseProgram(gShaderUI);

	changeTexCounter++;

	//Go through the list of buttons and render them
	for (size_t i = 0; i < nrOfButtons; i++)
	{
		int tmp = vertexRenderBuffers[currentMenu].textureIDs[i];
		//Activate the buttons texture
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, tmp);

		//Texture Sample sent to the gpu
		glProgramUniform1i(gShaderUI, uiShader->texture, i);
		glProgramUniformMatrix4fv(gShaderUI, uiShader->worldMatrix, 1, GL_FALSE, &manager.returnWorldMatrix(i)[0][0]);

		//Bind the vertex buffer that will be used
		glBindVertexArray(vertexRenderBuffers[currentMenu].gVertexAttribute[i]);
		glBindBuffer(GL_ARRAY_BUFFER, vertexRenderBuffers[currentMenu].gVertexBuffer[i]);

		glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
	}

	if (changeTexCounter == 100)
	{
		changeTex(manager.changeTex(0), 0);
		changeTex(manager.changeTex(1), 1);
		changeTexCounter = 0;
	}
	//if (changeTexCounter == 100)
	//{
	//	changeTex(manager.changeTex(0), 0);
	//	changeTex(manager.changeTex(1), 1);
	//	changeTexCounter = 0;
	//}

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		printf("Error");
}

void Render::cleanUp(int id) //Needs to be put together with UIManager clean up
{
	if (id == -1) //Remove all the buffers
	{
		for (size_t i = 0; i < nrOfMenus; i++)
			vertexRenderBuffers[i].clean();

		nrOfMenus = 0;
		currentMenu = -1;
		nrOfButtons = 0;
	}
	else if (nrOfMenus == 1) //Only one buffer left
	{
		vertexRenderBuffers[0].clean();
		nrOfMenus = 0;
		currentMenu - 1;
		nrOfButtons = 0;
	}
	else //Just remove one of the buffers
	{
		vertexRenderBuffers[id].clean();
		nrOfMenus--;
		currentMenu = nrOfMenus - 1;
		nrOfButtons = vertexRenderBuffers[currentMenu].count;
	}
}

void Render::newBuffers(int objCount, int textureIdList[])
{
	//Check so we are not going over the limit of opened menues.
	if (nrOfMenus + 1 <= 4)
	{
		nrOfMenus++;

		currentMenu = nrOfMenus - 1;
		nrOfButtons = objCount;

		//Set the defualt values.
		vertexRenderBuffers[currentMenu] = VertexBuffers(objCount);
		for (int i = 0; i < objCount; i++)
		{
			////Default values
			//vertexRenderBuffers[currentMenu].gVertexAttribute[i] = 0;
			//vertexRenderBuffers[currentMenu].gVertexBuffer[i] = 0;

			//Sets the newly created buffers values
			createBuffers(i);

			//Set the list of texture ids
			int tmp = textureList[textureIdList[i]];
			vertexRenderBuffers[currentMenu].textureIDs[i] = tmp;
		}
	}
}

void Render::createBuffers(int id)
{
	//create buffer and set data
	glGenBuffers(1, &vertexRenderBuffers[currentMenu].gVertexBuffer[id]);
	glBindBuffer(GL_ARRAY_BUFFER, vertexRenderBuffers[currentMenu].gVertexBuffer[id]);
	glBufferData(GL_ARRAY_BUFFER, sizeof(Vertex) * 4, &manager.returnPosAUv(id)[0], GL_STATIC_DRAW); // &tester[id].posList[0] bytt ut mot UIs buttons Vertex

	//define vertex data layout
	glGenVertexArrays(1, &vertexRenderBuffers[currentMenu].gVertexAttribute[id]);
	glBindVertexArray(vertexRenderBuffers[currentMenu].gVertexAttribute[id]);
	glEnableVertexAttribArray(0); //the vertex attribute object will remember its enabled attributes
	glEnableVertexAttribArray(1);

	GLint vertexPos = glGetAttribLocation(gShaderUI, "vertex_position");
	glVertexAttribPointer(vertexPos, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(0));
	GLint vertexUV = glGetAttribLocation(gShaderUI, "vertex_uv");
	glVertexAttribPointer(vertexUV, 2, GL_FLOAT, GL_FALSE, sizeof(Vertex), BUFFER_OFFSET(sizeof(float) * 2));

	GLenum error = glGetError();
	if (error != GL_NO_ERROR)
		printf("Error");
}


void Render::createTexture(const char* filename)
{
	GLuint texID = 0;
	int x, y, n;
	//Load texture from file
	stbi_uc* textureData = stbi_load(filename, &x, &y, &n, 4);

	//Error check
	if (textureData == nullptr)
		throw(std::string("Failed to load texture"));

	//Create texture holder
	glGenTextures(1, &texID);
	//glActiveTexture(GL_TEXTURE0 + textureCount);
	glBindTexture(GL_TEXTURE_2D, texID);

	//Sets paramteres for the texture
	glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, (void*)textureData);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
	glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);

	GLenum error1 = glGetError();
	if (error1 != GL_NO_ERROR)
		printf("Error");

	//Save the id
	textureList.push_back(texID);

	//Release the image
	stbi_image_free(textureData);

	textureCount++;
}
void Render::loadTextures()
{
	//Go through all the textures that will be needed
	const char* filename = new char();

	//Grass texture
	filename = "grassTexture.png";
	createTexture(filename);

	//Grass texture with a 2
	filename = "secondTexture.png";
	createTexture(filename);
	
	//Grass texture with a 3
	filename = "thirdTexture.png";
	createTexture(filename);

	//Grass texture with a 3
	filename = "fourthTexture.png";
	createTexture(filename);

	//Grass texture with a 3
	filename = "fifthTexture.png";
	createTexture(filename);

}


int Render::mouseClick(float mx, float my) 
{ 
	//UI->;
	return 0; 
}
int Render::mouseHoverCheck(float mx, float my) 
{ 
	//UI->;
	return 0; 
}

/*
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_CLAMP_TO_EDGE);
glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_CLAMP_TO_EDGE);
glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, x, y, 0, GL_RGBA, GL_UNSIGNED_BYTE, textureData);
*/

void Render::changeTex(int texListIndex, int whichButton)
{
	vertexRenderBuffers[currentMenu].textureIDs[whichButton] = textureList[texListIndex];
}