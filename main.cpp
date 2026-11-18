#include <iostream>
#include <glad/glad.h>// Include glad before glfw
#include <GLFW/glfw3.h>
#include <assert.h> // ¶ÏÑÔ
#include "wrapper/checkError.h"

/*
*  Create GLFW window
*  set up window event callbacks
*  set up keyboard event callbacks
* 
*  use GLAD to load all required OpenGL functions for the current current version
*  read and understand the GLAD source code
* 
*  function practice:
*	glViewport: set the viewport size
*	glClearColor: set the clear color
*	glClear(GL_COLOR_BUFFER_BIT): clear the color buffer
*   glfwSwapBuffers(window): swap the front and back buffers
* 
* experience OpenGL error handling mechanism
* encapsulate a function to check for OpenGl errors
* move the error checking code to another .cpp file
* create a macro named GL_CALL(func) to conviniently invoke OpenGL functions with integrated error checking
* use a global processor macro in CMakeLists.txt to control whether error checking is enabled
* 
* implement a singleton Application class 
*/

// implement a framebuffer resize handler
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	std::cout << "framebuffer current size: " << width << "x" << height << std::endl;
	glViewport(0, 0, width, height);// reset the viewport size
}
// implement a keyboard input handler
// key:GLFW keycode, scancode:ÎïÀí°´¼üÂë, action:press/release/repeat, mods:modifier keys(e.g. shift/ctrl/alt/super)
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	std::cout << "key: " << key << " scancode: " << scancode << " action: " << action << " mods: " << mods << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) {
		glfwSetWindowShouldClose(window, true);// set the window to close
	}
}

int main(){
	//1 Initialize GLFW basic settings
	glfwInit();
	glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
	glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 6);// OpenGL version 4.6
	glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);// Use core profile( retained mode)

	//2 Create window
	GLFWwindow* window = glfwCreateWindow(800, 600, "OpenGL Window", NULL, NULL);
	glfwMakeContextCurrent(window);// Make the window's context current

	// set up a callback to handle framebuffer resize events
	glfwSetFramebufferSizeCallback(window, framebufferSizeCallback);
	// set up a callback to handle keyboard input events
	glfwSetKeyCallback(window, keyCallback);

	//use GLAD to load all OpenGL functions for the current version
	if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress)){
		std::cout << "failed to initialize GLAD" << std::endl;
		return -1;
	}

	// set the viewport¡¢clear color
	glViewport(0, 0, 800, 600);
	glClearColor(0.2f, 0.3f, 0.3f, 1.0f);
	//3 run the form loop
	while (!glfwWindowShouldClose(window)) {
		// process window messages
		// procese pending input messages from the messagw queue(e.g. keyboard, mouse, etc.)
		// if pending messages exist, process them collectively and clean the queue
		glfwPollEvents();

		// clear the color buffer
		 GL_CALL(glClear(GL_COLOR_BUFFER_BIT));
		// render

		// swap the front and back buffers
		glfwSwapBuffers(window);
	}

	//4 perform cleanup before exit
	glfwTerminate();

	return 0;
}