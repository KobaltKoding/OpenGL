#include "VertexBuffer.h"
//#include "Renderer.h"
#include "Logger.h"


VertexBuffer::VertexBuffer(const void* data, unsigned int size)
{
	GLCall(glGenBuffers(1, &m_RendererID)); // create vertex buffer,
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // bind buffer
	GLCall(glBufferData(GL_ARRAY_BUFFER, size , data, GL_STATIC_DRAW)); //add data tu buffer
}

VertexBuffer::~VertexBuffer()
{
	GLCall(glDeleteBuffers(1, &m_RendererID));

}

void VertexBuffer::Bind() const 
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, m_RendererID)); // bind buffer
}

void VertexBuffer::Unbind() const
{
	GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0)); // bind buffer
}

