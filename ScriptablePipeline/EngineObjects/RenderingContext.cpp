//
// Created by tsaury on 21/03/2022.
//

#include "RenderingContext.h"

#include "../App.h"
#include "EngineObject.h"
#include "GameObject.h"
#include "Geometry.h"
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
    for(Terrain::const_iterator chunkIter = terrain.cbegin(); chunkIter != terrain.cend(); chunkIter++){
        switch (renderMode) {
            case Opti:
                for(VectorQuadObject1D::const_iterator quadIter = (*chunkIter)->getQuads().cbegin(); quadIter != (*chunkIter)->getQuads().cend(); quadIter++){
                    (*quadIter)->getGeometryPtr()->select();
                    (*quadIter)->fastRender();
                    (*quadIter)->getGeometryPtr()->unselect();
                }
                break;
            case SemiOpti:
                for(VectorCubeObject1D::const_iterator cubeIter = (*chunkIter)->getCubesSemiOpti().cbegin(); cubeIter != (*chunkIter)->getCubesSemiOpti().cend(); cubeIter++){
                    (*cubeIter)->fastRender();
                }
                break;
            case Brut:
                for(VectorCubeObject1D::const_iterator cubeIter = (*chunkIter)->getCubes().cbegin(); cubeIter != (*chunkIter)->getCubes().cend(); cubeIter++){
                    (*cubeIter)->fastRender();
                }
                break;
        }
    }
    if(renderMode == SemiOpti || renderMode == Brut){
        if(terrain.size() > 0){
            terrain[0]->getCubes().front()->getGeometryPtr()->unselect();
        }
    }
}