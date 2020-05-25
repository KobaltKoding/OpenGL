#include "Logger.h"

#include <iostream>

void GLClearError()
{
	while (glGetError() != GL_NO_ERROR);

}

bool GLLogCall(const char* funtion, const char* file, int line)
{
	while (GLenum error = glGetError())
	{
		std::cout << "opengl error :(" << error << ")" << funtion << "  " << file << ":" << line << std::endl;
		return false;
	}
	return true;
}