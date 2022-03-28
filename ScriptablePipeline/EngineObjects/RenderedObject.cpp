//
// Created by avarnier-navarro on 28/03/2022.
//

#include "RenderedObject.h"

void RenderedObject::update(int deltaTime) {

}

RenderedObject::RenderedObject(App *app, shared_ptr<Geometry> geometryPtr, shared_ptr<Texture> texturePtr) : EngineObject(app) {

    this->geometryPtr = geometryPtr;
    this->texturePtr = texturePtr;
}
RenderedObject::RenderedObject(App *app) : EngineObject(app) {
}

RenderedObject::~RenderedObject() {

}

shared_ptr<Geometry> RenderedObject::getGeometryPtr() const {
    return geometryPtr;
}

shared_ptr<Texture> RenderedObject::getTexturePtr() const {
    return texturePtr;
}

void RenderedObject::fastRender() const {
}
