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
    shared_ptr<Texture> cube_texture = make_shared<Texture>("../Images/uvtemplate.bmp");
    textures.push_back(cube_texture);

    //shared_ptr<Geometry> cubeMesh = make_shared<Geometry>(cubeVertexPos, cubeVertexPos, cubeVertexUv, 6*2*3, nullptr, 0);
    //geometries.push_back(cubeMesh);

    ModelLoader *loader = new ModelLoader();
    string str = getRootPath() + "/Models/untitled.obj";

    loader->import(&*str.begin());
    loader->loadMeshes(geometries);

    for (int i = 0; i < loader->getNumMesh(); ++i) {

        shared_ptr<EngineObject> grass = make_shared<GameObject>(this, i, 0);
        objects.push_back(grass);
    }

    WorldGeneration *World = new WorldGeneration(32, 2, 0.5);

    vector<shared_ptr<EngineObject>> generatedCubes = World->generateWorld(this);

    objects.insert(objects.end(), generatedCubes.begin(), generatedCubes.end());
    aiReleaseImport( loader->getAiScene());

    shared_ptr<Geometry> cubeMesh = make_shared<Geometry>(cubeVertexPos, cubeVertexPos, cubeVertexUv, 6 * 2 * 3,
                                                          nullptr, 0);
    geometries.push_back(cubeMesh);

    shared_ptr<EngineObject> cube = make_shared<GameObject>(this, 1, 0);
    objects.push_back(cube);

    for (int i = 0; i < geometries.size(); i++) {
        geometries[i]->bind();
    }
    for (int i = 0; i < textures.size(); i++) {
        textures[i]->bind();
    }

    mainCamera = make_shared<Camera>(this);
    mainCamera->transform->position += vec3(0, 65, 10);

    shaderID = loadShader::LoadShaders("/Shaders/ColoredCube.vertexshader", "/Shaders/ColoredCube.fragmentshader");
    glUseProgram(shaderID);
}

void App::main_loop() {
    mainCamera->update(deltaTime);
    GLuint LightWorldPosID = glGetUniformLocation(shaderID, "LightWorldPos");
    glUniform3f(LightWorldPosID, 2, 200, 2);
    GLuint LightColorID = glGetUniformLocation(shaderID, "LightColor");
    glUniform3f(LightColorID, 1, 1, 1);
    GLuint LightPowerID = glGetUniformLocation(shaderID, "LightPower");
    glUniform1f(LightPowerID, 12000);

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
    float epsilon = 0.00001f;
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
                    if (isDragging) {
                        mainCamera->transform->rotation[1] -= curEvent.motion.xrel * mouseSensitivity * deltaTime;
                        mainCamera->transform->rotation[0] -= curEvent.motion.yrel * mouseSensitivity * deltaTime;
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (!io.WantCaptureKeyboard)
                {
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
    mainCamera->transform->position += cameraVelocity[2] * deltaTime * mainCamera->transform->getForward();
    mainCamera->transform->position += cameraVelocity[0] * deltaTime * mainCamera->transform->getRight();
    mainCamera->transform->position[1] += cameraVelocity[1] * deltaTime;
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

vector<shared_ptr<EngineObject>>::iterator App::getObjectsIterator() {
    return objects.begin();
}

shared_ptr<GameObject> App::getObjectToRender(int i) {
    return shared_ptr<GameObject>(objectsToRender[i]);
}

int App::getObjectsToRenderCount() {
    return objectsToRender.size();
}

vector<shared_ptr<GameObject>>::iterator App::getObjectsToRenderIterator() {
    return objectsToRender.begin();
}

int App::getDeltaTime() {
    return deltaTime;
}

GLuint App::getShaderID() {
    return shaderID;
}

App::~App() {

}