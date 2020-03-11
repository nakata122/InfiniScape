#pragma once
#include "GLObject.h"
class Plane :
	public GLObject
{
	float ***Gradient;
public:
	Plane(int subdivision, int frequency);
	float OctavePerlin(float x, float y, int octaves);
	float lerp(float a, float b, float p);
	float dotGridGradient(int ix, int iy, float x, float y);
	float perlin(float x, float y);
	void generateNew();
};

