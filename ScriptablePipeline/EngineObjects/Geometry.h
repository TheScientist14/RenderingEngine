//
// Created by tsaury on 14/03/2022.
//

#pragma once

#include <memory>
#include <vector>

#include <GL/glew.h>
#include <glm/vec3.hpp>

using namespace std;
using namespace glm;

class Geometry : public enable_shared_from_this<Geometry> {

protected:
    vector<float> verticesPos;
    vector<vec3> verticesPosVec3;
    vector<float> verticesNormal;
    vector<float> verticesUV;
    int verticesCount;
    vector<unsigned int> triangles;
    vector<vec3> trianglesVec3;
    int trianglesCount;

    GLuint verticesID;
    vector<GLuint> buffersID;

    //const static Geometry* selectedGeometry;

public:
    Geometry(const float* verticesPos, int verticesCount, const unsigned int* triangles, int trianglesCount);
    Geometry(const float* verticesPos, const float* verticesUV, int verticesCount, const unsigned int* triangles, int trianglesCount);
    Geometry(vector<float> verticesPos, int verticesCount, vector<unsigned int> triangles, int trianglesCount);
    Geometry(vector<float> verticesPos, vector<float>verticesUV, int verticesCount, vector<unsigned int> triangles,
                       int trianglesCount);
    Geometry(vector<float> verticesPos, vector<float> verticesNormal, vector<float> verticesUV, int verticesCount, vector<unsigned int> triangles, int trianglesCount);
    Geometry(const float* verticesPos, const float* verticesNormal, const float* verticesUV, int verticesCount, const unsigned int* triangles, int trianglesCount);
    Geometry();
    virtual ~Geometry();

    void bind();
    void bindWithVec3();
    void draw() const;
    void drawFast() const;
    void select() const;
    void unselect() const;
};


