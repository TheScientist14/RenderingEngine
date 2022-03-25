//
// Created by tsaury on 14/03/2022.
//

#pragma once

#include "EngineObject.h"
#include "GL/glew.h"

class GameObject : public EngineObject{

public:
    struct ModelShaderData {
        mat4 MVP;
        mat4 M;
    };
    bool visible=true;

protected:
    int geometryIndex;
    int textureIndex;
    ModelShaderData shaderData;

public:
    GameObject(App* app, int geometryIndex, int textureIndex, bool visible);
    GameObject(App* app, int geometryIndex, int textureIndex);

    void update(float deltaTime) override;

    void render() const;
    void fastRender() const;

    int getGeometryIndex() const;
    int getTextureIndex() const;

    ModelShaderData* computeShaderData();

};
