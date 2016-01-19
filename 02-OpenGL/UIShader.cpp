#include "UIShader.h"

#include <vector>
#include <fstream>

UIShader::UIShader() {}
UIShader::UIShader(GLuint* gShaderP)
{
	gShaderProgram = gShaderP;
	compile();
	texture = glGetUniformLocation(*gShaderProgram, "textureSample");
	worldMatrix = glGetUniformLocation(*gShaderProgram, "worldMatrix");
}
UIShader::~UIShader()
{}

bool UIShader::compile()
{
	const char* vertex_shader = R"(
		#version 410
		layout(location = 0) in vec2 vertex_position;
		layout(location = 1) in vec2 vertex_uv;

		uniform mat4 worldMatrix;		

		out vec2 UV;
		
		void main () {
			UV = vertex_uv;
			gl_Position = vec4 (vertex_position, 0.0, 1.0) * worldMatrix;
		}
	)";

	const char* fragment_shader = R"(
		#version 410
		in vec2 UV;

		uniform sampler2D textureSample;
		
		out vec4 fragment_color;

		void main () 
		{
			fragment_color = texture(textureSample, UV);
			//vec4(1.0f, 0.0f, 0.0f, 1.0f) + texture(textureSample, UV) * 0.00000001f;
		}
	)";

	//create vertex shader
	GLuint vs = glCreateShader(GL_VERTEX_SHADER);
	glShaderSource(vs, 1, &vertex_shader, nullptr);
	glCompileShader(vs);
	CompileErrorPrint(&vs);

	//create fragment shader
	GLuint fs = glCreateShader(GL_FRAGMENT_SHADER);
	glShaderSource(fs, 1, &fragment_shader, nullptr);
	glCompileShader(fs);
	CompileErrorPrint(&fs);

	//link shader program (connect vs and ps)
	*gShaderProgram = glCreateProgram();
	glAttachShader(*gShaderProgram, fs);
	glAttachShader(*gShaderProgram, vs);
	glLinkProgram(*gShaderProgram);
	LinkErrorPrint(gShaderProgram);

	return true;
}

void UIShader::LinkErrorPrint(GLuint* gShaderProgram)
{
	GLint success;
	glGetProgramiv(*gShaderProgram, GL_LINK_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetProgramiv(*gShaderProgram, GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetProgramInfoLog(*gShaderProgram, maxLength, &maxLength, &errorLog[0]);

		std::fstream myfile;
		myfile.open("errorLinkCheck.txt", std::fstream::out);
		for (int i = 0; i < maxLength; i++)
		{
			myfile << errorLog[i];
		}
		myfile.close();

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteProgram(*gShaderProgram); // Don't leak the shader.
		throw;
	}
}
void UIShader::CompileErrorPrint(GLuint* shader)
{
	GLint success;
	glGetShaderiv(*shader, GL_COMPILE_STATUS, &success);
	if (success == GL_FALSE)
	{
		GLint maxLength = 0;
		glGetShaderiv((*shader), GL_INFO_LOG_LENGTH, &maxLength);

		// The maxLength includes the NULL character
		std::vector<GLchar> errorLog(maxLength);
		glGetShaderInfoLog((*shader), maxLength, &maxLength, &errorLog[0]);

		std::fstream myfile;
		myfile.open("errorCheck.txt", std::fstream::out);
		for (int i = 0; i < maxLength; i++)
		{
			myfile << errorLog[i];
		}
		myfile.close();

		// Provide the infolog in whatever manor you deem best.
		// Exit with failure.
		glDeleteShader(*shader); // Don't leak the shader.
		throw;
	}
}