//
// Created by tsaury on 14/03/2022.
//

#pragma once

#include <memory>
#include <string>
#include "GL/glew.h"

using namespace std;

class Texture : enable_shared_from_this<Texture> {

protected:
    unsigned char* texels;
    int width;
    int height;
    int channels;


public:

    Texture();
    Texture(const char* filepath);
    virtual ~Texture();

    void bind();
    void select(GLuint shaderID) const;
};

