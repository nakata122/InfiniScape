#pragma once

#include <GL/glew.h>

#include "GLObject.h"

class Program
{
protected:
	GLuint programID;
public:
	Program();

	virtual void bindProgram(GLObject &obj);
	void LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
};

