//
// Created by tsaury on 14/03/2022.
//

#include "Geometry.h"
#include <GL/glew.h>

// TODO : variable size of vertex attributes

Geometry::Geometry(const float *verticesPos, int verticesCount, const unsigned int *triangles, int trianglesCount) {
    this->verticesPos = verticesPos;
    this->verticesCount = verticesCount;
    this->triangles = triangles;
    this->trianglesCount = trianglesCount;
}

Geometry::Geometry(const float *verticesPos, const float *verticesUV, int verticesCount, const unsigned int *triangles,
                   int trianglesCount) : Geometry(verticesPos, verticesCount, triangles, trianglesCount) {
    this->verticesUV = verticesUV;
}

//Geometry::Geometry(const float *verticesPos, const float *verticesNormal, int verticesCount, const unsigned int *triangles,
//                   int trianglesCount) : Geometry(verticesPos, verticesCount, triangles, trianglesCount) {
//    this->verticesNormal = verticesNormal;
//}

Geometry::Geometry(const float *verticesPos, const float *verticesNormal, const float *verticesUV, int verticesCount,
                   const unsigned int *triangles, int trianglesCount) :
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

    // Generate 3 buffers, put the resulting identifiers in buffersID
    buffersID.resize(4);
    glGenBuffers(4, buffersID.data());

    // The following commands will talk about our 'buffersID' buffer
    glBindBuffer(GL_ARRAY_BUFFER, buffersID[0]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * verticesCount, verticesPos, GL_STATIC_DRAW);
    //normal
    glBindBuffer(GL_ARRAY_BUFFER, buffersID[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * verticesCount, verticesNormal, GL_STATIC_DRAW);
    //uv
    glBindBuffer(GL_ARRAY_BUFFER, buffersID[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * verticesCount, verticesUV, GL_STATIC_DRAW);
    //vertices index
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffersID[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, trianglesCount * sizeof(unsigned int) * 3, triangles, GL_STATIC_DRAW);
}

void Geometry::draw(GLuint shaderID) const {
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glEnableVertexAttribArray(2);
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

    if(triangles){
        // Index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffersID[3]);
        glDrawElements(GL_TRIANGLES, trianglesCount * 3, GL_UNSIGNED_INT, 0);
    }
    else{
        glDrawArrays(GL_TRIANGLES, 0, verticesCount);
    }
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
}
