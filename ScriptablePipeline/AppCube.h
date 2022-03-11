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

    GLuint vertexbuffer;
    GLuint VertexArrayID;
    GLuint programID;
};



