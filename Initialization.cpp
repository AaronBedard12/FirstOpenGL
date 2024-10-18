#include<iostream>
#include<glad/glad.h>
#include<GLFW/glfw3.h>
using namespace std;

/*Declaration of my functions
* I am personally a big fan of having the main function 
* as close to the top as possible
*/
void framebuffer_size_callback(GLFWwindow* window, int width, int height);
void GetInput(GLFWwindow* window);

struct vec3d
{
	float x, y, z;
};

struct triangle
{
	vec3d vertices[3];
};

int main()
{

	const char* vertexShaderSource = "#version 330 core \n"
		"layout (location = 0) in vec3 aPos;\n"
		"void main()\n"
		"{\n"
		"	gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
		"}\n";

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
;
	//Setting up a unit triangle
	struct triangle tri = { {{0.5f, -0.5f, 0}, {-0.5f, -0.5f, 0}, {0, 0.5f, 0}} };

	//This is a vertex buffer, I still am not really sure on what buffers are
	unsigned int VBO;
	glGenBuffers(1, &VBO);
	glBindBuffer(GL_ARRAY_BUFFER, VBO);

	//Populates the buffer
	glBufferData(GL_ARRAY_BUFFER, sizeof(tri.vertices), tri.vertices, GL_STATIC_DRAW);

	//Setting up a vertex shader (Whatever that means)
	unsigned int vertexShader;
	vertexShader = glCreateShader(GL_VERTEX_SHADER);

	glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
	glCompileShader(vertexShader);

	//While the user isn't trying to close the window, it allows the window to update with changes, aswell as takes input
	//This is apparently called the render loop
	while (!glfwWindowShouldClose(window))
	{
		GetInput(window);

		//The top one sets the colour of the window (with stupid american spelling)
		glad_glClearColor(0.2f, 0.0f, 0.3f, 1.0f);
		//A buffer is created with the colour, this clears that bit/those bits.
		glClear(GL_COLOR_BUFFER_BIT);

		glfwSwapBuffers(window);
		glfwPollEvents();
	}

	//The end of the code, closing the window, and turning the code off
	glfwTerminate();
	return 0;
}

void GetInput(GLFWwindow* window)
{
	if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);
}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
	//This updates the viewport so that when I want to resize the window, the context also updates
	glViewport(0, 0, width, height);
}