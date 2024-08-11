#include "../../include/shapes/Polygon.h"
#include <iostream>

Polygon::Polygon(int s, float r, glm::mat4 * camMat, glm::mat4 * projMat){
    sides = s;
    radius = r;
    rotSpeed = 1.0f;
    loc = glm::vec3(-0.5f, 0.5f, 0.0f);

    setCameraMat(camMat);
    setProjMat(projMat);
    constructVertices();
    init(); 
}

Polygon::Polygon(int s, float r, glm::vec3 l, float rotS, glm::mat4 * camMat, glm::mat4 * projMat){
    sides = s;
    radius = r;
    loc = l;
    rotSpeed = rotS;

    setCameraMat(camMat);
    setProjMat(projMat);
    constructVertices();
    init(); 
}

Polygon::Polygon(glm::mat4 * camMat, glm::mat4 * projMat){
    sides = 4;
    radius = 1;
    loc = glm::vec3(-0.5f, 0.5f, 0.0f);
    
    setCameraMat(camMat);
    setProjMat(projMat);
    constructVertices();
    init(); 
}

void Polygon::init() {

    // the initial location is the origin
    mMat = glm::translate(glm::mat4(1.0f), loc);

    std::vector<std::pair<GLenum, const char *> > sData;
    sData.push_back(std::make_pair(GL_VERTEX_SHADER, "/Users/wilbertchagula/Documents/CustomGameEngine/shaders/shapes/polygon/vertShader.glsl"));
    sData.push_back(std::make_pair(GL_FRAGMENT_SHADER, "/Users/wilbertchagula/Documents/CustomGameEngine/shaders/shapes/polygon/fragShader.glsl"));
    ShaderProgram * p = new ShaderProgram(sData);
	p->buildProgram();
    addShaderProg(p);

    glGenVertexArrays(1, vao);
    glBindVertexArray(vao[0]);
    glGenBuffers(2, vbo);
    
    glBindBuffer(GL_ARRAY_BUFFER, vbo[0]);
    glBufferData(GL_ARRAY_BUFFER, vertices.size() * sizeof(float), &vertices[0], GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, vbo[1]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, indices.size() * sizeof(unsigned int), &indices[0], GL_STATIC_DRAW);

}

void printMatrix(glm::mat4 mat) {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << std::endl;
    }
}

void Polygon::update(float timeSinceLastFrame) {
    time += timeSinceLastFrame;
    //glm::mat4 tempRot = glm::rotate(glm::mat4(1.0f), time * rotSpeed , glm::vec3(0, 0.1, 0));
    //glm::mat4 tempTrans = glm::translate(glm::mat4(1.0f), loc);
    mMat = glm::translate(glm::mat4(1.0f), loc);
    mMat = glm::rotate(mMat, time * rotSpeed  , glm::vec3(0, 0.1, 0));
    loc.y -= timeSinceLastFrame * rotSpeed / 2.0f;
    //mMat = tempTrans * tempRot;
    if (loc.y < -1.5) {
        loc.y = 1.5;
    }
    // printMatrix(mMat);
    // if (mMat[3][1] < -1.5) {
    //     mMat[3][1] = 1.5;
    // } else {
    //     mMat = glm::translate(mMat, timeSinceLastFrame * glm::vec3(0.0f, -1.0f, 0.0f) );
    // }
    
    //vertices[1] = vertices[1] + timeSinceLastFrame * height;
    //glBufferSubData(GL_ARRAY_BUFFER, 0, 3 * sizeof(float), &vertices[0]);
    // (*vMat) = glm::rotate(*vMat, 0.1f * timeSinceLastFrame, glm::vec3(0.3, 0.5, 0));
}

void Polygon::render() {
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
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    glEnable( GL_BLEND );
    glPolygonMode(GL_FRONT_AND_BACK,GL_LINE);
    glLineWidth(5);
    // glDrawElements(GL_TRIANGLES, indices.size(), GL_UNSIGNED_INT, 0);
    glDrawElements(GL_LINES, indices.size(), GL_UNSIGNED_INT, 0);

}

void Polygon::constructVertices() {

    float angle = glm::radians(360.0f / sides);
    glm::vec2 vert(0, 1);
    for (int i = 0; i < sides; i++) {
        glm::mat2 rotation(
            radius * cos(angle * i), radius * -sin(angle * i), 
            radius * sin(angle * i), radius * cos(angle * i)
        );
        glm::vec3 tempVert = glm::vec3(rotation * vert, 0);
        vertices.push_back(tempVert.x);
        vertices.push_back(tempVert.y);
        vertices.push_back(tempVert.z);
    }

    for (int i = 0; i < vertices.size() / 3; i++) {
       std::cout << "(" << vertices[i * 3] << ", " << vertices[i * 3 + 1] << ", " << vertices[i * 3 + 2] << ")" << std::endl;
    }

    // for (int i = 0; i < sides - 2; i++) {
    //     indices.push_back(0);
    //     indices.push_back(i + 1);
    //     indices.push_back(i + 2);
    // }

    for (int i = 0; i < sides; i++) {
        indices.push_back(i);
        indices.push_back((i + 1) % sides);
    }
}