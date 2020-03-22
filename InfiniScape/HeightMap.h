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
	GLuint OffsetID;
	GLuint TextureID[3];
public:
	HeightMap();
	void bindProgram(GLObject &obj, Camera &camera);
};

