#ifndef PYRAMID_H
#define PYRAMID_H
#include "../../include/shaders/ShaderProgram.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "./Shape.h"
#include <vector>

class Pyramid: public Shape {
    public:
        Pyramid(float h, float w, float l, glm::mat4 * camMat, glm::mat4 * projMat);
        Pyramid(glm::mat4 * camMat, glm::mat4 * projMat);
        void init();
        void render();
        void update(float timeSinceLastFrame);
    private:
        void constructVertices();
        std::vector<float> vertices;
        std::vector<int> indices;
        float height;
        float length;
        float width;
};

#endif