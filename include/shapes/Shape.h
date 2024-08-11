#ifndef SHAPE_H
#define SHAPE_H
#include "../../include/shaders/ShaderProgram.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Shape {
    public:
        void addShaderProg(ShaderProgram * shaderProg);
        void setCameraMat(glm::mat4 * camMat);
        void setProjMat(glm::mat4 * projMat);
        GLuint shaderProgram();
        glm::mat4 * vMat;
        glm::mat4 * pMat;
    protected:
        glm::vec3 loc;
        glm::mat4 mMat;
        ShaderProgram * prog;
        GLuint vao[1];
        GLuint vbo[2];
};

#endif