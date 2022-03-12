//
// Created by tsaury on 11/03/2022.
//

#include "../BaseApp.h"
#include <GL/glew.h>
#pragma once


class AppCube : public BaseApp{

public:
    void main_loop() override;
    void gl_init() override;
    void clean() override;

    void loadTexture();
    GLuint cube_arrayid;
    GLuint cube_vertexbuffer;
    GLuint cube_colorbuffer;
    GLuint uv_buffer;
    GLuint tetra_arrayid;
    GLuint tetra_vertexbuffer;
    GLuint tetra_colorbuffer;

    GLuint programID;
};



