#ifndef SHADER_H
#define SHADER_H
#define GLEW_STATIC
#include <string>
#include <GL/glew.h>
#include <vector>
class Shader {
	private:
		std::string sourceCode;
		GLenum shaderType;
		GLuint shader;
		std::vector<Shader*> shaders;
		void readFile(const char * shaderSrcPath);
		bool checkOpenGLError();
		void printShaderLog(GLuint shader);
		void printProgramLog(int prog);
	public:
		Shader(GLenum sType);
		~Shader();
		void compileShader(const char * shaderSrcPath);
		std::string getSourceCode() { return sourceCode; }
		GLuint getShader() { return shader; }
		GLenum getShaderType() { return shaderType; }
		GLuint buildProgram();
};
#endif