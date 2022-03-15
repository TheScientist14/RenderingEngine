//
// Created by tsaury on 14/03/2022.
//

#pragma once

#include <GL/glew.h>
#include <memory>
#include <vector>

using namespace std;

class Geometry : public enable_shared_from_this<Geometry> {

protected:
    const float* verticesPos;
    const float* verticesNormal;
    const float* verticesUV;
    int verticesCount;
    const int* triangles;
    int trianglesCount;

    GLuint verticesID;
    vector<GLuint> buffersID;

public:
    Geometry(const float* verticesPos, int verticesCount, const int* triangles, int trianglesCount);
    Geometry(const float* verticesPos, const float* verticesUV, int verticesCount, const int* triangles, int trianglesCount);
    //Geometry(const float* verticesPos, const float* verticesNormal, int verticesCount, const int* triangles, int trianglesCount);
    Geometry(const float* verticesPos, const float* verticesNormal, const float* verticesUV, int verticesCount, const int* triangles, int trianglesCount);
    virtual ~Geometry();

    void bind();
    void draw(GLuint shaderID) const;
};


