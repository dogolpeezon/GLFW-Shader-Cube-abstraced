# GLFW-Shader-Cube-abstraced
OpenGL glfw with shaders to draw a cube.. abstracted OOP

This is my attempt to abstract glfw samples into a more object oriented way. as most of the samples i have seen are all written in a single file.

Next i will attempt to refine this.. starting with indexing the vertices with Element_Array _Buffer and glDrawElementsInstanced();

Build:

g++ -Wall -g -o Cube shader.cpp manager.cpp main.cpp -lGLEW -lglfw3 -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl


