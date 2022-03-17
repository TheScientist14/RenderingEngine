//
// Created by tsaury on 14/03/2022.
//

#include "../BaseApp.h"
#include "vector"
#include "memory"
#include "EngineObjects/Geometry.h"
#include "EngineObjects/Texture.h"
#include "EngineObjects/Camera.h"
#include "EngineObjects/EngineObject.h"

using namespace std;

#pragma once


class App : public BaseApp {

public:
    void main_loop() override;
    void gl_init() override;
    void clean() override;
    void handle_events() override;

    shared_ptr<Geometry> getGeometry(int geometryID);
    shared_ptr<Texture> getTexture(int textureID);
    shared_ptr<Camera> getMainCamera();
    GLuint getShaderID();

protected:
    GLuint shaderID;
    vector<shared_ptr<Geometry>> geometries;
    vector<shared_ptr<Texture>> textures;
    vector<shared_ptr<EngineObject>> objects;
    shared_ptr<Camera> mainCamera;
    bool isDragging;

    float mouseSensitivity = 0.5f;
    float cameraSpeed = 0.5f;
};



