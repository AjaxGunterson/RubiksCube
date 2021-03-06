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
//x by x dimension of cube
const int CUBE_SIZE = 3;
//8 total points required to render a cube, 4 x,y points
const int POINTS_PER_SIDE = 8 * CUBE_SIZE * CUBE_SIZE;
//4 x,y points required to render each square
const int POINTS_PER_SQUARE = 4;
Side currentSide = FRONT;
Cube rubik(CUBE_SIZE);
Point cubePoints(rubik.getSize());
int test = 0;

/*remember to check vsync if running bad, 1 is on 0 is off.
* higher turns cap even lower
*/
int main(int argc, char *argv[])
{
	GLFWwindow* window;

	char name[] = { "Rubik's Cube" };

	//remember to check vsync here
	initializeWindow(window, 600, 600, name, 1);

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

	vector<float> temp = cubePoints.getPoints();
	float *points = &temp[0];

	vector<float> linesTemp = cubePoints.getDemarcations();
	float *lines = &linesTemp[0];

	unsigned int buffer;

	// Create a buffer
	glGenBuffers(1, &buffer);

	// Bind the buffer to vertx attributes
	glBindBuffer(GL_ARRAY_BUFFER, buffer);

	// Init buffer
	//glBufferData(GL_ARRAY_BUFFER, 8 * sizeof(float), points, GL_STATIC_DRAW);
	glBufferData(GL_ARRAY_BUFFER, 4 * sizeof(float), lines, GL_STATIC_DRAW);

	glEnableVertexAttribArray(0);

	//wtf does this do?
	glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);

	shaderUtil.Use();
}

void mainLoop(GLFWwindow *& window) {

	vector<float> temp = cubePoints.getPoints();

	//points to vector
	float *points = &temp[0];

	vector<float> linesTemp = cubePoints.getDemarcations();
	float *lines = &linesTemp[0];

	//double test = 0;
	double lastTime = glfwGetTime();
	int nbFrames = 0;
	int j = 0,
		k = 0;

	/* Loop until the user closes the window */
	while (!glfwWindowShouldClose(window))
	{
		/*Only use ms OR fps, not both*/
		//showMs(nbFrames, lastTime);
		//showFps(nbFrames, lastTime);

		/* Render here */
		glClear(GL_COLOR_BUFFER_BIT);
		

		/*Draw squares*/
		for (int i = 0; i < rubik.getSize() * rubik.getSize() * POINTS_PER_SQUARE; i += POINTS_PER_SQUARE) {

			//Don't want to disrupt i so make fake loop counter here
			k = ((i / POINTS_PER_SQUARE) / CUBE_SIZE);

			//vertexes per square * num of squares
			if ((i % (POINTS_PER_SQUARE * rubik.getSize())) == 0) {
				j = 0;
			}

			switch (rubik.getSide(currentSide)[k][j]) {
			case WHITE:
				glColor3b(127, 127, 127);
				break;
			case BLUE:
				glColor3b(0, 0, 127);
				break;
			case GREEN:
				glColor3b(0, 127, 0);
				break;
			case ORANGE:
				glColor3b(127, 80, 0);
				break;
			case RED:
				glColor3b(127, 0, 0);
				break;
			case YELLOW:
				glColor3b(127, 127, 0);
				break;
			default:
				glColor3b(20, 20, 100);
				break;
			}
			glDrawArrays(GL_QUADS, i, i + POINTS_PER_SQUARE);
			j++;
		}

		//reset fake internal counter
		j = 0;

		glClear(GL_ARRAY_BUFFER);

		//6 * 8 is added to compensate for edge sides
		glBufferData(GL_ARRAY_BUFFER, (rubik.getSize() - 1) * 2 * 4 * sizeof(float) + (6 * 8), lines, GL_STATIC_DRAW);

		/*Draw demarcations*/
		glColor3b(0, 0, 0);
		//2 because points per line
		glDrawArrays(GL_LINES, 0, 4 * (rubik.getSize() - 1) + 6);

		glColor3b(127, 0, 127);
		if (test < rubik.getSize()) {
			glDrawArrays(GL_LINES, (test * 2), 4);
		}
		else {
			glDrawArrays(GL_LINES, (test * 2) + 2, 4);
		}
		

		glClear(GL_ARRAY_BUFFER);

		/* Swap front and back buffers */
		glfwSwapBuffers(window);

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
	if (action == GLFW_RELEASE)
		return;

	switch (key) {
	case GLFW_KEY_ESCAPE:
		glfwSetWindowShouldClose(window, GLFW_TRUE);
		glfwTerminate();
		exit(1);
		break;
	case GLFW_KEY_Q:
		currentSide = FRONT;
		break;
	case GLFW_KEY_W:
		currentSide = BACK;
		break;
	case GLFW_KEY_E:
		currentSide = LEFT;
		break;
	case GLFW_KEY_A:
		currentSide = RIGHT;
		break;
	case GLFW_KEY_S:
		currentSide = TOP;
		break;
	case GLFW_KEY_D:
		currentSide = BOTTOM;
		break;
	case GLFW_KEY_R:
		if (test > rubik.getSize() - 1) {
			test -= rubik.getSize();
		}
		else {
			test += rubik.getSize();
		}
		break;
	case GLFW_KEY_F:
		switch (currentSide) {
		case FRONT:
			currentSide = BACK;
			break;
		case BACK:
			currentSide = LEFT;
			break;
		case LEFT:
			currentSide = RIGHT;
			break;
		case RIGHT:
			currentSide = TOP;
			break;
		case TOP:
			currentSide = BOTTOM;
			break;
		case BOTTOM:
			currentSide = FRONT;
			break;
		}
		break;
	case GLFW_KEY_UP:
		rubik.move(CLOCKWISE, test, currentSide);
		break;
	case GLFW_KEY_DOWN:
		rubik.move(COUNTER_CLOCKWISE, test, currentSide);
		break;
	case GLFW_KEY_RIGHT:
		if (test == rubik.getSize() - 1) { return; }
		
		if (test >= rubik.getSize() * 2 - 1) {return;}
		test++;
		break;
	case GLFW_KEY_LEFT:
		if (test == rubik.getSize()) { return; }

		if (test <= 0) {return;}
		test--;
		break;
	}
}