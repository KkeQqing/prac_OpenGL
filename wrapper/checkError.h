#pragma once

// preprocessor macro
#ifdef DEBUG
#define GL_CALL(func) do { \
    func; \
    checkError(__FILE__, __LINE__); \
} while(0)
#else
#define GL_CALL(func) (func)
#endif // invoke checkError() exclusively in debug mode


void checkError(const char* file, int line);