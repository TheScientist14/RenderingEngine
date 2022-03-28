//
// Created by tsaury on 14/03/2022.
//

#pragma once

#include "GL/glew.h"
#include "RenderedObject.h"

class GameObject : public RenderedObject{

public:
    struct ModelShaderData {
        mat4 MVP;
        mat4 M;
    };
    bool visible=true;

protected:
    shared_ptr<Geometry> geometryPtr;
    shared_ptr<Texture> texturePtr;
    ModelShaderData shaderData;

public:
    GameObject(App* app, shared_ptr<Geometry> geometryPtr, shared_ptr<Texture> texturePtr, bool visible);
    GameObject(App* app, shared_ptr<Geometry> geometryPtr, shared_ptr<Texture> texturePtr);

    void update(int deltaTime);

    //void render() const;
    void fastRender() const;

    shared_ptr<Geometry> getGeometryPtr() const override;
    shared_ptr<Texture> getTexturePtr() const override;

    ModelShaderData* computeShaderData();

};
