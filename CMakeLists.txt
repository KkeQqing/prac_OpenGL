#需求的最低cmake程序版本
cmake_minimum_required(VERSION 3.10)

#项目名称
project(TestGLFW VERSION 1.0)

#指定C++标准
set(CMAKE_CXX_STANDARD 17)

#将子目录wrapper添加到构建中
add_subdirectory(wrapper)

#输出程序名及本工程主程序文件
add_executable(TestGLFW main.cpp glad.c )

#向目标添加包含目录(在add_executable后)
target_include_directories(TestGLFW
	SYSTEM PRIVATE
	${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/include
)

#向目标添加链接目录(在add_executable后)
target_link_directories(TestGLFW
	PRIVATE ${CMAKE_CURRENT_SOURCE_DIR}/thirdParty/lib
)

#向目标添加链接库(在add_executable后)
target_link_libraries(TestGLFW 
	PRIVATE 
	glfw3
	wrapper
)

