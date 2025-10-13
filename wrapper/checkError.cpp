#include "checkError.h"
#include <glad/glad.h>
#include <iostream>
#include <assert.h>

void checkError(const char* file, int line) {
    GLenum errorCode;
    bool hasError = false;

    // OpenGL allows multiple errors to be queued
    while ((errorCode = glGetError()) != GL_NO_ERROR) { //glGetError():query the most recent OpenGL error 
        hasError = true;

        std::string errorName = "Unknown OpenGL error";
        switch (errorCode) {
        case GL_INVALID_ENUM:
            errorName = "GL_INVALID_ENUM";
            break;
        case GL_INVALID_VALUE:
            errorName = "GL_INVALID_VALUE";
            break;
        case GL_INVALID_OPERATION:
            errorName = "GL_INVALID_OPERATION";
            break;
        case GL_STACK_OVERFLOW:
            errorName = "GL_STACK_OVERFLOW";
            break;
        case GL_STACK_UNDERFLOW:
            errorName = "GL_STACK_UNDERFLOW";
            break;
        case GL_OUT_OF_MEMORY:
            errorName = "GL_OUT_OF_MEMORY";
            break;
        case GL_INVALID_FRAMEBUFFER_OPERATION:
            errorName = "GL_INVALID_FRAMEBUFFER_OPERATION";
            break;
        default:
            break;
        }

        // Print error with location and details
        std::cerr << "OpenGL Error: " << errorName << " (" << errorCode
            << ") at " << file << ":" << line << std::endl;
    }

    // Trigger breakpoint/assertion only if there was an actual error
    // This helps in debugging without stopping in release builds
    assert(!hasError);
}