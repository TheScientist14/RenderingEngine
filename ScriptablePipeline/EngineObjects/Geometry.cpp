//
// Created by tsaury on 14/03/2022.
//

#include "Geometry.h"
#include <GL/glew.h>

Geometry::Geometry(const float *verticesPos, int verticesCount, const int *triangles, int trianglesCount) {
    this->verticesPos = verticesPos;
    this->verticesCount = verticesCount;
    this->triangles = triangles;
    this->trianglesCount = trianglesCount;
}

Geometry::Geometry(const float *verticesPos, const float *verticesUV, int verticesCount, const int *triangles,
                   int trianglesCount) : Geometry(verticesPos, verticesCount, triangles, trianglesCount) {
    this->verticesUV = verticesUV;
}

//Geometry::Geometry(const float *verticesPos, const float *verticesNormal, int verticesCount, const int *triangles,
//                   int trianglesCount) : Geometry(verticesPos, verticesCount, triangles, trianglesCount) {
//    this->verticesNormal = verticesNormal;
//}

Geometry::Geometry(const float *verticesPos, const float *verticesNormal, const float *verticesUV, int verticesCount,
                   const int *triangles, int trianglesCount) :
                   Geometry(verticesPos, verticesCount, triangles, trianglesCount) {
    this->verticesNormal = verticesNormal;
    this->verticesUV = verticesUV;
}

Geometry::~Geometry() {

}

void Geometry::bind() {

    // This will identify our vertex buffer
    glGenVertexArrays(1, &verticesID);
    glBindVertexArray(verticesID);

    // Generate 3 buffer, put the resulting identifiers in buffersID
    glGenBuffers(3, buffersID);

    // The following commands will talk about our 'buffersID' buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffersID[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * verticesCount, verticesPos, GL_STATIC_DRAW);
    //normal
    glBindBuffer(GL_ARRAY_BUFFER, buffersID[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * verticesCount, verticesNormal, GL_STATIC_DRAW);
    //uv
    glBindBuffer(GL_ARRAY_BUFFER, buffersID[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * verticesCount, verticesUV, GL_STATIC_DRAW);
}

void Geometry::draw(GLuint shaderID) const {
    glBindBuffer(GL_ARRAY_BUFFER, buffersID[0]);
    glVertexAttribPointer(
            0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
            3,                  // size
            GL_FLOAT,           // type
            GL_FALSE,           // normalized?
            0,                  // stride
            (void*)0            // array buffer offset
    );
    glBindBuffer(GL_ARRAY_BUFFER, buffersID[1]);
    glVertexAttribPointer(
            1,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            3,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
    );

    glBindBuffer(GL_ARRAY_BUFFER, buffersID[2]);
    glVertexAttribPointer(
            2,                                // attribute. No particular reason for 1, but must match the layout in the shader.
            2,                                // size
            GL_FLOAT,                         // type
            GL_FALSE,                         // normalized?
            0,                                // stride
            (void*)0                          // array buffer offset
    );
    glDrawArrays(GL_TRIANGLES, 0, trianglesCount*3);
}
