#pragma once
#include "GLObject.h"
#include "Noise.h"
class Plane :
	public GLObject
{
	GLfloat *pixels;
	GLuint heightmapID;
public:
	int subdivision = 64;
	float offsetX = 0, offsetY = 0;
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

