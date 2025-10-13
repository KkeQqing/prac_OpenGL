#include "checkError.h"
#include <glad/glad.h>
#include <iostream>
#include <assert.h>

void checkError() {
	// check for OpenGL errors
	GLenum errorCode = glGetError();// query the most recent OpenGL error 
	std::string error = "";
	if (!errorCode == GL_NO_ERROR) {
		switch (errorCode) {
		case GL_INVALID_ENUM:
			error = "GL_INVALID_ENUM"; break;
		case GL_INVALID_VALUE:
			error = "GL_INVALID_VALUE"; break;
		case GL_INVALID_OPERATION:
			error = "GL_INVALID_OPERATION"; break;
		case GL_OUT_OF_MEMORY:
			error = "GL_INVALID_MEMORY"; break;
		default:
			error = "unknown error"; break;
		}
		std::cout << error << std::endl;
		assert(false);// trigger a breakpoint if in debug mode
	}
}