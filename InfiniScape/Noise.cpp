#include "Noise.h"

#include <cmath>
#include<iostream>


Noise::Noise(int seed)
{
	this->seed = seed;
	generateNew();
	generateMountain(0, 0);
}

float lerp(float a, float b, float t)
{
	return a * (1 - t) + b * t;
}

float smoothstep(const float &t) { return t * t * (3 - 2 * t); }

void Noise::generateNew()
{
	//if (Gradient != nullptr) delete[] Gradient;
	srand(seed);
	Gradient = new float[noiseSize * noiseSize];
	for (int i = 0; i < noiseSize; i++)
	{
		for (int j = 0; j < noiseSize; j++)
		{
			Gradient[i*noiseSize + j] = (float)(rand() % 100) / 100;
		}
	}

}

// Compute Perlin noise at coordinates x, y
float Noise::perlin(float x, float y) {
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

float Noise::OctavePerlin(float x, float y) {
	float total = 0;
	float frequency = this->frequency;
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

float Noise::AdvancedPerlin(float x, float y)
{
	return pow(OctavePerlin(x, y), elevation) * amplitude;
}

void divide(std::vector<Line> &curve)
{
	float newX = 0, newY = 0;

	int size = curve.size();
	for (int i = 0; i < size; i++)
	{
		float deltaX = (float)(rand() % 20) - 10;
		float deltaY = (float)(rand() % 20) - 10;

		newX = (curve[i].start.x + curve[i].end.x) / 2;
		newY = (curve[i].start.y + curve[i].end.y) / 2;

		newX = (int)newX;
		newY = (int)newY;

		glm::vec2 temp = curve[i].end;
		curve[i].end = glm::vec2(newX, newY);
		curve.push_back(Line(glm::vec2(newX, newY), temp));
		if(rand() % 100 > 90)
			curve.push_back(Line(glm::vec2(newX, newY), glm::vec2(newX + deltaX, newY + deltaY)));
	}
}

void Noise::generateMountain(float x, float y)
{
	srand(seed);
	curve.push_back(Line(glm::vec2(x, y), glm::vec2(100, 100)));
	for (int i = 0; i < 3; i++)
	{
		divide(curve);
	}
}

float max(float a, float b)
{
	return a < b ? b : a;
}

float Noise::getHeight(float x, float y)
{
	float strength = frequency;
	float final = 0;
	for (int i = 0; i < curve.size(); i++)
	{
		glm::vec2 start = curve[i].start;
		glm::vec2 end = curve[i].end;
		float distance = abs((end.y - start.y) * x - (end.x - start.x) * y + end.x * start.y - end.y * start.x)/glm::distance(start, end);
		final += smoothstep(max(0, strength - distance));
		//float distance = glm::dot(start, glm::vec2(x,y));
		//final += distance;
	}

	return final;
}

Noise::~Noise()
{
	delete[] Gradient;
}
