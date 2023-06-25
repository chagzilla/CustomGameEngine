#include "include/shaders/ShaderProgram.h"
#include "include/Engine.h"
#include <iostream>
#include <vector>

int main() {
    Engine game;
    std::vector<std::pair<GLenum, const char *> > sData;
    int status = game.run();
    return status;
}