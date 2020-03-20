#pragma once

#include<vector>
// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

struct Line {
	glm::vec2 start, end;
	Line(glm::vec2 s, glm::vec2 e) : start(s), end(e) {}
};

class Noise
{
	float *Gradient;
	std::vector<Line> curve;
public:
	//Perlin noise parameters
	int noiseSize = 256;
	float elevation = 1;
	float frequency = 0.05;
	float amplitude = 50;
	float persistence = 1;
	int octaves = 1;
	int seed = 0;

	Noise(int seed = 0);
	~Noise();

	void generateNew();
	float AdvancedPerlin(float x, float y);
	float OctavePerlin(float x, float y);
	float perlin(float x, float y);

	void generateMountain(float x, float y);
	float getHeight(float x, float y);
};

