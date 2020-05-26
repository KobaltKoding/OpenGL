#include<GL/glew.h>
#include <GLFW/glfw3.h>

#include<iostream>
#include<fstream>
#include<string>
#include<sstream>


#include "Renderer.h"
#include "VertexBuffer.h"
#include "VertexBufferLayout.h"
#include "IndexBuffer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "Logger.h"
#include "Texture.h"


int main(void)
{
	GLFWwindow* window;

	/* Initialize the library */
	if (!glfwInit())
		return -1;
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(640, 640, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(2);
	
	if (glewInit() != GLEW_OK)
		std::cout << "Error!!" << std::endl;

	std::cout << glGetString(GL_VERSION) << std::endl;
  {
	float positions[] = {
		-0.75f,-0.75f, 0.0f, 0.0f,
		 0.75f, -0.75f, 1.0f, 0.0f,
		 0.75f,  0.75f, 1.0f, 1.0f,
		-0.75f,  0.75f, 0.0f, 1.0f
	};

	unsigned int indices[] = {
		0,1,2,
		2,3,0
	};

	GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));
	GLCall(glEnable(GL_BLEND));

	VertexArray va;
	VertexBuffer vb(positions, 4 * 4 * sizeof(float));

	VertexBufferLayout layout;
	layout.Push<float>(2);
	layout.Push<float>(2);
	va.AddBuffer(vb,layout);


	IndexBuffer ib(indices, 6);

	Shader shader("res/shaders/Basic.shader");
	shader.Bind();
	//shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
	
	Texture texture("res/textures/kk.png");
	texture.Bind(0);
	shader.SetUniform1i("u_Texture", 0);

	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();

	Renderer renderer;

	float r = 0.1f, g = 0.9f, b = 0.5f;
	float increment = 0.1f;
	glClearColor(0.0f, 0.0f, 0.3f, 1.0f);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		
		renderer.Clear();

		shader.Bind();
		shader.SetUniform4f("u_Color", r, g, b, 1.0f);
		
		renderer.Draw(va, ib, shader);

		if (r > 1.0f)
		{
			increment = -0.1f;

		}
		else if (r < 0.0f)
			increment = 0.05f;
		r += increment;
		g -= increment;
		b += increment;


		/* Swap front and back buffers */
		GLCall(glfwSwapBuffers(window));

		/* Poll for and process events */
		GLCall(glfwPollEvents());
	}
	
  }
	glfwTerminate();
	return 0;
}
