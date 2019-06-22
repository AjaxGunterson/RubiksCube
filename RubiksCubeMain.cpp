#include <iostream>
#include <string>
#include "RubiksCube.h"
#include <GL\glew.h>
#include <GL\freeglut.h>
#include <GLFW\glfw3.h>
#include "ShaderUtil.h"
#include "Points.h"
#include <math.h>
#include <vector>

using namespace std;

//prototypes
int initializeWindow(GLFWwindow *&window, int xRes, int yRes, char* applicationName, int vsync);
void initUtils(ShaderUtil &shaderUtil);
void mainLoop(GLFWwindow *& window);
void showFps(int &nbFrames, double &time);
void showMs(int &nbFrames, double &time);
void framebuffer_size_callback(GLFWwindow *window, int width, int height);
void key_callback(GLFWwindow *window, int key, int scancode, int action, int mods);

//global variables
const int CUBE_SIZE = 3;
const int POINTS_PER_SIDE = 8 * CUBE_SIZE * CUBE_SIZE;
int test = 0;

int main(int argc, char *argv[])
{
	GLFWwindow* window;

	Cube rubik(CUBE_SIZE);

	Point cubePoints(CUBE_SIZE);
	
	char name[] = {"Rubik's Cube"};

	initializeWindow(window, 400, 400, name, 1);

	GLenum err = glewInit();
	if (GLEW_OK != err)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		cout << "Error: %s\n", glewGetErrorString(err);
	}
	else
	{
		cout << "Status: Using GLEW " << glewGetString(GLEW_VERSION) << endl;

		// TODO: Create and compile shaders here (vertex and fragment shaders)
		// and finally draw something with modern OpenGL!
		ShaderUtil shaderUtil;

		initUtils(shaderUtil);

		glfwSetKeyCallback(window, key_callback);
		glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);

		mainLoop(window);

		shaderUtil.Delete();

	}

	glfwTerminate();

	return 0;
}

int initializeWindow(GLFWwindow *&window, int xRes, int yRes, char* applicationName, int vsync) {
	
	/* Initialize the library */
	if (!glfwInit())
		return -1;

	/* Create a windowed mode window and its OpenGL context */
	window = glfwCreateWindow(xRes, yRes, applicationName, NULL, NULL);
	if (!window)
	{
		glfwTerminate();
		return -1;
	}

	/* Make the window's context current */
	glfwMakeContextCurrent(window);

	//vsync
	glfwSwapInterval(vsync);
}

void initUtils(ShaderUtil &shaderUtil) {
	shaderUtil.Load("shaders/vs.shader", "shaders/fs.shader");

	// Points for triangle
	float points[8] = {

		// bottom Left
		-0.2f, -0.2f,

		// top left
		-0.2f, 0.2f,

		//top right
		0.2f, 0.2f,

		//bottom Right
		0.2f, -0.2f

	};

	unsigned int buffer;

	// Create a buffer
	glGenBuffers(1, &buffer);

	// Bind the buffer to vertx attributes
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// Init buffer
	glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), points, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	//wtf does this do?
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	shaderUtil.Use();
}

void mainLoop(GLFWwindow *& window) {


	vector<float> squarePoints = {

		// bottom Left
		-0.2f, -0.2f,

		// top left
		-0.2f, 0.2f,

		//top right
		0.2f, 0.2f,

		//bottom Right
		0.2f, -0.2f

	};

	//points to vector
	float *points = &squarePoints[0];

	// Points for triangle
	//float points[8] = Point::triangle;
	float pointso[8];

	//double test = 0;
	double lastTime = glfwGetTime();
	int nbFrames = 0;
	
	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/*Only use ms OR fps*/
		//showMs(nbFrames, lastTime);
		showFps(nbFrames, lastTime);

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);

		// Draw triangle

		glColor3b(0, test, 0);
		glDrawArrays(GL_QUADS, 0, 4);

		//glDrawArrays(GL_TRIANGLES, test, 3);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

		if (test < 100)
			test++;

		glBufferData(GL_ARRAY_BUFFER, POINTS_PER_SIDE * sizeof(float), points, GL_STATIC_DRAW);

		/* Poll for and process events */
		glfwPollEvents();
	}
}

void showMs(int &nbFrames, double &lastTime) {
	double currentTime = glfwGetTime();
	nbFrames++;
	if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
		// printf and reset timer
		printf("%f ms/frame\n", 1000.0 / double(nbFrames));
		nbFrames = 0;
		lastTime += 1.0;
	}
}

void showFps(int &nbFrames, double &lastTime) {
	double currentTime = glfwGetTime();
	nbFrames++;
	if (currentTime - lastTime >= 1.0) { // If last prinf() was more than 1 sec ago
		// printf and reset timer
		cout << "FPS: " << double(nbFrames) << endl;
		nbFrames = 0;
		lastTime += 1.0;
	}
}

void framebuffer_size_callback(GLFWwindow *window, int width, int height) {
	if (height <= 0)
		height = 1;
	float aspectRation = (float)width / height;
	glViewport(0, 0, width, height);
	/*glMatrixMode(glresize)*/
}

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	switch (key) {
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		glfwTerminate();
		exit(1);
		break;
	case GLFW_KEY_K:
		test = 0;
		break;
	}
}