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


WorldGeneration::WorldGeneration(int prmSize, int prmBockSize, float prmBlockScaleFactor) {

    size = prmSize;
    blockSize = prmBockSize;
    blockScaleFactor =  prmBlockScaleFactor;

    generatedNoise = generateNoise();

}

vector<shared_ptr<EngineObject>> WorldGeneration::generateWorld(App *prmApp) const {

    // Create and configure FastNoise object
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetFractalType(FastNoiseLite::FractalType_PingPong);
    noise.SetFractalPingPongStrength(1.6);


    vector<shared_ptr<EngineObject>> objects;


    for (int y = 0; y < size; ++y) {
        for (int x = 0; x < size; ++x) {

            shared_ptr<EngineObject> cube = make_shared<GameObject>(prmApp, 0, 0);
            cube->transform->scale = vec3(blockScaleFactor, blockScaleFactor, blockScaleFactor);
            cube->transform->position = vec3(x * blockSize * blockScaleFactor, trunc(noise.GetNoise((float) x, (float) y) * 2 + 50),
                                             y * blockSize * blockScaleFactor);
            objects.push_back(cube);


        }
    }

    return objects;

}

float *WorldGeneration::generateNoise() const {
// Create and configure FastNoise object
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_Perlin);

// Gather noise data
    float *noiseData = new float[size * size]{};
    int index = 0;

    for (int y = 0; y < size; y++) {
        for (int x = 0; x < size; x++) {

            noiseData[index++] = noise.GetNoise((float) x, (float) y);
        }
    }

    return noiseData;

// Do something with this data...

// Free data later

}
