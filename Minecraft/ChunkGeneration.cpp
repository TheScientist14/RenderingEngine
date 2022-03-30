//
// Created by ewakeford on 18/03/2022.
//

#include <vector>
#include <set>
#include <string>
#include "ChunkGeneration.h"
#include "../helper/FastNoiseLite.h"
#include "../helper/find_exe_path.h"
#include "../ScriptablePipeline/EngineObjects/EngineObject.h"
#include "../ScriptablePipeline/EngineObjects/GameObject.h"
#include "../ScriptablePipeline/EngineObjects/Transform.h"
#include "../helper/ModelLoader.h"
#include "Quad.h"
#include "Cube.h"


ChunkGeneration::ChunkGeneration(App *prmApp, int prmBockSize, float prmBlockScaleFactor, int x, int z) {

    this->app = prmApp;
    blockSize = prmBockSize;
    blockScaleFactor = prmBlockScaleFactor;
    chunkCoord = vec3(x*size,0,z*size);
}

void ChunkGeneration::generateWorld(App *prmApp) {

    for (int x = chunkCoord.x; x < size + chunkCoord.x; ++x) {
        for (int y = chunkCoord.y; y < size + chunkCoord.y; ++y) {
            for (int z = chunkCoord.z; z < size + chunkCoord.z; ++z) {
                bool visible = true;

                // dont draw inside of cube
                if ((x != chunkCoord.x && x != size + chunkCoord.x - 1) && (y != chunkCoord.y && y != size + chunkCoord.y - 1) && (z != chunkCoord.z && z != size+ chunkCoord.z  - 1)) {
                    visible = false;
                }

                shared_ptr<Cube> cube = make_shared<Cube>(prmApp, 0, 0, visible, blockScaleFactor);
                cube->transform->setPosition(vec3(x * blockSize * blockScaleFactor,
                                                  y * blockSize * blockScaleFactor,
                                                  z * blockSize * blockScaleFactor));

                cubes.push_back(cube);

                cubesInt.push_back(1);
            }
        }
    }
    generateNoise();
    combineVerticesByAxis();
}

void ChunkGeneration::generateNoise() {
// Create and configure FastNoise object
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetFractalType(FastNoiseLite::FractalType_PingPong);
    noise.SetFractalPingPongStrength(1.6);

// Gather noise data
    int y;

    for (int z = 0; z < size; z++) {
        for (int x = 0; x < size; x++) {
            y = trunc((noise.GetNoise((float) x + chunkCoord.x, (float) z + chunkCoord.z) + 1) * 3);
            cubes[z * size * size + y * size + x]->visible = true;
            y++;
            for (y; y < size; y++) {
                cubes[z * size * size + y * size + x]->visible = false;
                cubesInt[z * size * size + y * size + x] = 0;
            }
        }
    }

// Do something with this data...

// Free data later

}


void ChunkGeneration::combineVerticesByAxis() {
    //x = Top Down
    //y = Left Right
    //z = Front Back

    bool isChanged = false;
    bool beginQuad = false;
    bool previousState = false;
    bool nowState = false;

    shared_ptr<Quad> quad = nullptr;
    vec3 firstcoord;
    int height = 1;
    int meshWidth = 1;



    //Z Walls
    for (int y = 0; y < size; y++) {
        for (int z = 0; z < size+1; z++) {
            previousState = false;
            for (int x = 0; x < size; x++) {

                if (z < size && z > 0) {
                    if (cubesInt[z * size * size + y * size + x] == cubesInt[(z - 1) * size * size + y * size + x]) {
                        nowState = false;
                    } else {
                        nowState = true;
                    }
                } else {
                    if(z == 0){
                        nowState = (cubesInt[z * size * size + y * size + x] == 1);
                    }else{
                        nowState = (cubesInt[(z-1) * size * size + y * size + x] == 1);
                    }
                }

                if (nowState == previousState) {
                    if (nowState) {
                        if (meshWidth <= size) {
                            meshWidth++;
                        }
                    }

                } else {
                    if (nowState) {
                        //firstcoord = cubesInt[z * size * size + y * size + x]->getLeftTopBack();
                        firstcoord = vec3((chunkCoord.x + x) -blockSize/2.0f, y+blockSize/2.0f, (chunkCoord.z + z)-blockSize/2.0f);
                        meshWidth = 1;
                    }
                    else{

                         pair<vec3, vec2> quad = make_pair(firstcoord, vec2(meshWidth, height));
                         quadsToRender.push_back(quad);

//                        quad = make_shared<Quad>(app, 1, meshWidth, vec3(0, 0, 1));
//                        quad->transform->setPosition(firstcoord);
//                        quads.push_back(quad);
                    }
                    previousState = nowState;

                }


/*                if (cubesInt[z * size * size + y * size + x] == nullptr){


                    isNull = true;
                    if(beginQuad) {
                        quad = make_shared<Quad>(app, 1, width, vec3(1, 0, 0));
                        quad->transform->setPosition(firstcoord);
                        width = 0;
                        quad->createTrianglesX();
                        quads.push_back(quad);
                        beginQuad = false;
                    }
                    isPreviousBlockEmpty = true;


                }
                else if (cubesInt[z * size * size + y * size + x] != nullptr){

                    isNull=false;
                    width++;
                    if (isPreviousBlockEmpty){
                        firstcoord = cubesInt[z * size * size + y * size + x]->getLeftTopBack();
                        beginQuad = true;
                        isPreviousBlockEmpty = false;
                    }
                }*/

            }
            if(previousState){
                pair<vec3, vec2> quad = make_pair(firstcoord, vec2(meshWidth, height));
                quadsToRender.push_back(quad);

//                quad = make_shared<Quad>(app, 1, meshWidth, vec3(0, 0, 1));
//                quad->transform->setPosition(firstcoord);
//                quads.push_back(quad);
            }
        }
    }

    VectorQuadObject1D mergedQuadsZ = sortQuadsWithSameSize(vec3(0,0,1));

    quads.insert(quads.end(), mergedQuadsZ.begin(), mergedQuadsZ.end());
    quadsToRender.clear();


    //X Walls
    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size+1; x++) {
            previousState = false;
            for (int z = 0; z < size; z++) {

                if (x < size && x > 0) {
                    if (cubesInt[z * size * size + y * size + x] == cubesInt[z * size * size + y * size + (x-1)]) {
                        nowState = false;
                    } else {
                        nowState = true;
                    }
                } else {
                    if(x == 0){
                        nowState = (cubesInt[z * size * size + y * size + x] == 1);
                    }else{
                        nowState = (cubesInt[z * size * size + y * size + (x-1)] == 1);
                    }
                }

                if (nowState == previousState) {
                    if (nowState) {
                        if (meshWidth <= size) {
                            meshWidth++;
                        }
                    }

                } else {
                    if (nowState) {
                        //firstcoord = cubesInt[z * size * size + y * size + x]->getLeftTopBack();
                        firstcoord = vec3((chunkCoord.x + x) -blockSize/2.0f, y+blockSize/2.0f, (chunkCoord.z + z)-blockSize/2.0f);
                        meshWidth = 1;
                    } else {

                        pair<vec3, vec2> quadPairX = make_pair(firstcoord, vec2(meshWidth, height));
                        quadsToRender.push_back(quadPairX);

                        /*quad = make_shared<Quad>(app, 1, meshWidth, vec3(1, 0, 0));
                        quad->transform->setPosition(firstcoord);
                        quads.push_back(quad);*/
                    }
                    previousState = nowState;

                }
            }
            if (previousState) {

                pair<vec3, vec2> quadPairX = make_pair(firstcoord, vec2(meshWidth, height));
                quadsToRender.push_back(quadPairX);

                /*quad = make_shared<Quad>(app, 1, meshWidth, vec3(1, 0, 0));
                quad->transform->setPosition(firstcoord);
                quads.push_back(quad);*/
            }
        }
    }

    VectorQuadObject1D mergedQuadsX = sortQuadsWithSameSize(vec3(1,0,0));

    quads.insert(quads.end(), mergedQuadsX.begin(), mergedQuadsX.end());
    quadsToRender.clear();

    //Y Walls
    for (int x = 0; x < size; x++) {
        for (int y = -1; y < size; y++) {
            previousState = false;
            for (int z = 0; z < size; z++) {

                if (y < size-1 && y >= 0) {
                    if (cubesInt[z * size * size + y * size + x] == cubesInt[z * size * size + (y+1) * size + x]) {
                        nowState = false;
                    } else {
                        nowState = true;
                    }
                } else {
                    if(y < 0){
                        nowState = (cubesInt[z * size * size + (y+1) * size + x] == 1);
                    }else{
                        nowState = (cubesInt[z * size * size + y * size + x] == 1);
                    }
                }

                if (nowState == previousState) {
                    if (nowState) {
                        if (meshWidth <= size) {
                            meshWidth++;
                        }
                    }

                } else {
                    if (nowState) {
                        //firstcoord = cubesInt[z * size * size + y * size + x]->getLeftTopBack();
                        firstcoord = vec3((chunkCoord.x + x) -blockSize/2.0f, y+blockSize/2.0f, (chunkCoord.z + z)-blockSize/2.0f);

                        meshWidth = 1;
                    } else {

                        pair<vec3, vec2> quadPairY = make_pair(firstcoord, vec2(meshWidth, height));
                        quadsToRender.push_back(quadPairY);

//                        quad = make_shared<Quad>(app, 1, meshWidth, vec3(0, 1, 0));
//                        quad->transform->setPosition(firstcoord);
//                        quads.push_back(quad);
                    }
                    previousState = nowState;

                }
            }
            if (previousState) {

                pair<vec3, vec2> quadPairY = make_pair(firstcoord, vec2(meshWidth, height));
                quadsToRender.push_back(quadPairY);



//                quad = make_shared<Quad>(app, 1, meshWidth, vec3(0, 1, 0));
//                quad->transform->setPosition(firstcoord);
//                quads.push_back(quad);
            }
        }
    }
    VectorQuadObject1D mergedQuadsY = sortQuadsWithSameSize(vec3(0,1,0));

    quads.insert(quads.end(), mergedQuadsY.begin(), mergedQuadsY.end());

