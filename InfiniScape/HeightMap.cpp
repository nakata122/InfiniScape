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
	//TextureID[0] = glGetUniformLocation(programID, "Height");
	TextureID[0] = glGetUniformLocation(programID, "Grass");
	TextureID[1] = glGetUniformLocation(programID, "Snow");
}

void HeightMap::bindProgram(GLObject &obj, Camera &camera)
{
	glUseProgram(programID);

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &(obj.getMVP())[0][0]);
	glUniformMatrix4fv(ModelID, 1, GL_FALSE, &(obj.getModel())[0][0]);
	glUniformMatrix4fv(ViewID, 1, GL_FALSE, &camera.getView()[0][0]);

	for (int i = 0; i < obj.getTextures().size(); i++)
	{
		glActiveTexture(GL_TEXTURE0 + i);
		glBindTexture(GL_TEXTURE_2D, obj.getTextures()[i]);
		glUniform1i(TextureID[i], i);
	}
}