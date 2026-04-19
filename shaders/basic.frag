/*
 * Shader are the way to use GPU in OpenGL.
 * Vertex shader is "where draw"
 * Fragment shader is "wich color"
 * version core 330 == Use OpenGL 3.3
 * 
 */

#version 330 core
out vec4 FragColor;

void main() {
    FragColor = vec4(1.0, 1.0, 1.0, 1.0);
}
// RGBA (Red, Green, Blue, alpha) 0-255, alpha 0.0-1.0
