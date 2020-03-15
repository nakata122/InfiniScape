#include "pch.h"
#include "HeightMap.h"
#include <iostream>
using namespace std;



HeightMap::HeightMap()
{
	LoadShaders("heightmap.vertexshader", "heightmap.fragmentshader");

	MatrixID = glGetUniformLocation(programID, "MVP");
	ModelID = glGetUniformLocation(programID, "M");
	ViewID = glGetUniformLocation(programID, "V");
	Texture1ID = glGetUniformLocation(programID, "Grass");
	Texture2ID = glGetUniformLocation(programID, "Snow");
}

void HeightMap::bindProgram(GLObject &obj, Camera &camera)
{
	glUseProgram(programID);

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(obj.getMVP())[0][0]);
	glUniformMatrix4fv(ModelID, 1, GL_FALSE, &(obj.getModel())[0][0]);
	glUniformMatrix4fv(ViewID, 1, GL_FALSE, &camera.getView()[0][0]);


	// Bind our texture in Texture Unit 0
	glActiveTexture(GL_TEXTURE0);
	glBindTexture(GL_TEXTURE_2D, obj.getTexture(0));
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(Texture1ID, 0);


	// Bind our texture in Texture Unit 1
	glActiveTexture(GL_TEXTURE1);
	glBindTexture(GL_TEXTURE_2D, obj.getTexture(1));
	// Set our "myTextureSampler" sampler to use Texture Unit 0
	glUniform1i(Texture2ID, 1);
}