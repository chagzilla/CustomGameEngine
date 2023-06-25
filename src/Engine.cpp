#include "../include/Engine.h"
#include <iostream>
#include "../include/shapes/Cube.h"

Engine::Engine() {
    init(800, 600);
}

Engine::Engine(int width, int height) {
    init(width, height);
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
    auto func = [](GLFWwindow* w, int i, int n , int t, int y)
    {
        static_cast<Engine*>(glfwGetWindowUserPointer(w))->key_callback(w, i, n, t, y);
    };
    glfwSetKeyCallback(window, func);


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

    cameraLoc = glm::vec3(0.0, 0.0, -8.0f);
    vMat = glm::translate(glm::mat4(1.0), cameraLoc);
    c = new Cube(&vMat, &pMat);

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

    glClearColor(0, 1.0, 0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_DEPTH_BUFFER_BIT);

    c->render();
}

void Engine::update() {
    if (MOVEUP) 
        cameraLoc.y -= cameraSpeed * timeSinceLastFrame;
    if (MOVEDOWN)
        cameraLoc.y += cameraSpeed * timeSinceLastFrame;
    if (MOVELEFT)
        cameraLoc.x += cameraSpeed * timeSinceLastFrame;
    if (MOVERIGHT)
        cameraLoc.x -= cameraSpeed * timeSinceLastFrame;

    vMat = glm::translate(glm::mat4(1.0), cameraLoc);
    c->update(timeSinceLastFrame);
}

int Engine::run() {

    currentTimeStamp = 0;
    lastTimeStamp = 0;
    timeSinceLastFrame = 0;

    glfwSwapInterval(1);
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
 