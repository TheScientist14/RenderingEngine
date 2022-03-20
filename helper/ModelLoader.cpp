//
// Created by ewakeford on 17/03/2022.
//

#include "ModelLoader.h"
#include <assimp/cimport.h>        // Plain-C interface
#include <assimp/scene.h>          // Output data structure
#include <assimp/postprocess.h>    // Post processing flags    // Post processing flags
#include "memory"
#include "../ScriptablePipeline/EngineObjects/EngineObject.h"
#include "../ScriptablePipeline/EngineObjects/GameObject.h"


const void ModelLoader::import(char *pFile) {
    // Start the import on the given file with some example postprocessing
    // Usually - if speed is not the most important aspect for you - you'll t
    // probably to request more postprocessing than we do in this example.
    aiScene = aiImportFile(pFile,
                           aiProcess_CalcTangentSpace |
                           aiProcess_Triangulate |
                           aiProcess_JoinIdenticalVertices |
                           aiProcess_SortByPType);
    // If the import failed, report it
    if (!aiScene) {
        printf("%s", aiGetErrorString());
    }

    pAiMesh = aiScene->mMeshes;

//    for(int i=0; i < numMesh;i++) {
//
//        vertexArray = (float *) pAiMesh[i]->mVertices;
//        nVertices = pAiMesh[i]->mNumVertices;
//
//
//        for (int j = 0; j < nVertices; j++) {
//            uvArray.push_back(pAiMesh[i]->mVertices[j].x);
//            uvArray.push_back(pAiMesh[i]->mVertices[j].y);
//            //printf("%f %f %f \n",pAiMesh[i]->mVertices[j].x,pAiMesh[i]->mVertices[j].y , pAiMesh[i]->mVertices[j].z);
//        }
//
//        nTriangles = pAiMesh[i]->mNumFaces;
//
//        for (int j = 0; j < nTriangles; ++j) {
//            for (int k = 0; k < pAiMesh[i]->mFaces[j].mNumIndices; ++k) {
//                vertexIndices.push_back(pAiMesh[i]->mFaces[j].mIndices[k]);
//                printf(" %d ", pAiMesh[i]->mFaces[j].mIndices[k]);
//            }
//            printf("\n");
//        }
//
//    }

    // We're done. Release all resources associated with this import
    //aiReleaseImport( scene);

}

const aiScene *ModelLoader::getAiScene() const {
    return aiScene;
}

float *ModelLoader::getVertexArray(int prmMeshIndex) const {
    return (float *) pAiMesh[prmMeshIndex]->mVertices;
}

int ModelLoader::getNVertices(int prmMeshIndex) const {
    return pAiMesh[prmMeshIndex]->mNumVertices;
}

int ModelLoader::getNumMesh() const {
    return aiScene->mNumMeshes;;
}

vector<float> ModelLoader::getUvArray(int prmMeshIndex) const {


    vector<float> uvArray;

    for (int j = 0; j < getNVertices(prmMeshIndex); j++) {
        uvArray.push_back(pAiMesh[prmMeshIndex]->mVertices[j].x);
        uvArray.push_back(pAiMesh[prmMeshIndex]->mVertices[j].y);
//        printf("%f %f %f \n", pAiMesh[prmMeshIndex]->mVertices[j].x, pAiMesh[prmMeshIndex]->mVertices[j].y,
//               pAiMesh[prmMeshIndex]->mVertices[j].z);
    }

    return uvArray;
}

int ModelLoader::getNTriangles(int prmMeshIndex) const {
    return pAiMesh[prmMeshIndex]->mNumFaces;
}

vector<unsigned int> ModelLoader::getVertexIndices(int prmMeshIndex) const {

    vector<unsigned int> vertexIndices;

    for (int j = 0; j < getNTriangles(prmMeshIndex); ++j) {
        for (int k = 0; k < pAiMesh[prmMeshIndex]->mFaces[j].mNumIndices; ++k) {
            vertexIndices.push_back(pAiMesh[prmMeshIndex]->mFaces[j].mIndices[k]);
//            printf(" %d ", pAiMesh[prmMeshIndex]->mFaces[j].mIndices[k]);
        }
//        printf("\n");
    }

    return vertexIndices;
}

float* ModelLoader::getNormalArray(int prmMeshIndex) const{

    return (float*)pAiMesh[prmMeshIndex]->mNormals;
}

int ModelLoader::loadMeshes(vector<shared_ptr<Geometry>> &prmGeometries) {

    for (int i = 0; i < getNumMesh(); ++i) {

        shared_ptr<Geometry> mesh = make_shared<Geometry>(getVertexArray(i), getNormalArray(i),
                                                          getUvArray(i).data(), getNVertices(i),
                                                          getVertexIndices(i).data(), getNTriangles(i));
        prmGeometries.push_back(mesh);

    }

    return getNumMesh();
}

ModelLoader::ModelLoader() {

}

ModelLoader::~ModelLoader() {

}


