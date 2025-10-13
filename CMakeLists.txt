cmake_minimum_required(VERSION 3.10)
project(TestGLFW VERSION 1.0)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)  # 明确要求支持 C++17

#在项目中加入一个全局预编译宏,若不需要可注释掉
add_compile_definitions(DEBUG)

# 添加子目录
add_subdirectory(wrapper)

# 查找 GLFW 库
find_library(GLFW_LIBRARY 
    NAMES glfw3 glfw
    PATHS ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/lib
    NO_DEFAULT_PATH
)

if(NOT GLFW_LIBRARY)
    message(FATAL_ERROR "GLFW library not found in thirdParty/lib")
endif()

# 主程序
add_executable(TestGLFW main.cpp glad.c)

# 链接库
target_link_libraries(TestGLFW PRIVATE ${GLFW_LIBRARY} wrapper)

# 如果主程序直接包含第三方头（如 #include <glad/glad.h>），则保留 SYSTEM PRIVATE
# 否则可删除
target_include_directories(TestGLFW SYSTEM PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/include)