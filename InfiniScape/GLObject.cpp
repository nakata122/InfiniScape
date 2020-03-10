#include "pch.h"

#include "GLObject.h"
#include <iostream>

GLObject::GLObject()
{
	Model = glm::mat4(1.0f);
}

void GLObject::draw()
{

	// 1rst attribute buffer : vertices
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(
		0,                  // attribute.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,					// stride
		(GLvoid*)0          // array buffer offset
	);


	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,                  // attribute.
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,					// stride
		(GLvoid*)0          // array buffer offset
	);
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);

	glDrawElements(
		GL_TRIANGLES,      // mode
		indices.size(),    // count
		GL_UNSIGNED_SHORT, // type
		(void*)0           // element array buffer offset
	);
	//glDrawArrays(GL_POINTS, 0, vertices.size());

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
}

GLuint GLObject::getProgramID()
{
	return programID;
}

void GLObject::setMVP(glm::mat4 Projection, glm::mat4 View)
{
	MVP = Projection * View * Model;
}

glm::mat4 GLObject::getMVP()
{
	return MVP;
}

void GLObject::updateBuffers()
{
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), &texCoords[0], GL_STATIC_DRAW);

	glGenBuffers(1, &indexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);
}

void GLObject::addTexture(GLuint texture)
{
	textureID[texCount++] = texture;
}

GLuint GLObject::getTexture(int index)
{
	return textureID[index];
}

GLObject::~GLObject()
{
	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &indexbuffer);
}