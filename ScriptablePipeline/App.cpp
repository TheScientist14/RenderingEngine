//
// Created by tsaury on 11/03/2022.
//

#include "App.h"

#include <string>

#include "SDL.h"

#include <GL/glew.h>

#include "imgui_impl_sdl.h"
#include "backends/imgui_impl_opengl3.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/vector3.h>

#include "../helper/ModelLoader.h"
#include "../helper/stb_image.h"
#include "../helper/find_exe_path.h"
#include "../Shaders/loadShader.h"
#include "../../Minecraft/WorldGeneration.h"

#include "EngineObjects/Transform.h"
#include "EngineObjects/Geometry.h"
#include "EngineObjects/Texture.h"
#include "EngineObjects/Camera.h"
#include "EngineObjects/EngineObject.h"
#include "EngineObjects/GameObject.h"
#include "EngineObjects/RenderingContext.h"

App::~App() {

}

void App::gl_init() {

#pragma region cube_vertex
    static const float cubeVertexPos[] = {
            -1.0f, -1.0f, -1.0f, // triangle 1 : begin
            -1.0f, -1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, // triangle 1 : end
            1.0f, 1.0f, -1.0f, // triangle 2 : begin
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f, // triangle 2 : end
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,
            -1.0f, -1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, -1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, -1.0f,
            1.0f, -1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, -1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, -1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, -1.0f, 1.0f
    };
#pragma endregion cube_vertex

#pragma region UV_buffer
    // Two UV coordinatesfor each vertex. They were created with Blender. You'll learn shortly how to do this yourself.
    static const GLfloat cubeVertexUv[] = {
            0.000059f, 1.0f - 0.000004f,
            0.000103f, 1.0f - 0.336048f,
            0.335973f, 1.0f - 0.335903f,
            1.000023f, 1.0f - 0.000013f,
            0.667979f, 1.0f - 0.335851f,
            0.999958f, 1.0f - 0.336064f,
            0.667979f, 1.0f - 0.335851f,
            0.336024f, 1.0f - 0.671877f,
            0.667969f, 1.0f - 0.671889f,
            1.000023f, 1.0f - 0.000013f,
            0.668104f, 1.0f - 0.000013f,
            0.667979f, 1.0f - 0.335851f,
            0.000059f, 1.0f - 0.000004f,
            0.335973f, 1.0f - 0.335903f,
            0.336098f, 1.0f - 0.000071f,
            0.667979f, 1.0f - 0.335851f,
            0.335973f, 1.0f - 0.335903f,
            0.336024f, 1.0f - 0.671877f,
            1.000004f, 1.0f - 0.671847f,
            0.999958f, 1.0f - 0.336064f,
            0.667979f, 1.0f - 0.335851f,
            0.668104f, 1.0f - 0.000013f,
            0.335973f, 1.0f - 0.335903f,
            0.667979f, 1.0f - 0.335851f,
            0.335973f, 1.0f - 0.335903f,
            0.668104f, 1.0f - 0.000013f,
            0.336098f, 1.0f - 0.000071f,
            0.000103f, 1.0f - 0.336048f,
            0.000004f, 1.0f - 0.671870f,
            0.336024f, 1.0f - 0.671877f,
            0.000103f, 1.0f - 0.336048f,
            0.336024f, 1.0f - 0.671877f,
            0.335973f, 1.0f - 0.335903f,
            0.667969f, 1.0f - 0.671889f,
            1.000004f, 1.0f - 0.671847f,
            0.667979f, 1.0f - 0.335851f
    };

#pragma endregion UV_buffer

#pragma region cube_vertex_elements
    float cube_vertices[] = {
            1, 1, 1, 1, -1, 1, -1, -1, 1, -1, 1, 1,
            1, 1, 1, 1, -1, 1, 1, -1, -1, 1, 1, -1,
            1, 1, 1, 1, 1, -1, -1, 1, -1, -1, 1, 1,
            1, 1, -1, 1, -1, -1, -1, -1, -1, -1, 1, -1,
            -1, 1, 1, -1, -1, 1, -1, -1, -1, -1, 1, -1,
            1, -1, 1, 1, -1, -1, -1, -1, -1, -1, -1, 1
    };
#pragma endregion cube_vertex_elements

// Draw some widgets
    shared_ptr<Texture> cube_texture = make_shared<Texture>("../Images/dirt.bmp");
    textures.push_back(cube_texture);

    //shared_ptr<Geometry> cubeMesh = make_shared<Geometry>(cubeVertexPos, cubeVertexPos, cubeVertexUv, 6*2*3, nullptr, 0);
    //geometries.push_back(cubeMesh);

    ModelLoader *loader = new ModelLoader();
    string str = getRootPath() + "/Models/untitled.obj";

    loader->import(&*str.begin());
    loader->loadMeshes(geometries);

    for (int i = 0; i < loader->getNumMesh(); ++i) {

        shared_ptr<GameObject> grass = make_shared<GameObject>(this, i, 0);
        objects.push_back(grass);
        objectsToRender.push_back(grass);
    }

    WorldGeneration *World = new WorldGeneration(2, 0.5);

    World->generateWorld(this);
    VectorEngineObject1D generatedCubes = World->getCubes();

    objects.insert(objects.end(), generatedCubes.begin(), generatedCubes.end());
    objectsToRender.insert(objectsToRender.end(), generatedCubes.begin(), generatedCubes.end());
    aiReleaseImport( loader->getAiScene());

    shared_ptr<Geometry> cubeMesh = make_shared<Geometry>(cubeVertexPos, cubeVertexPos, cubeVertexUv, 6 * 2 * 3,
                                                          nullptr, 0);
    geometries.push_back(cubeMesh);

    shared_ptr<GameObject> cube = make_shared<GameObject>(this, 1, 0);
    objects.push_back(cube);
    objectsToRender.push_back(cube);

    for (int i = 0; i < geometries.size(); i++) {
        geometries[i]->bind();
    }
    for (int i = 0; i < textures.size(); i++) {
        textures[i]->bind();
    }

    mainCamera = make_shared<Camera>(this);
    mainCamera->transform->move(vec3(0, 0, 10));

    shaderID = loadShader::LoadShaders("/Shaders/ColoredCube.vertexshader", "/Shaders/ColoredCube.fragmentshader");
    glUseProgram(shaderID);

    LightWorldPosID = glGetUniformLocation(shaderID, "LightWorldPos");
    LightColorID = glGetUniformLocation(shaderID, "LightColor");
    LightPowerID = glGetUniformLocation(shaderID, "LightPower");
}

