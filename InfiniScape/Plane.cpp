#include "pch.h"

#include <iostream>
#include <vector>
#include <time.h>
#include <cmath>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Plane.h"

float Plane::lerp(float a, float b, float p)
{
	return a + p * (b - a);
}

// Computes the dot product of the distance and gradient vectors.
float Plane::dotGridGradient(int ix, int iy, float x, float y) {

	// Compute the distance vector
	float dx = x - (float)ix;
	float dy = y - (float)iy;

	// Compute the dot-product
	return (dx*Gradient[iy][ix][0] + dy * Gradient[iy][ix][1]);
}

// Compute Perlin noise at coordinates x, y
float Plane::perlin(float x, float y) {

	// Determine grid cell coordinates
	int x0 = (int)x;
	int x1 = x0 + 1;
	int y0 = (int)y;
	int y1 = y0 + 1;

	// Determine interpolation weights
	// Could also use higher order polynomial/s-curve here
	float sx = x - (float)x0;
	float sy = y - (float)y0;

	// Interpolate between grid point gradients
	float n0, n1, ix0, ix1, value;

	n0 = dotGridGradient(x0, y0, x, y);
	n1 = dotGridGradient(x1, y0, x, y);
	ix0 = lerp(n0, n1, sx);

	n0 = dotGridGradient(x0, y1, x, y);
	n1 = dotGridGradient(x1, y1, x, y);
	ix1 = lerp(n0, n1, sx);

	value = lerp(ix0, ix1, sy);
	return value;
}

float Plane::OctavePerlin(float x, float y, int octaves, float persistence) {
	float total = 0;
	float frequency = 1;
	float amplitude = 1;
	float maxValue = 0;  // Used for normalizing result to 0.0 - 1.0
	for (int i = 0; i < octaves; i++) {
		total += perlin(x * frequency, y * frequency) * amplitude;

		maxValue += amplitude;

		amplitude *= persistence;
		frequency *= 2;
	}

	return total / maxValue;
}


Plane::Plane(int s)
{
	subdivision = s;

	generateNew();

	vertices.resize(subdivision);
	numTriangles = subdivision * 2;
	int minS = sqrt(subdivision);

	texCoords.resize(subdivision);

	for (int i = 0; i < minS; i++)
	{
		for (int j = 0; j < minS; j++)
		{
			float height = OctavePerlin((float)i / frequency, (float)j / frequency, octaves, persistence)*amplitude;
			vertices[i * minS + j] = glm::vec3(i, height, j);

			float xCoord = (float)(j + 1.01) / (float)(minS);
			float yCoord = (float)(i + 1.01) / (float)(minS);
			texCoords[i * minS + j] = glm::vec2(xCoord, yCoord);
		}
	}

	indices.resize(subdivision * 3 * 2);
	for (int i = 0; i < minS - 1; i++)
	{
		for (int j = 0; j < minS-1; j++)
		{
			int ind =  i * minS * 6 + j*6;
			indices[ind] = i * minS + j;
			indices[ind + 1] = i * minS + j + 1;
			indices[ind + 2] = (i + 1) * minS + j + 1;

			indices[ind + 3] = i * minS + j;
			indices[ind + 4] = (i + 1) * minS + j;
			indices[ind + 5] = (i + 1) * minS + j + 1;
		}
	}


	generateBuffers();
}

void Plane::updateVertices()
{
	int minS = sqrt(subdivision);

	for (int i = 0; i < minS; i++)
	{
		for (int j = 0; j < minS; j++)
		{
			float height = OctavePerlin((float)i / frequency, (float)j / frequency, octaves, persistence)*amplitude;
			vertices[i * minS + j] = glm::vec3(i, height, j);
		}
	}

	updateVerticexBuffer();
}

void Plane::generateNew()
{
	//if (Gradient != nullptr) delete[] Gradient;
	srand((unsigned)time(NULL));

	Gradient = new float**[1000];
	for (int i = 0; i < 1000; i++)
	{
		Gradient[i] = new float*[1000];
		for (int j = 0; j < 1000; j++)
		{
			Gradient[i][j] = new float[2];
			Gradient[i][j][0] = rand() % 10;
			Gradient[i][j][1] = rand() % 10;
		}
	}
}