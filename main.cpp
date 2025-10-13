#include <iostream>
#include <glad/glad.h>// Include glad before glfw
#include <GLFW/glfw3.h>

/*
*  Create GLFW window
*  set up window event callbacks
*  set up keyboard event callbacks
*/

// implement a framebuffer resize handler
void framebufferSizeCallback(GLFWwindow* window, int width, int height) {
	std::cout << "framebuffer current size: " << width << "x" << height << std::endl;
}
// implement a keyboard input handler
// key:GLFW keycode, scancode:ÎïÀí°´¼üÂë, action:press/release/repeat, mods:modifier keys(e.g. shift/ctrl/alt/super)
void keyCallback(GLFWwindow* window, int key, int scancode, int action, int mods) {
	std::cout << "key: " << key << " scancode: " << scancode << " action: " << action << " mods: " << mods << std::endl;
	if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
		glfwSetWindowShouldClose(window, true);// set the window to close
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

	//3 run the form loop
	while (!glfwWindowShouldClose(window)) {
		// process window messages
		// procese pending input messages from the messagw queue(e.g. keyboard, mouse, etc.)
		// if pending messages exist, process them collectively and clean the queue
		glfwPollEvents();
	}

	//4 perform cleanup before exit
	glfwTerminate();

	return 0;
}