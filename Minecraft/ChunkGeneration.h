//
// Created by ewakeford on 18/03/2022.
//

#pragma once


#include <vector>
#include <memory>
#include <glm/vec3.hpp>
#include <glm/vec2.hpp>
#include "../ScriptablePipeline/EngineObjects/RenderingContext.h"

using namespace std;
using namespace glm;

class GameObject;
class App;
class Cube;
class Quad;

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
    VectorCubeObject1D cubesSemiOpti;
    VectorQuadObject1D quads;
    vector<pair<vec3, vec2>> quadsToRender;


    void generateWorld();
    void generateCubes();
    void generateCubesSemiOpti();
    void generateNoise();
    void combineVerticesByAxis();
    VectorIntObject1D getCubesInt();
    VectorCubeObject1D getCubes();
    VectorCubeObject1D getCubesSemiOpti();
    VectorQuadObject1D getQuads();

    void setCube(int cubeId, int x, int y, int z);

    VectorQuadObject1D sortQuadsWithSameSize(vec3 prmDirection);

    vec3 worldToChunkCoords(vec3 worldCoord);
    int getBlockIndex(int x, int y, int z);

    bool shouldFilledCubeBeDrawnSemiOpti(int x, int y, int z);
};


