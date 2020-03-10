#include "pch.h"

#include "GLObject.h"
#include <iostream>


GLObject::GLObject()
{
	Model = glm::mat4(1.0f);
}

void GLObject::draw(glm::mat4 Projection, glm::mat4 View, GLuint MatrixID)
{
	MVP = Projection * View * Model;

	glUniformMatrix4fv(MatrixID, 1, GL_FALSE, &MVP[0][0]);

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
	
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);

	glDrawElements(
		GL_TRIANGLES,      // mode
		indices.size(),    // count
		GL_UNSIGNED_SHORT, // type
		(void*)0           // element array buffer offset
	);
	//glDrawArrays(GL_POINTS, 0, vertices.size());

	glDisableVertexAttribArray(0);
}

void GLObject::updateBuffers()
{
	std::cout << vertices.size() << std::endl;
	glGenBuffers(1, &vertexbuffer);
	glBindBuffer(GL_ARRAY_BUFFER, vertexbuffer);
	glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(glm::vec3), &vertices[0], GL_STATIC_DRAW);

	glGenBuffers(1, &indexbuffer);
	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, indexbuffer);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned short), &indices[0], GL_STATIC_DRAW);
}

GLuint GLObject::getProgramID()
{
	return programID;
}

void GLObject::setProgramID(GLuint id)
{
	programID = id;
}

void GLObject::cleanUp()
{
	// Cleanup VBO
	glDeleteBuffers(1, &vertexbuffer);
	glDeleteProgram(programID);
}