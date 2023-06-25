#include "include/shaders/ShaderProgram.h"
#include "include/Engine.h"
#include <iostream>
#include <vector>

int main() {
    Engine game;
    std::vector<std::pair<GLenum, const char *> > sData;
	// sData.push_back(std::make_pair(GL_VERTEX_SHADER, "/Users/wilbertchagula/Documents/CustomGameEngine/shaders/offsetVShader.glsl"));
	// // sData.push_back(std::make_pair(GL_TESS_CONTROL_SHADER, "/Users/wilbertchagula/Documents/CustomGameEngine/shaders/tcsShader.glsl"));
	// // sData.push_back(std::make_pair(GL_TESS_EVALUATION_SHADER, "/Users/wilbertchagula/Documents/CustomGameEngine/shaders/tesShader.glsl"));
	// sData.push_back(std::make_pair(GL_FRAGMENT_SHADER, "/Users/wilbertchagula/Documents/CustomGameEngine/shaders/fragShader.glsl"));
	// // sData.push_back(std::make_pair(GL_GEOMETRY_SHADER, "/Users/wilbertchagula/Documents/CustomGameEngine/shaders/geoShader.glsl"));
	// ShaderProgram p(sData);
	// p.buildProgram();
    // game.addShaderProg(&p);
    // GLuint vao;
    // std::cout << "creating vertex arrays" << std::endl;
    // glGenVertexArrays(1, &vao);
    // std::cout << "vertex array created" << std::endl;
    // glBindVertexArray(vao);

    int status = game.run();
    // glDeleteVertexArrays(1, &vao);
    // glDeleteProgram(p.getProgram());
    return status;
}