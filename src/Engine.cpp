#include "../include/Engine.h"
#include <iostream>
#include <cstdlib>
#include "../include/shapes/Cube.h"

Engine::Engine() {
    init(800, 600);
}

Engine::Engine(int width, int height) {
    init(width, height);
}

void cursor_position_callback(GLFWwindow* window, double xpos, double ypos)
{
 std::cout << "xpos: " << xpos << std::endl << "ypos: " << ypos << std::endl;
}
void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
} 

void Engine::key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_UP && (action == GLFW_PRESS))
        MOVEUP = true;
    if (key == GLFW_KEY_DOWN && (action == GLFW_PRESS))
        MOVEDOWN = true;
    if (key == GLFW_KEY_RIGHT && (action == GLFW_PRESS))
        MOVERIGHT = true;
    if (key == GLFW_KEY_LEFT && (action == GLFW_PRESS))
        MOVELEFT = true;

    if (key == GLFW_KEY_UP && (action == GLFW_RELEASE))
        MOVEUP = false;
    if (key == GLFW_KEY_DOWN && (action == GLFW_RELEASE))
        MOVEDOWN = false;
    if (key == GLFW_KEY_RIGHT && (action == GLFW_RELEASE))
        MOVERIGHT = false;
    if (key == GLFW_KEY_LEFT && (action == GLFW_RELEASE))
        MOVELEFT = false;
    // vMat = glm::translate(glm::mat4(1.0), cameraLoc);
}

void Engine::mouse_callback(double xPos, double yPos) {
    // std::cout << "Setting new mouse pos: (" << xPos << ", " << yPos << ")" << std::endl;
    // glm::vec3 newPos(xPos, yPos, 0);
    // glm::vec3 oldPos(lastMouseXPos, lastMouseYPos, 0);
    // lastMouseXPos = xPos;
    // lastMouseYPos = yPos;
    // glm::vec3 direction = newPos - oldPos;
    // newPos = glm::normalize(newPos);
    // oldPos = glm::normalize(oldPos);
    // float radians = glm::dot(newPos, oldPos);
    // //std::cout << "radians: " << radians << std::endl;
    // glm::vec3 norm = glm::cross(newPos, oldPos);
    //std::cout << "(" << direction.x << ", " << direction.y << ", " << direction.z << ")" << std::endl;

    // vMat = glm::rotate(vMat, -direction.x * 0.1f, glm::vec3(0, 1, 0));
    // vMat = glm::rotate(vMat, -direction.y * 0.1f, glm::vec3(1, 0, 0));
    //vMat = glm::lookAt(glm::vec3(0.0, 0.0, 8), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 5.0, 0.0)); 

    float xoffset = xPos - lastMouseXPos;
    float yoffset = lastMouseYPos - yPos; 
    lastMouseXPos = xPos;
    lastMouseYPos = yPos;

    float sensitivity = 0.1f;
    xoffset *= sensitivity;
    yoffset *= sensitivity;

    yaw   += xoffset;
    pitch += yoffset;

    if(pitch > 89.0f)
        pitch = 89.0f;
    if(pitch < -89.0f)
        pitch = -89.0f;

    glm::vec3 direction;

    direction.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    direction.y = sin(glm::radians(pitch));
    direction.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    cameraFront = glm::normalize(direction);
    vMat = glm::lookAt(cameraLoc, cameraFront , glm::vec3(0, 1, 0)); // + cameraLoc
}

