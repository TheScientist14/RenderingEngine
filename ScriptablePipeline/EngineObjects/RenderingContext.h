//
// Created by tsaury on 21/03/2022.
//

#pragma once

#include <memory>
#include <vector>
#include <map>

using namespace std;

class Geometry;
class GameObject;
class ModelShaderData;
class App;
class ChunkGeneration;

typedef vector<shared_ptr<ChunkGeneration>> Terrain;

class RenderingContext {

protected:
    App* app;

    shared_ptr<Geometry> selectedGeometry = nullptr;

public:
    RenderingContext(App* app);
    virtual ~RenderingContext();

    void renderEntities();


    enum TerrainRenderMode {
        Opti, SemiOpti, Brut
    };

    void renderTerrain(Terrain &terrain, TerrainRenderMode renderMode);
};
