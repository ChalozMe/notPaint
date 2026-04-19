#pragma once

class Renderer {
public:
    Renderer();
    void drawPoint(float x, float y);

private:
    unsigned int VAO, VBO;
};

/*
 *VBO == data (points), GPU memory
 *VAO == how reed that points, config of that poitns
*/
