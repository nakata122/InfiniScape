#include "pch.h"

#include <iostream>
#include <thread>
#include <vector>
#include <time.h>
#include <cmath>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Plane.h"

float lerp(float a, float b, float t)
{
	return a * (1 - t) + b * t;
}

float Plane::smoothstep(const float &t) { return t*t*(3.0 - 2.0*t); }

// Compute Perlin noise at coordinates x, y
float Plane::perlin(float x, float y) {
	int size = noiseSize - 1;

	// Determine grid cell coordinates
	int x0 = (int)floor(x) & size;
	int x1 = (x0 + 1) & size;
	int y0 = (int)floor(y) & size;
	int y1 = (y0 + 1) & size;

	// Determine interpolation weights
	float sx = smoothstep(x - floor(x));
	float sy = smoothstep(y - floor(y));

	// Bilinear interpolation
	float n0, n1, ix0, ix1, value;

	n0 = Gradient[y0 * size + x0];
	n1 = Gradient[y0 * size + x1];
	ix0 = lerp(n0, n1, sx);

	n0 = Gradient[y1 * size + x0];
	n1 = Gradient[y1 * size + x1];
	ix1 = lerp(n0, n1, sx);

	value = lerp(ix0, ix1, sy);
	return value;
}

float Plane::OctavePerlin(float x, float y, int octaves, float persistence) {
	float total = 0;
	float frequency = this->frequency;
	float amplitude = 1;
	float maxValue = 0;  // Used for normalizing result to 0.0 - 1.0
	for (int i = 0; i < octaves; i++) {
		total += perlin(x * frequency, y * frequency) * amplitude;

		maxValue += amplitude;

		amplitude *= persistence;
		frequency *= 1.5;
	}

	return total / maxValue;
}


Plane::Plane(int numTriangles)
{
	this->numTriangles = subdivision * subdivision;

	generateNew();

	vertices.resize(numTriangles);
	int minS = subdivision;

	texCoords.resize(numTriangles);
	normals.resize(numTriangles);

	int vertI = 0;
	for (int i = 0; i < minS; i++)
	{
		for (int j = 0; j < minS; j++)
		{
			calculateHeight(i, j, vertI);

			float xCoord = (float)(j + 1.01) / (float)(minS);
			float yCoord = (float)(i + 1.01) / (float)(minS);
			texCoords[vertI] = glm::vec2(xCoord, yCoord);

			vertI++;
		}
	}


	indices.resize(numTriangles * 3 * 2);
	int tempI = 0;
	vertI = 0;
	for (int i = 0; i < minS - 1; i++)
	{
		for (int j = 0; j < minS - 1; j++)
		{
			indices[tempI] = vertI;
			indices[tempI + 1] = vertI + 1;
			indices[tempI + 2] = vertI + minS + 1;

			indices[tempI + 3] = vertI;
			indices[tempI + 4] = vertI + minS;
			indices[tempI + 5] = vertI + minS + 1;


			glm::vec3 d1 = vertices[vertI + 1] - vertices[vertI];
			glm::vec3 d2 = vertices[vertI + minS + 1] - vertices[vertI];
			normals[vertI] = normalize(cross(d1, d2));

			tempI += 6;
			vertI++;
		}
		vertI++;
	}


	generateBuffers();
}

void Plane::calculateHeight(int i, int j, int vIndex)
{
	float height = pow(OctavePerlin((float)i, (float)j, octaves, persistence), elevation) * amplitude;
	if (height < 2) height = 0;
	vertices[vIndex] = glm::vec3((float)i / 2, height, (float)j / 2);
}

void Plane::updateVertices()
{
	int minS = subdivision;

	std::thread uhalf(&Plane::vertexThread, this);

	int vertI = 0;
	for (int i = 0; i < minS - 1; i++)
	{
		for (int j = 0; j < minS - 1; j++)
		{

			glm::vec3 d1 = vertices[vertI + 1] - vertices[vertI];
			glm::vec3 d2 = vertices[vertI + minS + 1] - vertices[vertI];
			normals[vertI] = normalize(cross(d1, d2));

			vertI++;
		}
		vertI++;
	}
	uhalf.join();

	updatePositionBuffers();
}

void Plane::vertexThread()
{
	int minS = subdivision;

	int vertI = 0;
	for (int i = 0; i < minS; i++)
	{
		for (int j = 0; j < minS; j++)
		{
			calculateHeight(i, j, vertI);

			vertI++;
		}
	}
}

void Plane::generateNew()
{
	//if (Gradient != nullptr) delete[] Gradient;
	srand(seed);
	Gradient = new float[noiseSize * noiseSize];
	for (int i = 0; i < noiseSize; i++)
	{
		for (int j = 0; j < noiseSize; j++)
		{
			Gradient[i*noiseSize + j] = (float)(rand() % 100)/100;
		}
	}


	/*Gradient = new float**[noiseSize];
	for (int i = 0; i < noiseSize; i++)
	{
		Gradient[i] = new float*[noiseSize];
		for (int j = 0; j < noiseSize; j++)
		{
			Gradient[i][j] = new float[2];
			Gradient[i][j][0] = rand() % 100;
			Gradient[i][j][1] = rand() % 100;
		}
	}*/
}