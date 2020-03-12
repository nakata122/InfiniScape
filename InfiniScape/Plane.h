#pragma once
#include "GLObject.h"
class Plane :
	public GLObject
{
	float ***Gradient;
public:
	float frequency = 20;
	float amplitude = 20;
	float persistence = 1;
	int octaves = 1;
	int subdivision = 4;

	Plane(int subdivision);
	float OctavePerlin(float x, float y, int octaves, float persistence);
	float lerp(float a, float b, float p);
	float dotGridGradient(int ix, int iy, float x, float y);
	float perlin(float x, float y);
	void updateVertices();
	void generateNew();
};