void App::main_loop() {
    mainCamera->update(deltaTime);

    //Render Loop
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(win);

    ImGui::NewFrame();

    ImGui::Begin("Perfs");
    ImGui::Text("Frame Time (ms) new : %d", deltaTime);
    ImGui::Text("FPS : %f", 1.0 / (float)deltaTime * 1000) ;
    ImGui::InputFloat("Sens", &mouseSensitivity);
    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());

    RenderingContext* renderingContext = new RenderingContext(this);
    renderingContext->render();
}

void App::handle_events() {
    SDL_Event curEvent;
    ImGuiIO& io = ImGui::GetIO();
    while (SDL_PollEvent(&curEvent)) {
        ImGui_ImplSDL2_ProcessEvent(&curEvent);
        switch (curEvent.type) {
            case SDL_QUIT:
                app_running = false;
                return;
            case SDL_MOUSEBUTTONDOWN:
                if (!io.WantCaptureMouse)
                {
                    isDragging = true;
                }
                //... app processing other events;
                break;
            case SDL_MOUSEBUTTONUP:
                isDragging = false; // cancelling dragging even if imgui captures mouse events
                break;
            case SDL_MOUSEMOTION:
                if (!io.WantCaptureMouse){
                    float epsilon = 0.01f;
                    if (isDragging) {
                        vec3 eulerAngles = mainCamera->transform->getEulerAngles();
                        if(abs(eulerAngles.y) > 80) {
                            printf("%f, %f, %f", eulerAngles.x, eulerAngles.y, eulerAngles.z);
                        }
                        // 0 -90 0 ~ 180 -90- 180
                        eulerAngles.x += -curEvent.motion.yrel * mouseSensitivity * deltaTime;
                        eulerAngles.y += -curEvent.motion.xrel * mouseSensitivity * deltaTime;
                        if(abs(eulerAngles.z) < epsilon){
                            if(eulerAngles.y < -90){
                                eulerAngles.x += 180;
                                eulerAngles.y += 180;
                                eulerAngles.z = 180;
                            }
                            else if(eulerAngles.y > 90){
                                eulerAngles.x += 180;
                                eulerAngles.y -= 180;
                                eulerAngles.z = 180;
                            }
                        }

                        if(abs(eulerAngles.y) > 80){
                            printf(" %f, %f, %f\n", eulerAngles.x, eulerAngles.y, eulerAngles.z);
                        }

                        quat quatPitch = angleAxis(radians(eulerAngles.x), vec3(1,0,0));
                        quat quatYaw = angleAxis(radians(eulerAngles.y), vec3(0,1,0));
                        mainCamera->transform->setRotation(mat4_cast(normalize(quatYaw * quatPitch)));
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (!io.WantCaptureKeyboard)
                {
                    float epsilon = 0.0001f;
                    switch (curEvent.key.keysym.sym) {
                        case SDLK_LEFT: case SDLK_q:
                            if(cameraVelocity[0] >= -epsilon){
                                cameraVelocity[0] = -cameraSpeed;
                            }
                            break;
                        case SDLK_RIGHT: case SDLK_d:
                            if(cameraVelocity[0] <= epsilon) {
                                cameraVelocity[0] = cameraSpeed;
                            }
                            break;
                        case SDLK_UP: case SDLK_z:
                            if(cameraVelocity[2] >= -epsilon) {
                                cameraVelocity[2] = -cameraSpeed;
                            }
                            break;
                        case SDLK_DOWN: case SDLK_s:
                            if(cameraVelocity[2] <= epsilon) {
                                cameraVelocity[2] = cameraSpeed;
                            }
                            break;
                        case SDLK_LCTRL: case SDLK_a:
                            if(cameraVelocity[1] >= -epsilon) {
                                cameraVelocity[1] = -cameraSpeed;
                            }
                            break;
                        case SDLK_LSHIFT: case SDLK_e:
                            if(cameraVelocity[1] <= epsilon) {
                                cameraVelocity[1] = cameraSpeed;
                            }
                            break;
                    }
                }
                break;
            case SDL_KEYUP:
                if(!io.WantCaptureKeyboard){
                    float epsilon = 0.0001f;
                    switch (curEvent.key.keysym.sym) {
                        case SDLK_LEFT: case SDLK_q:
                            if(cameraVelocity[0] < -epsilon) {
                                cameraVelocity[0] = 0;
                            }
                            break;
                        case SDLK_RIGHT: case SDLK_d:
                            if(cameraVelocity[0] > epsilon) {
                                cameraVelocity[0] = 0;
                            }
                            break;
                        case SDLK_UP: case SDLK_z:
                            if(cameraVelocity[2] < -epsilon) {
                                cameraVelocity[2] = 0;
                            }
                            break;
                        case SDLK_DOWN: case SDLK_s:
                            if(cameraVelocity[2] > epsilon) {
                                cameraVelocity[2] = 0;
                            }
                            break;
                        case SDLK_LCTRL: case SDLK_a:
                            if(cameraVelocity[1] < -epsilon) {
                                cameraVelocity[1] = 0;
                            }
                            break;
                        case SDLK_LSHIFT: case SDLK_e:
                            if(cameraVelocity[1] > epsilon) {
                                cameraVelocity[1] = 0;
                            }
                            break;
                    }
                }
                break;
        }
    }
    mainCamera->transform->move(
            cameraVelocity[2] * deltaTime * mainCamera->transform->getForward()
            + cameraVelocity[0] * deltaTime * mainCamera->transform->getRight());
    vec3 tmpPos = mainCamera->transform->getPosition();
    tmpPos[1] += cameraVelocity[1] * deltaTime;
    mainCamera->transform->setPosition(tmpPos);
}

void App::clean() {
    // TODO : Call desctructor ?
}

shared_ptr<Geometry> App::getGeometry(int geometryID) {
    return shared_ptr<Geometry>(geometries[geometryID]);
}

shared_ptr<Texture> App::getTexture(int textureID) {
    return shared_ptr<Texture>(textures[textureID]);
}

shared_ptr<Camera> App::getMainCamera() {
    return shared_ptr<Camera>(mainCamera);
}

shared_ptr<EngineObject> App::getObject(int i) {
    return shared_ptr<EngineObject>(objects[i]);
}

int App::getObjectsCount() {
    return objects.size();
}

vector<shared_ptr<EngineObject>>::iterator App::getObjectsBegin() {
    return objects.begin();
}

vector<shared_ptr<EngineObject>>::iterator App::getObjectsEnd() {
    return objects.end();
}

shared_ptr<GameObject> App::getObjectToRender(int i) {
    return shared_ptr<GameObject>(objectsToRender[i]);
}

int App::getObjectsToRenderCount() {
    return objectsToRender.size();
}

vector<shared_ptr<GameObject>>::iterator App::getObjectsToRenderBegin() {
    return objectsToRender.begin();
}

vector<shared_ptr<GameObject>>::iterator App::getObjectsToRenderEnd() {
    return objectsToRender.end();
}

int App::getDeltaTime() {
    return deltaTime;
}

GLuint App::getShaderID() {
    return shaderID;
}

void App::setUpGlobalUniforms() {
    glUniform3f(LightWorldPosID, 2, 200, 2);
    glUniform3f(LightColorID, 1, 1, 1);
    glUniform1f(LightPowerID, 12000);
}
