#include "../../include/shapes/Shape.h"
#include <iostream>


void Shape::addShaderProg(ShaderProgram * shaderProg) {
    prog = shaderProg;
}

void Shape::setCameraMat(glm::mat4 * camMat) {
    vMat = camMat;
}

void Shape::setProjMat(glm::mat4 * projMat) {
    pMat = projMat;
}

GLuint Shape::shaderProgram() {
    return prog->getProgram();
}
