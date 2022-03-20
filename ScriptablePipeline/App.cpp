//
// Created by tsaury on 11/03/2022.
//

#include "App.h"

#include <string>

#include "SDL.h"

#include <GL/glew.h>

#include "imgui_impl_sdl.h"
#include "backends/imgui_impl_sdl.h"
#include "backends/imgui_impl_opengl3.h"


#include <assimp/postprocess.h>
#include "../helper/ModelLoader.h"

#include "../helper/stb_image.h"
#include "../helper/find_exe_path.h"
#include "../Shaders/loadShader.h"
#include "EngineObjects/GameObject.h"

#include "EngineObjects/Transform.h"
#include "../../Minecraft/WorldGeneration.h"

#include <assimp/cimport.h>
#include <assimp/scene.h>
#include <assimp/vector3.h>

using namespace std;

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

    auto temp = World->generateWorld(this);

    objects.insert(objects.end(), temp.begin(), temp.end());
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

/*    shared_ptr<EngineObject> cube = make_shared<GameObject>(this, 0, 0);
    objects.push_back(cube);
    cube->transform.rotation = vec3(30, 45, 0);
    shared_ptr<EngineObject> cube2 = make_shared<GameObject>(this, 0, 0);
    objects.push_back(cube2);
    cube2->transform.position = vec3(2, 0, 0);
    cube2->transform.rotation = vec3(30, 45, 0);*/

    mainCamera = make_shared<Camera>(this);
    mainCamera->transform->position += vec3(0, 55, 0);

/*    int n = 10;
    float gap = 0.5;
    float cubeSize = 2;
    vector<int> cubesIndex;
    for(int i = 0; i < n; i++){
        shared_ptr<EngineObject> cube = make_shared<GameObject>(this, 0, 0);
        cube->transform->rotation = vec3(0, 10 * i, 0);
        cube->transform->position = vec3(-i * (cubeSize + gap), 0, -i * (cubeSize + gap));
        cube->setParent(mainCamera);
        cubesIndex.push_back(objects.size());
        objects.push_back(cube);
        for(int j = 0; j < i; j++){
            shared_ptr<EngineObject> cube1 = make_shared<GameObject>(this, 0, 0);
            shared_ptr<EngineObject> cube2 = make_shared<GameObject>(this, 0, 0);
            cube1->transform->rotation = vec3(0, i * 10, 0);
            cube1->transform->position = vec3(-j * (cubeSize + gap), 0, -i * (cubeSize + gap));
            cube2->transform->rotation = vec3(0, i * 10, 0);
            cube2->transform->position = vec3(-i * (cubeSize + gap), 0, -j * (cubeSize + gap));
            cubesIndex.push_back(objects.size());
            objects.push_back(cube1);
            cubesIndex.push_back(objects.size());
            objects.push_back(cube2);
        }
    }*/

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


    for (int i = 0; i < objects.size(); i++) {
        objects[i]->update(deltaTime);
    }
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
    mainCamera->transform->position += cameraVelocity[1] * deltaTime;
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

GLuint App::getShaderID() {
    return shaderID;
}
