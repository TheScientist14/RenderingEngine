//
// Created by ewakeford on 17/03/2022.
//

#pragma once

#include <vector>
#include <memory>
#include "../../ScriptablePipeline/EngineObjects/Geometry.h"

using namespace std;

struct aiScene;

class ModelLoader {

public:

    char* pFile;
    const aiScene* scene;
    class aiMesh** pAiMesh;

    ModelLoader();
    virtual ~ModelLoader();

    int loadMeshes(vector<shared_ptr<Geometry>> &prmGeometries);


    const void import(char* pFile);

    const aiScene *getAiScene() const;

    float *getVertexArray(int prmMeshIndex) const;

    int getNVertices(int prmMeshIndex) const;

    int getNumMesh() const;

    vector<float> getUvArray(int prmMeshIndex) const;

    int getNTriangles(int prmMeshIndex) const;

    float* getNormalArray(int prmMeshIndex) const;

    vector<unsigned int> getVertexIndices(int prmMeshIndex) const;



};