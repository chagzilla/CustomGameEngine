#ifndef CUBE_H
#define CUBE_H
#include "../../include/shaders/ShaderProgram.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "./Shape.h"

class Cube: public Shape {
    public:
        Cube();
        Cube(glm::mat4 * camMat, glm::mat4 * projMat);
        void render();
        void update(float timeSinceLastFrame);
        void init();
};

#endif