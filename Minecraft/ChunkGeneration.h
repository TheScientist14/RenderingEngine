//
// Created by ewakeford on 18/03/2022.
//

#pragma once


#include <vector>
#include <memory>
#include "Cube.h"
#include "Quad.h"

using namespace std;

class GameObject;
class App;
class Cube;

typedef vector<int> VectorIntObject1D;
typedef vector<shared_ptr<Cube>> VectorCubeObject1D;
typedef vector<shared_ptr<Quad>> VectorQuadObject1D;

class ChunkGeneration : public enable_shared_from_this<ChunkGeneration>{

public:

    ChunkGeneration(App *prmApp, int prmBockSize, float prmBlockScaleFactor, int x, int z);

    const static int size = 16;
    App *app;
    vec3 chunkCoord;
    int blockSize;
    float blockScaleFactor;
    VectorIntObject1D cubesInt;
    VectorCubeObject1D cubes;
    VectorQuadObject1D quads;
    vector<pair<vec3, vec2>> quadsToRender;

    void generateWorld(App* prmApp);
    void generateNoise();
    void combineVerticesByAxis();
    VectorIntObject1D getCubesInt();
    VectorCubeObject1D getCubes();
    VectorQuadObject1D getQuads();

    VectorQuadObject1D sortQuadsWithSameSize(vec3 prmDirection);

    static vec3 worldToChunkCoords(vec3 worldCoord, vec3 chunkCoord, float blockSize);

};


