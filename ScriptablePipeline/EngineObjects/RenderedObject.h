//
// Created by avarnier-navarro on 28/03/2022.
//

#pragma once

#include "EngineObject.h"

class Geometry;
class Texture;

class RenderedObject : public EngineObject {
protected:
    RenderedObject(App* app, shared_ptr<Geometry> geometryPtr, shared_ptr<Texture> texturePtr);
    RenderedObject(App* app);
    virtual ~RenderedObject();

    shared_ptr<Geometry> geometryPtr;
    shared_ptr<Texture> texturePtr;
public:
    virtual void update(int deltaTime);

    virtual void fastRender() const;

    virtual shared_ptr<Geometry> getGeometryPtr() const;
    virtual shared_ptr<Texture> getTexturePtr() const;

};
