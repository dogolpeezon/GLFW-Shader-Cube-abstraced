# GLFW-Shader-Cube-abstraced
OpenGL glfw with shaders to draw a cube.. abstracted OOP

This is my attempt to abstract glfw samples into a more object oriented way. as most of the samples i have seen are all written in a single file.

Next i will attempt to refine this.. starting with indexing the vertices with Element_Array _Buffer and glDrawElementsInstanced();

Build:

g++ -Wall -g -o Cube shader.cpp manager.cpp main.cpp -lGLEW -lglfw3 -lGL -lX11 -lXi -lXrandr -lXxf86vm -lXinerama -lXcursor -lrt -lm -pthread -ldl

##![cube](https://user-images.githubusercontent.com/26413252/36912676-5ebc2776-1e3f-11e8-8049-6e75edc8af39.gif)


![screenshot at 2018-02-21 12-38-34](https://user-images.githubusercontent.com/26413252/36635749-9b954f42-19b2-11e8-9957-5884c8a8167e.png)

I have created these diagrams to demonstrate how the vertices layout for the cube..

![cube-plan](https://user-images.githubusercontent.com/26413252/36899519-5ff4b220-1e17-11e8-8b5e-27c5ce04c30a.png)

![cube-iso](https://user-images.githubusercontent.com/26413252/36899388-c98ec514-1e16-11e8-8172-2d8b0d0e8da4.png)
