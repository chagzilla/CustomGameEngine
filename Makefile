LDLIBS= -lglfw -lglew -framework OpenGL
SRCS= src/Engine.cpp src/shaders/Shader.cpp src/shaders/ShaderProgram.cpp src/shapes/Cube.cpp
game:
	g++ -std=c++11 main.cpp $(SRCS) $(LDLIBS) -o game
clear_screen: 
	g++ Chapter_one/clear.cpp Chapter_one/sb7.cpp $(LDLIBS) -o clear 
changing_screen:
	g++ Chapter_one/changing.cpp Chapter_one/sb7.cpp $(LDLIBS) -o changing
first_point:
	g++ utils/Shader.cpp utils/ShaderProgram.cpp Chapter_one/firstShaders.cpp Chapter_one/sb7.cpp $(LDLIBS) -o firstPoint
first_tri:
	g++ utils/Shader.cpp utils/ShaderProgram.cpp Chapter_one/firstTriangle.cpp Chapter_one/sb7.cpp $(LDLIBS) -o firstTri
offset:
	g++ Chapter_two/firstTriangle.cpp $(SRCS) $(LDLIBS) -o offset
