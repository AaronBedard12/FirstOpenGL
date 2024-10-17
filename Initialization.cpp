#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>


void framebuffer_size_callback(GLFWwindow* window, int width, int height);

int main()
{
	//initializes OpenGL, If We can't, then exit gracefully
	if (!glfwInit())
	{
		fprintf(stderr, "GLFW Initialization failed");
		return -1;
	}

	/*The next two lines tells OpenGL what version we are using.
	* The first one is the major : 3.x
	* The second one is the minor: y.3
	* Therefore, the version is 3.3
	*/
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);

	//This lets OpenGL know that we are using core and not Compatibility
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

	//Creating the window in memory, while setting a pointer to the memory address of it
	GLFWwindow* window = glfwCreateWindow(800, 800, "First Window", NULL, NULL);

	//Error handling, The window might not be insantiated, causing problems, this avoids that
	if (window == NULL)
	{
		fprintf(stderr, "Failed to open window");
		glfwTerminate();
		return -1;
	}
	glfwMakeContextCurrent(window); //Makes the actual window to display

	//Inisializing GLAD so that openGL can interact with graphics card
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
	{
		std::cout << "Failed to initialize GLAD" << std::endl;
		return -1;
	}

	//setting up the coordinates
	glViewport(0, 0, 800, 800);
	//Allows the window to be resized. See the framebuffer_size_callback definition for more info
	glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

	//While the user isn't trying to close the window, it allows the window to update with changes, aswell as takes input
	while (!glfwWindowShouldClose(window))
	{
		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//The end of the code, closing the window, and turning the code off
	glfwTerminate();
	return 0;
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	glViewport(0, 0, width, height);
}