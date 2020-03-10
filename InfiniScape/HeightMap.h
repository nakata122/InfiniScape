#pragma once
#include "GLObject.h"
#include "Program.h"
class HeightMap :
	public Program
{
	GLuint MatrixID;
	GLuint TextureID;
public:
	HeightMap();
	void bindProgram(GLObject &obj);
};

