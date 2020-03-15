#pragma once
#include "GLObject.h"
#include "Program.h"
#include "Camera.h"
class HeightMap :
	public Program
{
	GLuint MatrixID;
	GLuint ModelID;
	GLuint ViewID;
	GLuint Texture1ID;
	GLuint Texture2ID;
public:
	HeightMap();
	void bindProgram(GLObject &obj, Camera &camera);
};

