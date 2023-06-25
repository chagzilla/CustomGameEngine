#ifndef CUBE_H
#define CUBE_H
#include "../../include/shaders/ShaderProgram.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>


class Cube {
    public:
        Cube();
        Cube(glm::mat4 * camMat, glm::mat4 * projMat);
        void render();
        void update(float timeSinceLastFrame);
        void init();
        void addShaderProg(ShaderProgram * shaderProg);
        void setCameraMat(glm::mat4 * camMat);
        void setProjMat(glm::mat4 * projMat);
        GLuint shaderProgram();
    private:
        glm::vec3 cubeLoc;
        glm::mat4 mMat;
        glm::mat4 * vMat;
        glm::mat4 * pMat;
        ShaderProgram * prog;
        GLuint vao[1];
        GLuint vbo[1];
};

#endif