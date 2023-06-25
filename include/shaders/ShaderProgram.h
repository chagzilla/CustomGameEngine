#ifndef SHADERPROGRAM_H
#define SHADERPROGRAM_H
#include <vector>
// #include <OpenGL/gl.h>
#include "Shader.h"
class ShaderProgram {
	private:
		GLuint prog;
		GLuint prepareShader(GLenum sType, const char * sPath);
		void printProgramLog(int prog);
	public:
		ShaderProgram();
		ShaderProgram(std::vector<std::pair<GLenum, const char *> > sData);
		void addShader(Shader * s);
		void buildProgram(); 
		GLuint getProgram() {  return prog; }
};
#endif