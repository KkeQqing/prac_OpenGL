
#将下列文件编译为wrapper静态库
add_library(wrapper STATIC
    src/ checkError.cpp
)

# 暴露第三方头文件路径给链接此库的目标
target_include_directories(wrapper PUBLIC
    ${CMAKE_CURRENT_SOURCE_DIR}/../thirdParty/include
)