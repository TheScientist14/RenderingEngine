//
// Created by tsaury on 14/03/2022.
//

#pragma once

#include "vector"
#include "memory"

#include <GL/glew.h>

#include <glm/vec3.hpp>

#include "../BaseApp.h"

using namespace std;
using namespace glm;

class Geometry;
class Texture;
class Camera;
class EngineObject;
class GameObject;

typedef shared_ptr<Geometry> Sp_Geometry;
typedef shared_ptr<Texture> Sp_Texture;
typedef shared_ptr<Camera> Sp_Camera;
typedef shared_ptr<EngineObject> Sp_EngineObject;
typedef shared_ptr<GameObject> Sp_GameObject;

class App : public BaseApp {

public:
    void main_loop() override;
    void gl_init() override;
    void clean() override;
    void handle_events() override;

    Sp_Geometry getGeometry(int geometryID);
    Sp_Texture getTexture(int textureID);
    Sp_Camera getMainCamera();
    vector<Sp_EngineObject>::iterator getObjectsBegin();
    vector<Sp_EngineObject>::iterator getObjectsEnd();
    Sp_EngineObject getObject(int i);
    int getObjectsCount();
    vector<Sp_GameObject>::iterator getObjectsToRenderBegin();
    vector<Sp_GameObject>::iterator getObjectsToRenderEnd();
    Sp_GameObject getObjectToRender(int i);
    int getObjectsToRenderCount();
    int getDeltaTime();
    GLuint getShaderID();

    void setUpGlobalUniforms();

    virtual ~App();

protected:
    GLuint shaderID;
    GLuint LightWorldPosID;
    GLuint LightColorID;
    GLuint LightPowerID;
    vector<shared_ptr<Geometry>> geometries;
    vector<shared_ptr<Texture>> textures;
    vector<shared_ptr<EngineObject>> objects;
    vector<shared_ptr<GameObject>> objectsToRender;
    shared_ptr<Camera> mainCamera;
    bool isDragging;

    float mouseSensitivity = 0.08f;
    float cameraSpeed = 0.01f;
    vec3 cameraVelocity;
};