/*//    beginQuad = false;
//    isPreviousBlockEmpty = true;
//    //all z
//    for (int y = 0; y < size; ++y) {
//        for (int x = 0; x < size ; x++) {
//            for (int z = 0; z < size; z++) {
//
//                if (cubesInt[z * size * size + y * size + x] == nullptr){
//
//                    isNull = true;
//                    if(beginQuad) {
//                        quad = make_shared<Quad>(app, 1, width, vec3(0, 0, 1));
//                        quad->transform->setPosition(firstcoord);
//                        width = 0;
//                        quad->createTrianglesX();
//                        quads.push_back(quad);
//                        beginQuad = false;
//                    }
//                    isPreviousBlockEmpty = true;
//
//
//                }
//                else if (cubesInt[z * size * size + y * size + x] != nullptr){
//
//                    isNull=false;
//                    width++;
//                    if (isPreviousBlockEmpty){
//                        firstcoord = cubesInt[z * size * size + y * size + x]->getLeftTopBack();
//                        beginQuad = true;
//                        isPreviousBlockEmpty = false;
//                    }
//
//                }
//
//            }
//            if(beginQuad) {
//                quad = make_shared<Quad>(app, 1, width, vec3(0, 0, 1));
//                quad->transform->setPosition(firstcoord);
//                width = 0;
//                quad->createTrianglesX();
//                quads.push_back(quad);
//                beginQuad = false;
//            }
//        }
//        if(beginQuad) {
//            quad = make_shared<Quad>(app, 1, width, vec3(0, 0, 1));
//            quad->transform->setPosition(firstcoord);
//            width = 0;
//            quad->createTrianglesX();
//            quads.push_back(quad);
//            beginQuad = false;
//        }
//    }
//    beginQuad = false;
//    isPreviousBlockEmpty = true;
//    //all y
//    for (int z = 0; z < size; ++z) {
//        for (int x = 0; x < size ; x++) {
//            for (int y = 0; y < size; y++) {
//
//                if (cubesInt[z * size * size + y * size + x] == nullptr){
//
//                    isNull = true;
//                    if(beginQuad) {
//                        quad = make_shared<Quad>(app, 1, width, vec3(0, 1, 0));
//                        quad->transform->setPosition(firstcoord);
//                        width = 0;
//                        quad->createTrianglesX();
//                        quads.push_back(quad);
//                        beginQuad = false;
//                    }
//                    isPreviousBlockEmpty = true;
//
//
//                }
//                else if (cubesInt[z * size * size + y * size + x] != nullptr){
//
//                    isNull=false;
//                    width++;
//                    if (isPreviousBlockEmpty){
//                        firstcoord = cubesInt[z * size * size + y * size + x]->getLeftTopBack();
//                        beginQuad = true;
//                        isPreviousBlockEmpty = false;
//                    }
//
//                }
//
//            }
//        }
//    }*/
}


