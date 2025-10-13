

#将下列文件编译为wrapper静态库
add_library(wrapper STATIC
	src/ checkError.cpp
)

#添加包含目录
target_include_directories(wrapper PUBLIC
	${CMAKE_CURRENT_SOURCE_DIR}/../thirdParty/include
)