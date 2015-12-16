#ifndef VERTEX_H
#define VERTEX_H


#include <glm\glm.hpp>
#include <glm\gtc\matrix_transform.hpp>

struct Vertex
{
	float x, y, z; 
	float u, v;
	
	Vertex(){}

	Vertex( float tx, float ty, float tz , float tu, float tv )
	{
		x = tx;
		y = ty;
		z = tz;
		u = tu;
		v = tv;
	}

	~Vertex(){}

	glm::vec3 getXYZ()
	{
		return glm::vec3(x, y, z);
	}
};

#endif