#include "pch.h"

#include <iostream>
#include <thread>
#include <vector>

#include "Plane.h"
#include "texture.h"


Plane::Plane(int numTriangles)
{

	this->numTriangles = subdivision * subdivision;

	pixels = new GLfloat[numTriangles];
	//glGenTextures(1, &heightmapID);
	//addTexture(heightmapID);

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

			float xCoord = (float)(j + 1) / (float)(minS);
			float yCoord = (float)(i + 1) / (float)(minS);
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
			indices[tempI + 4] = vertI + minS + 1;
			indices[tempI + 5] = vertI + minS;


			glm::vec3 d1 = vertices[vertI + 1] - vertices[vertI];
			glm::vec3 d2 = vertices[vertI + minS + 1] - vertices[vertI];
			normals[vertI] = normalize(cross(d1, d2));

			tempI += 6;
			vertI++;
		}
		vertI++;
	}


	std::thread ahalf(&Plane::pixelThread, this, 0);

	std::thread bhalf(&Plane::pixelThread, this, minS / 4);

	std::thread chalf(&Plane::pixelThread, this, minS / 2);

	std::thread dhalf(&Plane::pixelThread, this, minS * 3 / 4);

	ahalf.join();
	bhalf.join();
	chalf.join();
	dhalf.join();

	generateBuffers();
}

void Plane::calculateHeight(int i, int j, int vIndex)
{
	float height = noise.AdvancedPerlin((float)i + offsetX, (float)j + offsetY);
	if (height < 2) height = 0;
	//float height = noise.getHeight((float)i / 2, (float)j / 2);
	vertices[vIndex] = glm::vec3((float)i, height, (float)j);
}

void Plane::updateVertices()
{
	if (currentCamera != nullptr)
	{
		offsetX = currentCamera->position.x;
		offsetY = currentCamera->position.z;
	}

	std::thread uhalf(&Plane::vertexThread, this, 0);

	uhalf.join(); 

	updatePositionBuffers();
}

void Plane::vertexThread(int startS)
{
	int minS = subdivision;

	int vertI = startS, tempI = 0;

	for (int i = 0; i < minS; i++)
	{
		float height = noise.AdvancedPerlin(startS + minS + 1, (float)i);
		vertices[vertI] = glm::vec3(startS + minS + 1, height, (float)i);

		if (i < minS - 1) {
			indices[tempI] = vertI;
			indices[tempI + 1] = vertI + 1;
			indices[tempI + 2] = vertI + minS * (minS - 1) + 1;

			indices[tempI + 3] = vertI;
			indices[tempI + 4] = vertI + minS * (minS - 1) + 1;
			indices[tempI + 5] = vertI + minS * (minS - 1);
		}

		vertI++;
		tempI += 6;
	}
}

void Plane::indexThread(int startS)
{
	int minS = subdivision;

	int vertI = startS, tempI = 0;
	for (int i = 0; i < minS - 1; i++)
	{
		indices[tempI] = vertI;
		indices[tempI + 1] = vertI + 1;
		indices[tempI + 2] = vertI + minS * (minS - 1) + 1;

		indices[tempI + 3] = vertI;
		indices[tempI + 4] = vertI + minS * (minS - 1) + 1;
		indices[tempI + 5] = vertI + minS * (minS - 1);

		vertI++;
		tempI += 6;
	}
}

void Plane::updateHeightMap()
{
	int minS = subdivision;

	if (currentCamera != nullptr)
	{
		offsetX = currentCamera->position.x;
		offsetY = currentCamera->position.z;
	}
	
	std::thread ahalf(&Plane::pixelThread, this, 0);

	std::thread bhalf(&Plane::pixelThread, this, minS / 4);

	std::thread chalf(&Plane::pixelThread, this, minS / 2);

	std::thread dhalf(&Plane::pixelThread, this, minS * 3 / 4);

	ahalf.join();
	bhalf.join();
	chalf.join();
	dhalf.join();
	
	loadData_custom(minS, heightmapID, pixels);
}

void Plane::pixelThread(int startS)
{
	int minS = subdivision;

	for (int i = startS; i <  startS + minS/4; i++)
	{
		for (int j = 0; j < minS; j++)
		{
			pixels[i*minS + j] = noise.AdvancedPerlin(i + offsetX, j + offsetY);
		}
	}
}


Plane::~Plane()
{
	delete[] pixels;
}