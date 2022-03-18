//
// Created by ewakeford on 17/03/2022.
//

#pragma once

#include <vector>
#include <memory>
#include "../../ScriptablePipeline/EngineObjects/Geometry.h"

using namespace std;

class ModelLoader {

public:

    char* pFile;
    const class aiScene* aiScene;
    class aiMesh** pAiMesh;


    int loadMeshes(vector<shared_ptr<Geometry>> &prmGeometries);


    const void import(char* pFile);

    const struct aiScene *getAiScene() const;

    float *getVertexArray(int prmMeshIndex) const;

    int getNVertices(int prmMeshIndex) const;

    int getNumMesh() const;

    vector<float> getUvArray(int prmMeshIndex) const;

    int getNTriangles(int prmMeshIndex) const;

    float* getNormalArray(int prmMeshIndex) const;

    vector<unsigned int> getVertexIndices(int prmMeshIndex) const;



};