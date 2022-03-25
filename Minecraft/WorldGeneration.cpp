//
// Created by ewakeford on 18/03/2022.
//

#include <vector>
#include <string>
#include "WorldGeneration.h"
#include "../helper/FastNoiseLite.h"
#include "../helper/find_exe_path.h"
#include "../ScriptablePipeline/EngineObjects/EngineObject.h"
#include "../ScriptablePipeline/EngineObjects/GameObject.h"
#include "../ScriptablePipeline/EngineObjects/Transform.h"
#include "../helper/ModelLoader.h"


WorldGeneration::WorldGeneration(int prmBockSize, float prmBlockScaleFactor) {

    blockSize = prmBockSize;
    blockScaleFactor = prmBlockScaleFactor;


}

void WorldGeneration::generateWorld(App *prmApp) {

    // Create and configure FastNoise object
//    FastNoiseLite noise;
//    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
//    noise.SetFractalType(FastNoiseLite::FractalType_PingPong);
//    noise.SetFractalPingPongStrength(1.6);

    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            for (int z = 0; z < size; ++z) {
                bool visible = true;

                // dont draw inside of cube
                if ((x != 0 && x != size - 1) && (y != 0 && y != size - 1) && (z != 0 && z != size - 1)) {
                    visible = false;
                }

                shared_ptr<GameObject> cube = make_shared<GameObject>(prmApp, 0, 0, visible);
                cube->transform->setPosition(vec3(x * blockSize * blockScaleFactor,
                                                  y * blockSize * blockScaleFactor,
                                                  z * blockSize * blockScaleFactor));


                //                cube->transform->scale = vec3(blockScaleFactor, blockScaleFactor, blockScaleFactor);
                //                cube->transform->position = vec3(x * blockSize * blockScaleFactor,
                //                                                 trunc(noise.GetNoise((float) x, (float) y) * 2 + 50),
                //                                                 y * blockSize * blockScaleFactor);
                //
                //
                //                printf("%f ", trunc(noise.GetNoise((float) x, (float) y) * 2 + 50));

                cubes.push_back(cube);
            }
        }
    }

    generateNoise();
}

void WorldGeneration::generateNoise() {
// Create and configure FastNoise object
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetFractalType(FastNoiseLite::FractalType_PingPong);
    noise.SetFractalPingPongStrength(1.6);

// Gather noise data
    int y;

    for (int z = 0; z < size; z++) {
        for (int x = 0; x < size; x++) {

            y = trunc((noise.GetNoise((float) x, (float) z)+ 1)*3);
            cubes[z * size * size + y * size + x]->visible = true;
            y++;
            for (y; y < size; y++) {
                cubes[z * size * size + y * size + x] = nullptr;
            }
        }
    }

// Do something with this data...

// Free data later

}

VectorEngineObject1D WorldGeneration::getCubes() {
    return cubes;
}

void WorldGeneration::combineVerticesByAxis() {
    //x = Left Right
    //y = Top Down
    //z = Front Back

    bool isChanged = false;
    bool isPreviousBlockEmpty = true;
    bool isNull = false;

    for (int x = 0; x < size; x++) {
        for (int z = 0; z < size ; z++) {
            for (int y = 0; y < size; ++y) {

                if (cubes[z * size * size + y * size + x] == nullptr){

                    isNull = true;
                    if (isNull == isPreviousBlockEmpty){
                        //DoNothing
                    }
                    else{
                        isPreviousBlockEmpty = true;
                        //make block draw left face
                    }

                }
                else if (cubes[z * size * size + y * size + x] != nullptr){

                    isNull=false;
                    if (isNull == isPreviousBlockEmpty){
                        //DoNothing
                    }
                    else{
                        isPreviousBlockEmpty = false;
                        //make previous block draw right face
                    }

                }

                cubes[z * size * size + 0 * size + x];
            }


        }
    }

}
