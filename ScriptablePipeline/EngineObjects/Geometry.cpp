//
// Created by tsaury on 14/03/2022.
//

#include "Geometry.h"
const Geometry* Geometry::selectedGeometry = nullptr;
// TODO : variable size of vertex attributes

Geometry::Geometry(const float *verticesPos, int verticesCount, const unsigned int *triangles, int trianglesCount) {
    for(int i = 0; i < verticesCount * 3; i++){
        this->verticesPos.push_back(verticesPos[i]);
    }
    this->verticesCount = verticesCount;
    for(int i = 0; i < trianglesCount * 3; i++){
        this->triangles.push_back(triangles[i]);
    }
    this->trianglesCount = trianglesCount;
}

Geometry::Geometry(const float *verticesPos, const float *verticesUV, int verticesCount, const unsigned int *triangles,
                   int trianglesCount) : Geometry(verticesPos, verticesCount, triangles, trianglesCount) {
    for(int i = 0; i < verticesCount * 2; i++){
        this->verticesUV.push_back(verticesUV[i]);
    }
}

//Geometry::Geometry(const float *verticesPos, const float *verticesNormal, int verticesCount, const unsigned int *triangles,
//                   int trianglesCount) : Geometry(verticesPos, verticesCount, triangles, trianglesCount) {
//    for(int i = 0; i < verticesCount * 3; i++){
//        this->verticesNormal.push_back(verticesNormal[i]);
//    }
//}

Geometry::Geometry(const float *verticesPos, const float *verticesNormal, const float *verticesUV, int verticesCount,
                   const unsigned int *triangles, int trianglesCount) :
                   Geometry(verticesPos, verticesUV, verticesCount, triangles, trianglesCount) {
    for(int i = 0; i < verticesCount * 3; i++){
        this->verticesNormal.push_back(verticesNormal[i]);
    }
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
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * verticesCount, verticesPos.data(), GL_STATIC_DRAW);
    //normal
    glBindBuffer(GL_ARRAY_BUFFER, buffersID[1]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 3 * verticesCount, verticesNormal.data(), GL_STATIC_DRAW);
    //uv
    glBindBuffer(GL_ARRAY_BUFFER, buffersID[2]);
    glBufferData(GL_ARRAY_BUFFER, sizeof(float) * 2 * verticesCount, verticesUV.data(), GL_STATIC_DRAW);
    //vertices index
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffersID[3]);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(unsigned int) * 3 * trianglesCount, triangles.data(), GL_STATIC_DRAW);
}

void Geometry::draw() const {
    if(selectedGeometry != this){
        if(selectedGeometry != nullptr){
            selectedGeometry->unselect();
        }
        select();
    }
    drawFast();
}

/**
 * the geometry must be selected before being drawn fast
 */
void Geometry::drawFast() const{
    if(triangles.empty()){
        glDrawArrays(GL_TRIANGLES, 0, verticesCount);
    }
    else{
        // Index buffer
        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, buffersID[3]);
        glDrawElements(GL_TRIANGLES, trianglesCount * 3, GL_UNSIGNED_INT, 0);
    }
}

void Geometry::select() const{
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
    selectedGeometry = this;
}

void Geometry::unselect() const{
    glDisableVertexAttribArray(0);
    glDisableVertexAttribArray(1);
    glDisableVertexAttribArray(2);
    selectedGeometry = nullptr;
}

// calculate mvp then render
// optimize rotations
// caching mvp
// rendering context