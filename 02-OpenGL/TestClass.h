#pragma once
#ifndef TESTCLASS_H
#define TESTCLASS_H

#include "Vertex.h"

class TestClass
{
private:
public:
	TestClass();

	void init(Vertex tPosList[]);

	Vertex posList[4];
	int size = 4;
};

#endif
