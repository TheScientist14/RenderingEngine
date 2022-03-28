//
// Created by tsaury on 21/03/2022.
//

#include "RenderingContext.h"

#include "../App.h"
#include "EngineObject.h"
#include "GameObject.h"
#include "Geometry.h"
#include "../../Minecraft/Quad.h"

RenderingContext::RenderingContext(App *app) {
    this->app = app;
}

RenderingContext::~RenderingContext() {

}

void RenderingContext::render() {
    app->setUpGlobalUniforms();

    vector<shared_ptr<RenderedObject>>::iterator iter;
    for(iter = app->getObjectsToRenderBegin(); iter != app->getObjectsToRenderEnd(); ++iter){
        if((*iter) != nullptr){
            shared_ptr<Geometry> curGeometry = (*iter)->getGeometryPtr();
            if(selectedGeometry != curGeometry){
                if(selectedGeometry != nullptr){
                    selectedGeometry->unselect();
                }
                selectedGeometry = curGeometry;
                curGeometry->select();
            }
            (*iter)->fastRender();
        }
    }
}
