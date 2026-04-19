/*
 * Shader are the way to use GPU in OpenGL.
 * Vertex shader is "where draw"
 * Fragment shader is "wich color"
 * version core 330 == Use OpenGL 3.3
 * 
 */
#version 330 core
layout (location = 0) in vec2 aPos;

void main() {
    gl_Position = vec4(aPos, 0.0, 1.0);
    gl_PointSize = 5.0;
}
