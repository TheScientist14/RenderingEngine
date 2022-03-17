//
// Created by ewakeford on 17/03/2022.
//

#include "ModelLoader.h"
#include <assimp/cimport.h>        // Plain-C interface
#include <assimp/scene.h>          // Output data structure
#include <assimp/postprocess.h>    // Post processing flags    // Post processing flags


const aiScene* ModelLoader::import(char* pFile)
{
    // Start the import on the given file with some example postprocessing
    // Usually - if speed is not the most important aspect for you - you'll t
    // probably to request more postprocessing than we do in this example.
    scene = aiImportFile( pFile,
                                         aiProcess_CalcTangentSpace       |
                                         aiProcess_Triangulate            |
                                         aiProcess_JoinIdenticalVertices  |
                                         aiProcess_SortByPType);
    // If the import failed, report it
    if( !scene)
    {
        printf( "%s", aiGetErrorString());
        return false;
    }

    // We're done. Release all resources associated with this import
    //aiReleaseImport( scene);
    return scene;
}