VectorQuadObject1D ChunkGeneration::sortQuadsWithSameSize(vec3 prmDirection) {

    VectorQuadObject1D quadsMerged;
    int x = prmDirection.x;
    int y = prmDirection.y;

//    vector<pair<vec3, vec2>> drawnQuads;

    for (int i = 0; i < quadsToRender.size(); ++i) {
        pair<vec3, vec2> quadToMerge = quadsToRender[i];
//
//        bool hasBeenDrawn = false;
//        for (int i = 0; i < drawnQuads.size(); i++) {
//            if (drawnQuads[i] == quadToMerge) {
//                hasBeenDrawn = true;
//            }
//        }

//        if (!hasBeenDrawn) {
        bool doNext;
        do {
            doNext = false;


            vec3 coord;

            if (x != 0) {
                coord = vec3(quadToMerge.first.x , quadToMerge.first.y + quadToMerge.second.y, quadToMerge.first.z);
            } else if (y != 0) {
                coord = vec3(quadToMerge.first.x + quadToMerge.second.y, quadToMerge.first.y, quadToMerge.first.z);
            } else {
                coord = vec3(quadToMerge.first.x , quadToMerge.first.y + quadToMerge.second.y, quadToMerge.first.z);
            }


//            drawnQuads.push_back(quadToMerge);

            for (int j = 0; j < quadsToRender.size(); ++j) {

                if (quadsToRender[j].first == coord) {

                        if (quadsToRender[j].second.x == quadToMerge.second.x) {
                            quadToMerge.second.y++;

                            quadsToRender.erase(quadsToRender.cbegin() + j); // doesn't work ?
                            doNext = true;
//                        drawnQuads.push_back(quadsToRender[j]);
                            break;

                        }


                }

            }

        }while(doNext);

            shared_ptr<Quad> quad = make_shared<Quad>(app, quadToMerge.second.y, quadToMerge.second.x, prmDirection);
            if (x != 0) {
                //quad->transform->setPosition(quadToMerge.first);
                quad->transform->setPosition(vec3(quadToMerge.first.x,quadToMerge.first.y + quadToMerge.second.y -1 ,quadToMerge.first.z));
            } else if (y != 0) {
                quad->transform->setPosition(quadToMerge.first);
            } else {
                quad->transform->setPosition(vec3(quadToMerge.first.x,quadToMerge.first.y + quadToMerge.second.y -1 ,quadToMerge.first.z));
            }
            //quad->transform->setPosition(quadToMerge.first);

            quadsMerged.push_back(quad);

//        }

    }

    return quadsMerged;
}


VectorQuadObject1D ChunkGeneration::getQuads() {

    return quads;
}

vec3 ChunkGeneration::worldToChunkCoords(vec3 worldCoord, vec3 chunkCoord, float blockSize) {
    vec3 chunkCoords = vec3(worldCoord.x / blockSize - 0.5f - (chunkCoord.x - 0.5f) * size,
                            worldCoord.y / blockSize - 0.5f - chunkCoord.y,
                            worldCoord.z);
    if (worldCoord.x >= 0 && worldCoord.x < size
            && worldCoord.y >= 0 && worldCoord.y < size
            && worldCoord.z >= 0 && worldCoord.z < size) {
        return chunkCoords;
    } else {
        return vec3(-1);
    }
}

VectorCubeObject1D ChunkGeneration::getCubes() {
    return cubes;
}

VectorIntObject1D ChunkGeneration::getCubesInt() {
    return cubesInt;
}
