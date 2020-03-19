#pragma once
#include "GLObject.h"
#include "Noise.h"
class Plane :
	public GLObject
{
	GLfloat *pixels;
	GLuint heightmapID;
public:
	int subdivision = 128;
	float offsetX, offsetY;
	Noise noise;


	Plane(int numTriangles);
	~Plane();
	void calculateHeight(int i, int j, int vIndex);
	void updateVertices();
	void vertexThread(int startS);
	void indexThread(int startS);
	void pixelThread(int startS);
	void updateHeightMap();
};

