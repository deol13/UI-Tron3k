#pragma once
#ifndef UISHADER_H
#define UISHADER_H

#include <gl/glew.h>
#include <gl/GL.h>
#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

class UIShader
{
private:
	void CompileErrorPrint(GLuint* shader);
	void LinkErrorPrint(GLuint* gShaderProgram);

public:
	UIShader();
	UIShader(GLuint* gShaderP);
	~UIShader();

	GLuint* gShaderProgram;
	GLint texture;
	GLint worldMatrix;

	bool compile();
};

#endif