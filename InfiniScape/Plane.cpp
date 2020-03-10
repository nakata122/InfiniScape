#include "pch.h"

#include <iostream>
#include <vector>

// Include GLM
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Plane.h"


Plane::Plane(int subdivision)
{
	vertices.resize(subdivision);
	numTriangles = subdivision * 2;
	int minS = sqrt(subdivision);

	texCoords.resize(subdivision);

	for (int i = 0; i < minS; i++)
	{
		for (int j = 0; j < minS; j++)
		{
			vertices[i * minS + j] = glm::vec3(i, (float)(rand()%10)/10, j);

			float xCoord = (float)(j + 1.01) / (float)minS;
			float yCoord = (float)(i + 1.01) / (float)minS;
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


	updateBuffers();
}
