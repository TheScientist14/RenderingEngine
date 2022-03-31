//
// Created by tsaury on 14/03/2022.
//

#pragma once

#include "vector"
#include "memory"

#include <GL/glew.h>

#include <glm/vec3.hpp>

#include "../BaseApp.h"
#include "EngineObjects/RenderingContext.h"

using namespace std;
using namespace glm;

class Geometry;
class Texture;
class Camera;
class EngineObject;
class RenderedObject;
class Quad;
class Cube;
class GameObject;
class Skybox;
class ChunkGeneration;

typedef shared_ptr<Geometry> Sp_Geometry;
typedef shared_ptr<Texture> Sp_Texture;
typedef shared_ptr<Camera> Sp_Camera;
typedef shared_ptr<EngineObject> Sp_EngineObject;
typedef shared_ptr<RenderedObject> Sp_RenderedObject;
typedef shared_ptr<Quad> Sp_QuadObject;
typedef shared_ptr<GameObject> Sp_GameObject;

class App : public BaseApp {

public:
    typedef vector<shared_ptr<ChunkGeneration>> Terrain;

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
    vector<Sp_RenderedObject>::iterator getObjectsToRenderBegin();
    vector<Sp_RenderedObject>::iterator getObjectsToRenderEnd();
    Sp_RenderedObject getObjectToRender(int i);
    int getObjectsToRenderCount();
    int getDeltaTime();
    GLuint getShaderID();
    RenderingContext::TerrainRenderMode getRenderMode();
    RenderingContext *renderingContext;

    void setUpGlobalUniforms();

    virtual ~App();

protected:

    struct HitInfo {
        bool hasHit;
        vec3 blockHitPos;
        vec3 faceHit; // unit vector of the normal of the plane hit
    };

    GLuint shaderID;
    vector<shared_ptr<Geometry>> geometries;
    vector<shared_ptr<Texture>> textures;
    vector<shared_ptr<EngineObject>> objects;
    vector<shared_ptr<RenderedObject>> objectsToRender;
    shared_ptr<Camera> mainCamera;
    bool isMouseCaptured = true;
    Terrain map;
    Terrain mapReload;
    bool isDragging;
    int nbChunk = 4;

    void drawImGUI();
    HitInfo raycastFromCamera();
    void loadChunk();
    shared_ptr<ChunkGeneration> getChunk(int prmX, int prmY);

    float mouseSensitivity = 0.08f;
    float cameraSpeed = 0.01f;
    vec3 cameraVelocity;

    shared_ptr<Skybox> skybox;

    /**
     *  ----------- LIGHTS -----------
     **/

    GLuint specularPowerID;
    float specularPower = 5;

    GLuint pointLightWorldPosID;
    GLuint pointLightColorID;
    GLuint pointLightPowerID;
    float pointLightPower = 60;
    vec3 pointLightColor = vec3(1, 1, 1);
    vec3 pointLightWorldPos = vec3(0, 20, 0);

    GLuint ambientLightColorID;
    GLuint ambientLightPowerID;
    float ambientLightPower = 0.1;
    vec3 ambientLightColor = vec3(1,1,1);

    bool isDayCycleEnabled = true;
    int dayTime = 0;
    const int dayTimeLength = 1200000; // 1000 * 60 * 20 = 20 min
    GLuint directionalLightDirectionID;
    GLuint directionalLightColorID;
    GLuint directionalLightPowerID;
    float directionalLightPower = 1;
    vec3 directionalLightColor = vec3(0.953125f, 0.91015625f, 0.60546875f);
    vec3 directionalLightDirection = vec3(0, -1, 0.1f);
    /*extern*/ RenderingContext::TerrainRenderMode renderMode = RenderingContext::Opti;
};



