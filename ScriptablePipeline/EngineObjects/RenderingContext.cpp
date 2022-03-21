//
// Created by tsaury on 21/03/2022.
//

#include "RenderingContext.h"

#include "../App.h"
#include "EngineObject.h"

RenderingContext::RenderingContext(App *app) {
    this->app = app;
}

RenderingContext::~RenderingContext() {

}

void RenderingContext::render() {

    vector<shared_ptr<GameObject>>::iterator iter = app->getObjectsToRenderIterator();
    //for(iter, iter..end();)

    for (int i = 0; i < app->getObjectsCount(); i++) {
        app->getObject(i)->update(app->getDeltaTime());
    }
}
