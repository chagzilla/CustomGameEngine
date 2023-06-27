#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <glm/glm.hpp>
#include "../include/shaders/ShaderProgram.h"
#include "./shapes/Cube.h"

class Engine {
    public:
        Engine();
        Engine(int width, int height);
        void addShaderProg(ShaderProgram * prog);
        int run();
    private:
        float cameraSpeed = 10;
        Cube * c; 
        float pitch, yaw;
        glm::mat4 vMat, pMat;
        glm::vec3 cameraLoc;
        glm::vec3 cameraFront;
        GLFWwindow * window;
        ShaderProgram * prog;
        bool MOVEUP, MOVEDOWN, MOVELEFT, MOVERIGHT;
        double lastMouseXPos, lastMouseYPos;
        double currentTimeStamp;
        double lastTimeStamp;
        double timeSinceLastFrame;
        float offset;
        float dir;
        GLuint vao[10];
        int numVAOs = 1;
        int init(int width, int height);
        void render();
        void update();
        void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);
        void mouse_callback(double xPos, double yPos);
};