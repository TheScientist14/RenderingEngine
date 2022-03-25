//
// Created by tsaury on 21/03/2022.
//

#include "RenderingContext.h"

#include "../App.h"
#include "EngineObject.h"
#include "GameObject.h"
#include "Geometry.h"

RenderingContext::RenderingContext(App *app) {
    this->app = app;
}

RenderingContext::~RenderingContext() {

}

void RenderingContext::render() {
    app->setUpGlobalUniforms();

    for (int i = 0; i < app->getObjectsCount(); i++) {
        if(app->getObject(i) != nullptr) {
            app->getObject(i)->update(app->getDeltaTime());
        }
    }

    vector<shared_ptr<GameObject>>::iterator iter;
    for(iter = app->getObjectsToRenderBegin(); iter != app->getObjectsToRenderEnd(); ++iter){
        if((*iter) != nullptr){
            shared_ptr<Geometry> curGeometry = app->getGeometry((*iter)->getGeometryIndex());
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
