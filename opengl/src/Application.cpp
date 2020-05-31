//#include<GL/glew.h>
#include <glad\glad.h>
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

#include "glm\glm.hpp"
#include "glm\gtc\matrix_transform.hpp"

#include "imgui\imgui.h"
#include "imgui\imgui_impl_glfw_gl3.h"


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
	window = glfwCreateWindow(960, 540, "Hello World", NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);
	glfwSwapInterval(1);
	

	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	std::cout << glGetString(GL_VERSION) << std::endl;
  {
	float positions[] = {
		 100.0f, 100.0f, 0.0f, 0.0f,
		 400.0f, 100.0f, 1.0f, 0.0f,
		 400.0f, 400.0f, 1.0f, 1.0f,
		 100.0f, 400.0f, 0.0f, 1.0f
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

	glm::mat4 proj = glm::ortho(0.0, 960.0, 0.0, 540.0, -1.0, 1.0);
	glm::mat4 view = glm::translate(glm::mat4(1.0f), glm::vec3(-100, 0, 0));
	


	Shader shader("res/shaders/Basic.shader");
	shader.Bind();
	shader.SetUniform4f("u_Color", 0.2f, 0.3f, 0.8f, 1.0f);
	
	Texture texture("res/textures/kk.png");
	texture.Bind(0);
	shader.SetUniform1i("u_Texture", 0);

	va.Unbind();
	vb.Unbind();
	ib.Unbind();
	shader.Unbind();

	Renderer renderer;

	ImGui::CreateContext();
	ImGui_ImplGlfwGL3_Init(window, true);
	ImGui::StyleColorsDark();

	glm::vec3 translation(200, 200, 0);

	float r = 0.1f, g = 0.9f, b = 0.5f;
	float increment = 0.01f;
	//glClearColor(1.0f, 0.0f, 0.0f, 1.0f);
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		
		renderer.Clear();

		ImGui_ImplGlfwGL3_NewFrame();

		glm::mat4 model = glm::translate(glm::mat4(1.0f),translation);
		glm::mat4 mvp = proj * view * model;


		shader.Bind();
		shader.SetUniform4f("u_Color", r, g, b, 1.0f);
		shader.SetUniformMat4f("u_MVP", mvp);

		
		renderer.Draw(va, ib, shader);

		if (r > 1.0f)
		{
			increment = -0.01f;

		}
		else if (r < 0.0f)
			increment = 0.005f;
		r += increment;
		g -= increment;
		b += increment;
		//glClearColor(r, g, b, 1.0f);

		{

			ImGui::SliderFloat3("Translation", &translation.x, 0.0f, 960.0f);            // Edit 1 float using a slider from 0.0f to 1.0f    
			
			ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
		}

		ImGui::Render();
		ImGui_ImplGlfwGL3_RenderDrawData(ImGui::GetDrawData());

		/* Swap front and back buffers */
		GLCall(glfwSwapBuffers(window));

		/* Poll for and process events */
		GLCall(glfwPollEvents());
	}
	
  }
	ImGui_ImplGlfwGL3_Shutdown();
	ImGui::DestroyContext();

	glfwTerminate();
	return 0;
}
