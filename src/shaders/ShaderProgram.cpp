#include "../../include/shaders/Shader.h"
#include "../../include/shaders/ShaderProgram.h"
#include <fstream>
#include <cstring>
#include <iostream>

ShaderProgram::ShaderProgram() {
	prog = glCreateProgram();
}

ShaderProgram::ShaderProgram(std::vector<std::pair<GLenum, const char *> > sData) {
	prog = glCreateProgram();
	for (int i = 0; i < sData.size(); i++) {
		Shader s(sData[i].first);
		s.compileShader(sData[i].second);
		addShader(&s);
	}
}

void ShaderProgram::printProgramLog(int prog) {
   int len = 0;
   int chWrittn = 0;
   char *log;
   glGetProgramiv(prog, GL_INFO_LOG_LENGTH, &len);
   if (len > 0) {
      log = (char *)malloc(len);
      glGetProgramInfoLog(prog, len, &chWrittn, log);
      std::cout << "Program Info Log: " << log << std::endl;
      free(log);
   }
}

void ShaderProgram::buildProgram() {
   GLint linked;  
   glLinkProgram(prog);
   std::cout << "gl program created" << std::endl;
   glGetProgramiv(prog, GL_LINK_STATUS, &linked);
   if (linked != 1)
   {
      std::cout << "linking failed" << std::endl;
      printProgramLog(prog);
   }
}

void ShaderProgram::addShader(Shader * s) {
	glAttachShader(prog, s->getShader());
}
