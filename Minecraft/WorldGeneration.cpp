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

    generatedNoise = generateNoise();

}

void WorldGeneration::generateWorld(App *prmApp) {

    // Create and configure FastNoise object
    FastNoiseLite noise;
    noise.SetNoiseType(FastNoiseLite::NoiseType_OpenSimplex2);
    noise.SetFractalType(FastNoiseLite::FractalType_PingPong);
    noise.SetFractalPingPongStrength(1.6);

    for (int x = 0; x < size; ++x) {
        for (int y = 0; y < size; ++y) {
            for (int z = 0; z < size; ++z) {
                bool visible = true;

                // dont draw inside of cube
                if((x != 0 && x != size-1) && (y != 0 && y != size-1) && (z != 0 && z != size-1)) {
                    visible = false;
                }

                shared_ptr<EngineObject> cube = make_shared<GameObject>(prmApp, 0, 0, visible);
                cube->transform->position = vec3(x * blockSize * blockScaleFactor,
                                y * blockSize * blockScaleFactor,
                                z * blockSize * blockScaleFactor);


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
    }

    float *WorldGeneration::generateNoise() {
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

VectorEngineObject1D WorldGeneration::getCubes() {
    return cubes;
}
