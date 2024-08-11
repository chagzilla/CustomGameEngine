#ifndef POLYGON_H
#define POLYGON_H
#include "../../include/shaders/ShaderProgram.h"
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include "./Shape.h"
#include <vector>

class Polygon: public Shape {
    public:
        Polygon(int s, float r, glm::mat4 * camMat, glm::mat4 * projMat);
        Polygon(glm::mat4 * camMat, glm::mat4 * projMat);
        Polygon(int s, float r, glm::vec3 l, float ratS, glm::mat4 * camMat, glm::mat4 * projMat);
        void init();
        void render();
        void update(float timeSinceLastFrame);
    private:
        void constructVertices();
        std::vector<float> vertices;
        std::vector<int> indices;
        float radius;
        int sides;
        float time;
        float rotSpeed;
};

#endif