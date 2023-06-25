#include "../../include/shaders/Shader.h"
#include <fstream>
#include <cstring>
#include <iostream>
Shader::Shader(GLenum sType) {
	shader = glCreateShader(sType);
	shaderType = sType;	
}

void Shader::readFile(const char * shaderSrcPath) {
	std::ifstream fileStream(shaderSrcPath, std::ios::in);
	std::string line = "";
	std::cout << "Reading contents of file: " << shaderSrcPath << std::endl;
	while (!fileStream.eof()) {
		getline(fileStream, line);
		sourceCode.append(line + "\n");
	}
	std::cout << "Finished reading file" << std::endl;
	fileStream.close();	
	std::cout << "File closed" << std::endl;
}

void Shader::compileShader(const char * shaderSrcPath) {
	
	GLint shaderCompiled;
	readFile(shaderSrcPath);
	const char * src = sourceCode.c_str();
	std::cout << "adding source" << std::endl;
	glShaderSource(shader, 1, &src, NULL);
	std::cout << "compiling shader" << std::endl;
	glCompileShader(shader);
	checkOpenGLError();
	glGetShaderiv(shader, GL_COMPILE_STATUS, &shaderCompiled);
	if (shaderCompiled != 1) {
		if (shaderType == 35633) std::cout << "Vertex ";
		if (shaderType == 36488) std::cout << "Tess Control ";
		if (shaderType == 36487) std::cout << "Tess Eval ";
		if (shaderType == 36313) std::cout << "Geometry ";
		if (shaderType == 35632) std::cout << "Fragment ";
		std::cout << "shader compilation error." << std::endl;
		printShaderLog(shader);
	}
}

bool Shader::checkOpenGLError() {
	bool foundError = false;
	int glErr = glGetError();
	while (glErr != GL_NO_ERROR) {
		std::cout << "glError: " << glErr << std::endl;
		foundError = true;
		glErr = glGetError();
	}
	
	return foundError;
}

void Shader::printShaderLog(GLuint shader) {
	int len = 0;
	int chWrittn = 0;
	char * log;
	glGetShaderiv(shader, GL_INFO_LOG_LENGTH, &len);
	if (len > 0) {
		log = (char *)malloc(len);
		glGetShaderInfoLog(shader, len, &chWrittn, log);
		std::cout << "Shader Info Log: " << log << std::endl;
		free(log);
	}
}

Shader::~Shader() {
	if (shaderType != 0) {
		glDeleteShader(shader);
	}
}
