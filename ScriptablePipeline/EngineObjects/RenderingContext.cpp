//
// Created by tsaury on 21/03/2022.
//

#include "RenderingContext.h"

#include "../App.h"
#include "GameObject.h"
#include "Geometry.h"
#include "../../Minecraft/Cube.h"
#include "../../Minecraft/Quad.h"
#include "../../Minecraft/ChunkGeneration.h"

RenderingContext::RenderingContext(App *app) {
    this->app = app;
}

RenderingContext::~RenderingContext() {

}

void RenderingContext::renderEntities() {
    app->setUpGlobalUniforms();

    vector<shared_ptr<RenderedObject>>::iterator iter;
    for (iter = app->getObjectsToRenderBegin(); iter != app->getObjectsToRenderEnd(); ++iter) {
        if ((*iter) != nullptr) {
            shared_ptr<Geometry> curGeometry = (*iter)->getGeometryPtr();
            if (selectedGeometry != curGeometry) {
                if (selectedGeometry != nullptr) {
                    selectedGeometry->unselect();
                }
                selectedGeometry = curGeometry;
                curGeometry->select();
            }
            (*iter)->fastRender();
        }
    }
}

void RenderingContext::renderTerrain(Terrain &terrain, TerrainRenderMode renderMode) {
    if(renderMode == SemiOpti || renderMode == Brut){
        if(terrain.size() > 0){
            terrain[0]->getCubes().front()->getGeometryPtr()->select();
        }
    }
    for(Terrain::const_iterator chunkIter = terrain.cbegin(); chunkIter != terrain.cend(); chunkIter++) {
        // need to declare pointers before switch otherwise, for loop crashes
        VectorQuadObject1D quads = (*chunkIter)->getQuads();
        VectorCubeObject1D cubesSemiOpti = (*chunkIter)->getCubesSemiOpti();
        VectorCubeObject1D cubes = (*chunkIter)->getCubes();
        switch (renderMode) {
            case Opti:
                for(VectorQuadObject1D::const_iterator quadIter = quads.cbegin(); quadIter != quads.cend(); quadIter++){
                    if((*quadIter) != nullptr){
                        (*quadIter)->getGeometryPtr()->select();
                        (*quadIter)->fastRender();
                        (*quadIter)->getGeometryPtr()->unselect();
                    }
                }
                break;
            case SemiOpti:
                for(VectorCubeObject1D::const_iterator cubeIter = cubesSemiOpti.cbegin(); cubeIter != cubesSemiOpti.cend(); cubeIter++){
                    if((*cubeIter) != nullptr){
                        (*cubeIter)->fastRender();
                    }
                }
                break;
            case Brut:
                for(VectorCubeObject1D::const_iterator cubeIter = cubes.cbegin(); cubeIter != cubes.cend(); cubeIter++){
                    if((*cubeIter) != nullptr){
                        (*cubeIter)->fastRender();
                    }
                }
                break;
        }
    }
}

