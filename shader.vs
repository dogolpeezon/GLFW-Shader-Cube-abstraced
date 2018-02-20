#version 330 core

layout(location = 0) in vec3 vertexPosition;
layout(location = 1) in vec3 vertexColor;
layout(location = 2) in vec3 vertexNormal;

//uniform mat4 MVP;
uniform mat4 model, view, projection;

out vec3 fragmentColor;

void main(){

	gl_Position =  projection * view * model * vec4(vertexPosition, 1.0f);
	fragmentColor = vertexColor;
}