int Engine::init(int width, int height) {
    if (!glfwInit())
    {
        std::cout << "GLFW Failed to initialize!!!" << std::endl;
    }

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    // if mac os is not working try uncommenting this line
#ifdef __APPLE__
    std::cout << "Running MAC OS setup: " << std::endl;
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE);
#endif

    std::cout << "CREATING glfw window" << std::endl;
    window = glfwCreateWindow(600, 600, "Game Engine", NULL, NULL);
    if (!window)
    {
        // Window or OpenGL context creation failed
        std::cout << "ERROR CREATING glfw window" << std::endl;
    }

    std::cout << "CREATED glfw window" << std::endl;
    glfwMakeContextCurrent(window);
    glfwSetWindowUserPointer(window, this);
    auto key_callback = [](GLFWwindow* w, int i, int n , int t, int y)
    {
        static_cast<Engine*>(glfwGetWindowUserPointer(w))->key_callback(w, i, n, t, y);
    };
    glfwSetKeyCallback(window, key_callback);

    auto mouseFunc = [](GLFWwindow* w, double xpos, double ypos)
    {
        static_cast<Engine*>(glfwGetWindowUserPointer(w))->mouse_callback(xpos, ypos);
    };
    glfwSetCursorPosCallback(window, mouseFunc);


    std::cout << "INITIALIZING GLEW" << std::endl;
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK) {
        std::cout << "FAILED to initialize GLEW" << std::endl;
        exit(EXIT_FAILURE);
    }

    int w, h;
    glfwGetFramebufferSize(window, &w, &h);
    float aspect = (float)w / (float)h;
    pMat = glm::perspective(1.0472f, aspect, 0.1f, 1000.0f);
    UIVMat = glm::mat4(1.0f);
    UIPMat = glm::mat4(1.0f);

    cameraLoc = glm::vec3(0.0, 0.0, 8.0f);
    cameraFront = glm::vec3(0.0, 0.0, -1.0f);
    yaw = -90.0f;
    //vMat = glm::lookAt(glm::vec3(0.0, 0.0, 8), glm::vec3(0.0, 0.0, 0.0), glm::vec3(0.0, 1.0, 0.0));
    //vMat = glm::translate(vMat, cameraLoc);
    //vMat = glm::rotate(vMat, 2.9f, glm::vec3(1.0f, 0, 0));
    c = new Cube(&vMat, &pMat);
    p = new Pyramid(5, 1, 2, &vMat, &pMat);
    poly = new Polygon(10, 0.5f, &UIVMat, &UIPMat);
    for (int i = 0; i < 100; i++) {
        shapes.push_back(Polygon((rand() % 7) + 3, (rand() % 100) / 1000.0f, glm::vec3((rand() % 100) / 50.0f - 1.0f, 1.5 + ((rand() % 100) / 10.0f), 0.0f), ((rand() % 100) / 10.0f), &UIVMat, &UIPMat));
    }

    return 0;
}

void Engine::addShaderProg(ShaderProgram * shaderProg) {
    prog = shaderProg;
}

void Engine::render() {
    /*
        this specifies that the screen will be cleared to a certain color
        in this case red because we specify the color buffer bit
    */
    currentTimeStamp = glfwGetTime();
    timeSinceLastFrame = (currentTimeStamp - lastTimeStamp) / 2;
    lastTimeStamp = currentTimeStamp;

    glClearColor(0, 0.0, 0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

   
    c->render();
    p->render();
    // poly->render();
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i].render();
    }

}

void Engine::update() {
    if (MOVEUP) 
        cameraLoc += cameraFront * (float)timeSinceLastFrame * 10.0f;
    if (MOVEDOWN)
        cameraLoc -= cameraFront * (float)timeSinceLastFrame * 10.0f;
    if (MOVELEFT)
        cameraLoc += (glm::cross(glm::vec3(0, 1, 0), cameraFront) * cameraSpeed * (float)timeSinceLastFrame);
    if (MOVERIGHT)
        cameraLoc -= (glm::cross(glm::vec3(0, 1, 0), cameraFront) * cameraSpeed * (float)timeSinceLastFrame);

    vMat = glm::lookAt(cameraLoc, cameraFront + cameraLoc, glm::vec3(0, 1, 0));
    c->update(timeSinceLastFrame);
    p->update(timeSinceLastFrame);
    // poly->update(timeSinceLastFrame);
    for (int i = 0; i < shapes.size(); i++) {
        shapes[i].update(timeSinceLastFrame);
    }
}

int Engine::run() {

    currentTimeStamp = 0;
    lastTimeStamp = 0;
    timeSinceLastFrame = 0;
    glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
    
    glfwSwapInterval(1);
    glfwGetCursorPos(window, &lastMouseXPos, &lastMouseYPos);

    while (!glfwWindowShouldClose(window))
    {
        update();
        render();
        glfwSwapBuffers(window);
        glfwPollEvents(); 
    }
    glfwDestroyWindow(window);
    glfwTerminate();
    return 0;
}
 
