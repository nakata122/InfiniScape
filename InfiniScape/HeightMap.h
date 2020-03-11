#pragma once
#include "GLObject.h"
#include "Program.h"
class HeightMap :
	public Program
{
	GLuint MatrixID;
	GLuint Texture1ID;
	GLuint Texture2ID;
public:
	HeightMap();
	void bindProgram(GLObject &obj);
};

