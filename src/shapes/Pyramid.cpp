#include "../../include/shapes/Pyramid.h"
#include <iostream>

Pyramid::Pyramid(float h, float w, float l, glm::mat4 * camMat, glm::mat4 * projMat){
    height = h;
    width = w;
    length = l;

    setCameraMat(camMat);
    setProjMat(projMat);
    constructVertices();
    init(); 
}

Pyramid::Pyramid(glm::mat4 * camMat, glm::mat4 * projMat){
    std::cout << "Initializing the Pyramid" << std::endl;
    // Pyramid(1.0f, 1.0f, 1.0f, camMat, projMat);
    height = 1.0;
    width = 1.0;
    length = 1.0;

    setCameraMat(camMat);
    setProjMat(projMat);
    constructVertices();
    init(); 
}

void Pyramid::init() {

    // the initial location is the origin
    loc = glm::vec3(3.0f, 0.0f, -5.0f);
    mMat = glm::translate(glm::mat4(1.0f), loc);

    std::vector<std::pair<GLenum, const char *> > sData;
    sData.push_back(std::make_pair(GL_VERTEX_SHADER, "/Users/wilbertchagula/Documents/CustomGameEngine/shaders/shapes/pyramid/vertShader.glsl"));
    sData.push_back(std::make_pair(GL_FRAGMENT_SHADER, "/Users/wilbertchagula/Documents/CustomGameEngine/shaders/shapes/pyramid/fragShader.glsl"));
    ShaderProgram * p = new ShaderProgram(sData);
	p->buildProgram();
    addShaderProg(p);

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(2, vbo);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * 4, &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * 4, &indices[0], GL_STATIC_DRAW);

}

void Pyramid::update(float timeSinceLastFrame) {
     mMat = glm::rotate(mMat, timeSinceLastFrame, glm::vec3(0.3, 0.5, 0));
    // vertices[1] = vertices[1] + timeSinceLastFrame * height;
    // glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * sizeof(float), &vertices[0]);
    // (*vMat) = glm::rotate(*vMat, 0.1f * timeSinceLastFrame, glm::vec3(0.3, 0.5, 0));
}

void Pyramid::render() {
    glBindVertexArray(vao[0]);
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
    glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);

}

void Pyramid::constructVertices() {
    vertices.push_back(0.0f);
    vertices.push_back(height / 2.0f);
    vertices.push_back(0.0f);

    vertices.push_back(-width / 2.0f);
    vertices.push_back(-height / 2.0f);
    vertices.push_back(length / 2.0f);

    vertices.push_back(width / 2.0f);
    vertices.push_back(-height / 2.0f);
    vertices.push_back(length / 2.0f);

    vertices.push_back(width / 2.0f);
    vertices.push_back(-height / 2.0f);
    vertices.push_back(-length / 2.0f);

    vertices.push_back(-width / 2.0f);
    vertices.push_back(-height / 2.0f);
    vertices.push_back(-length / 2.0f);



    // for (int i = 0; i < vertices.size(); i++) {
    //     std::cout << vertices[i] << std::endl;
    // }

    indices = {
        0, 1, 2,
        0, 2, 3,
        0, 3, 4,
        0, 4, 1,
        1, 4, 2,
        4, 3, 2
    };
}
