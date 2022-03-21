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

class App : public BaseApp {

public:
    void main_loop() override;
    void gl_init() override;
    void clean() override;
    void handle_events() override;

    shared_ptr<Geometry> getGeometry(int geometryID);
    shared_ptr<Texture> getTexture(int textureID);
    shared_ptr<Camera> getMainCamera();
    vector<shared_ptr<EngineObject>>::iterator getObjectsIterator();
    shared_ptr<EngineObject> getObject(int i);
    int getObjectsCount();
    vector<shared_ptr<GameObject>>::iterator getObjectsToRenderIterator();
    shared_ptr<GameObject> getObjectToRender(int i);
    int getObjectsToRenderCount();
    int getDeltaTime();
    GLuint getShaderID();

    virtual ~App();

protected:
    GLuint shaderID;
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



