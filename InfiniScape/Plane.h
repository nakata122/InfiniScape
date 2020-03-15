#pragma once
#include "GLObject.h"
class Plane :
	public GLObject
{
	float *Gradient;
public:
	float frequency = 0.05;
	float amplitude = 1;
	float persistence = 1;
	int octaves = 1;
	int seed = 0;
	int subdivision = 256;
	int noiseSize = 128;
	float elevation = 1;

	Plane(int numTriangles);
	float OctavePerlin(float x, float y, int octaves, float persistence);
	float smoothstep(const float &t);
	float perlin(float x, float y);
	void calculateHeight(int i, int j, int vIndex);
	void updateVertices();
	void vertexThread();
	void generateNew();
};

