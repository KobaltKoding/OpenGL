#include "Renderer.h"
#include "Logger.h"

//#include <iostream>
//
//
//void GLClearError()
//{
//	while (glGetError() != GL_NO_ERROR);
//
//}
//
//bool GLLogCall(const char* funtion, const char* file, int line)
//{
//	while (GLenum error = glGetError())
//	{
//		std::cout << "opengl error :(" << error << ")" << funtion << "  " << file << ":" << line << std::endl;
//		return false;
//	}
//	return true;
//}


void Renderer::Draw(const VertexArray& va, const IndexBuffer& ib, const Shader& shader) const
{
	shader.Bind();

	va.Bind();
	ib.Bind();
	

	GLCall(glDrawElements(GL_TRIANGLES, ib.GetCount(), GL_UNSIGNED_INT, nullptr));

}

void Renderer::Clear() const
{
	GLCall(glClear(GL_COLOR_BUFFER_BIT));
}