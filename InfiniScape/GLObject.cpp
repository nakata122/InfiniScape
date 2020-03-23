#include "pch.h"

#include "GLObject.h"
#include <iostream>

GLObject::GLObject()
{
	Model = glm::mat4(1.0f);
}

void GLObject::draw()
{

	glBindVertexArray(VertexArrayID);

	glDrawElements(
		GL_TRIANGLES,      // mode
		indices.size(),    // count
		GL_UNSIGNED_INT,   // type
		(void*)0           // element array buffer offset
	);
	//glDrawArrays(GL_POINTS, 0, vertices.size());
	glBindVertexArray(0);
}

GLuint GLObject::getProgramID()
{
	return programID;
}

void GLObject::setMVP(const Camera &camera)
{
	Model = glm::translate(glm::mat4(1.0f), glm::vec3(camera.position.x, camera.position.y-50, camera.position.z));
	MVP = camera.getProjection() * camera.getView() * Model;
}

glm::mat4 GLObject::getMVP()
{
	return MVP;
}

glm::mat4 GLObject::getModel()
{
	return Model;
}

void GLObject::generateBuffers()
{
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);

	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &normalbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), &normals[0], GL_STATIC_DRAW);

	glGenBuffers(1, &uvbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glBufferData(GL_ARRAY_BUFFER, texCoords.size() * sizeof(glm::vec2), &texCoords[0], GL_STATIC_DRAW);

	glGenBuffers(1, &indexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

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

	glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(
		1,                  // attribute.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,					// stride
		(GLvoid*)0          // array buffer offset
	);

	glBindBuffer(GL_ARRAY_BUFFER, uvbuffer);
	glEnableVertexAttribArray(2);
	glVertexAttribPointer(
		2,                  // attribute.
		2,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,					// stride
		(GLvoid*)0          // array buffer offset
	);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBindVertexArray(0);

	glDisableVertexAttribArray(0);
	glDisableVertexAttribArray(1);
	glDisableVertexAttribArray(2);
}

void GLObject::updatePositionBuffers(int startS)
{
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), NULL, GL_STREAM_DRAW);
	glBufferSubData(GL_ARRAY_BUFFER, 0, vertices.size() * sizeof(glm::vec3), &vertices[0]);

	//glBindBuffer(GL_ARRAY_BUFFER, normalbuffer);
	//glBufferData(GL_ARRAY_BUFFER, normals.size() * sizeof(glm::vec3), NULL, GL_STREAM_DRAW);
	//glBufferSubData(GL_ARRAY_BUFFER, 0, normals.size() * sizeof(glm::vec3), normals.data());
}

void GLObject::addTexture(GLuint texture)
{
	textureID.push_back(texture);
}

std::vector<GLuint> &GLObject::getTextures()
{
	return textureID;
}

GLObject::~GLObject()
{
	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteBuffers(1, &indexbuffer);
}