main中代码为：
	创建基础窗体
	事件回调函数：窗体激活的情况下，用于响应窗口变化、键盘、鼠标等操作信息的函数
2025/9/29
添加查错代码
	GLenum errorCode = glGetError();//检测和获取最近一次的OpenGL的错误代码
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
		}
2025/9/30
添加wrapper文件夹，包装器，用于存放对第三方库的封装
将之前的checkError()函数移到wrapper文件夹中

