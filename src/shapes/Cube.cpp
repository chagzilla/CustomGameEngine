#include "../../include/shapes/Cube.h"
#include <iostream>

Cube::Cube(){

    // init(); 
}

Cube::Cube(glm::mat4 * camMat, glm::mat4 * projMat){
    setCameraMat(camMat);
    setProjMat(projMat);
    init(); 
}

void Cube::init() {

    // the initial location is the origin
    cubeLoc = glm::vec3(0.0f, 0.0f, 0.0f);
    mMat = glm::translate(glm::mat4(1.0f), cubeLoc);

    std::vector<std::pair<GLenum, const char *> > sData;
    sData.push_back(std::make_pair(GL_VERTEX_SHADER, "/Users/wilbertchagula/Documents/CustomGameEngine/shaders/shapes/cube/vertShader.glsl"));
    sData.push_back(std::make_pair(GL_FRAGMENT_SHADER, "/Users/wilbertchagula/Documents/CustomGameEngine/shaders/shapes/cube/fragShader.glsl"));
    ShaderProgram * p = new ShaderProgram(sData);
	p->buildProgram();
    addShaderProg(p);

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(1, vbo);

    // figure out how to do this dynamically so I don't have to remember these vertices or to make it easier for other shapes
    float vertexPositions[108] = {
        -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,  1.0f, -1.0f,
         1.0f, -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f, -1.0f,
         1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f, -1.0f,
         1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f, -1.0f, -1.0f,  1.0f, -1.0f, -1.0f,  1.0f,  1.0f,
        -1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f, -1.0f,
         1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f, -1.0f,  1.0f,
        -1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f,  1.0f,
         1.0f,  1.0f,  1.0f, -1.0f,  1.0f,  1.0f, -1.0f,  1.0f, -1.0f,
    };
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertexPositions), vertexPositions, GL_STATIC_DRAW);
}


void Cube::addShaderProg(ShaderProgram * shaderProg) {
    prog = shaderProg;
}

void Cube::update(float timeSinceLastFrame) {
    mMat = glm::rotate(mMat, timeSinceLastFrame, glm::vec3(0.3, 0.5, 0));
    // (*vMat) = glm::rotate(*vMat, 0.1f * timeSinceLastFrame, glm::vec3(0.3, 0.5, 0));
}

void Cube::render() {
    glUseProgram(prog->getProgram());

    GLuint mvLoc, projLoc;
    mvLoc = glGetUniformLocation(prog->getProgram(), "mv_matrix");
    projLoc = glGetUniformLocation(prog->getProgram(), "proj_matrix");

    glm::mat4 mvMat = (*vMat) * (mMat);
    // glm::mat4 mvMat = glm::lookAt(glm::vec3(0.0, 0.0, 3), glm::vec3(0.0, 2.0, 0.0), glm::vec3(0.0, 1.0, 0.0))  * mMat;
    glUniformMatrix4fv(mvLoc, 1, GL_FALSE, glm::value_ptr(mvMat));
    glUniformMatrix4fv(projLoc, 1, GL_FALSE, glm::value_ptr(*pMat));

    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 0, 0);
    glEnableVertexAttribArray(0);

    glEnable(GL_DEPTH_TEST);
    glDepthFunc(GL_LEQUAL);
    glDrawArrays(GL_TRIANGLES, 0, 36);
}

void Cube::setCameraMat(glm::mat4 * camMat) {
    vMat = camMat;
}

void Cube::setProjMat(glm::mat4 * projMat) {
    pMat = projMat;
}

GLuint Cube::shaderProgram() {
    return prog->getProgram();
}
