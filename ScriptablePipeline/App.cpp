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
#include "EngineObjects/Skybox.h"

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
    Sp_Texture cube_texture = make_shared<Texture>("../Images/dirt.bmp");
    textures.push_back(cube_texture);

    //Sp_Geometry cubeMesh = make_shared<Geometry>(cubeVertexPos, cubeVertexPos, cubeVertexUv, 6*2*3, nullptr, 0);
    //geometries.push_back(cubeMesh);

    ModelLoader *loader = new ModelLoader();
    string str = getRootPath() + "/Models/untitled.obj";

    loader->import(&*str.begin());
    loader->loadMeshes(geometries);

    for (int i = 0; i < loader->getNumMesh(); ++i) {

        Sp_GameObject grass = make_shared<GameObject>(this, i, 0);
        objects.push_back(grass);
        objectsToRender.push_back(grass);
    }

    WorldGeneration *World = new WorldGeneration(2, 0.5);

    World->generateWorld(this);
    VectorEngineObject1D generatedCubes = World->getCubes();

    objects.insert(objects.end(), generatedCubes.begin(), generatedCubes.end());
    objectsToRender.insert(objectsToRender.end(), generatedCubes.begin(), generatedCubes.end());
    aiReleaseImport(loader->getAiScene());

    Sp_Geometry cubeMesh = make_shared<Geometry>(cubeVertexPos, cubeVertexPos, cubeVertexUv, 6 * 2 * 3,
                                                 nullptr, 0);
    geometries.push_back(cubeMesh);

    Sp_GameObject cube = make_shared<GameObject>(this, 1, 0);
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

    skybox = make_shared<Skybox>(this, "../Images/skybox/skybox_right.bmp",
                                 "../Images/skybox/skybox_left.bmp",
                                 "../Images/skybox/skybox_up.bmp",
                                 "../Images/skybox/skybox_down.bmp",
                                 "../Images/skybox/skybox_front.bmp",
                                 "../Images/skybox/skybox_back.bmp", width, height);

    shaderID = loadShader::LoadShaders("/Shaders/ColoredCube.vertexshader", "/Shaders/ColoredCube.fragmentshader");
    glUseProgram(shaderID);

    pointLightWorldPosID = glGetUniformLocation(shaderID, "PointLightWorldPos");
    pointLightColorID = glGetUniformLocation(shaderID, "PointLightColor");
    pointLightPowerID = glGetUniformLocation(shaderID, "PointLightPower");

    ambientLightColorID = glGetUniformLocation(shaderID, "AmbientLightColor");
    ambientLightPowerID = glGetUniformLocation(shaderID, "AmbientLightPower");

    directionalLightColorID = glGetUniformLocation(shaderID, "DirectionalLightColor");
    directionalLightDirectionID = glGetUniformLocation(shaderID, "DirectionalLightDirection");
    directionalLightPowerID = glGetUniformLocation(shaderID, "DirectionalLightPower");

    specularPowerID = glGetUniformLocation(shaderID, "SpecularPower");

    skybox->setupOpenGL();
}

void App::main_loop() {

    glUseProgram(shaderID);
    mainCamera->update(deltaTime);

    RenderingContext *renderingContext = new RenderingContext(this);
    renderingContext->render();

    if (isDayCycleEnabled) {
        dayTime += deltaTime * 10;
        while (dayTime >= dayTimeLength) {
            dayTime -= dayTimeLength;
        }
        float angle = (dayTime / (float) dayTimeLength) * 2 * pi<float>();
        directionalLightDirection = vec3(-cos(angle), sin(angle), 0.1f);
    }

    skybox->setTime(dayTime / (float) dayTimeLength);
    skybox->draw();

    drawImGUI();
}

void App::handle_events() {
    SDL_Event curEvent;
    ImGuiIO &io = ImGui::GetIO();
    while (SDL_PollEvent(&curEvent)) {
        ImGui_ImplSDL2_ProcessEvent(&curEvent);
        switch (curEvent.type) {
            case SDL_QUIT:
                app_running = false;
                return;
            case SDL_MOUSEBUTTONDOWN:
                if (!io.WantCaptureMouse) {
                    isDragging = true;
                }
                //... app processing other events;
                break;
            case SDL_MOUSEBUTTONUP:
                isDragging = false; // cancelling dragging even if imgui captures mouse events
                break;
            case SDL_MOUSEMOTION:
                if (!io.WantCaptureMouse) {
                    float epsilon = 0.01f;

                    if (isDragging) {
                        vec3 eulerAngles = mainCamera->transform->getEulerAngles();

                        if (abs(eulerAngles.z) < epsilon) {
                            eulerAngles.x -= curEvent.motion.yrel * mouseSensitivity * deltaTime;
                            eulerAngles.y -= curEvent.motion.xrel * mouseSensitivity * deltaTime;
                            if (eulerAngles.y < -90) {
                                eulerAngles.x += 180;
                                eulerAngles.y = -eulerAngles.y - 180;
                                eulerAngles.z += 180;
                            } else if (eulerAngles.y > 90) {
                                eulerAngles.x += 180;
                                eulerAngles.y = -eulerAngles.y + 180;
                                eulerAngles.z += 180;
                            }
                        } else {
                            eulerAngles.x -= curEvent.motion.yrel * mouseSensitivity * deltaTime;
                            eulerAngles.y += curEvent.motion.xrel * mouseSensitivity * deltaTime;
                            if (eulerAngles.y < -90) {
                                eulerAngles.x += 180;
                                eulerAngles.y = -eulerAngles.y + 180;
                                eulerAngles.z += 180;
                            } else if (eulerAngles.y > 90) {
                                eulerAngles.x += 180;
                                eulerAngles.y = -eulerAngles.y - 180;
                                eulerAngles.z += 180;
                            }
                        }
                        quat quatPitch = angleAxis(radians(eulerAngles.x), vec3(1, 0, 0));
                        quat quatYaw = angleAxis(radians(eulerAngles.y), vec3(0, 1, 0));
                        quat quatRoll = angleAxis(radians(eulerAngles.z), vec3(0, 0, 1));
                        mainCamera->transform->setRotation(mat4_cast(normalize(quatRoll * quatYaw * quatPitch)));
                    }
                }
                break;
            case SDL_KEYDOWN:
                if (!io.WantCaptureKeyboard) {
                    float epsilon = 0.0001f;
                    switch (curEvent.key.keysym.sym) {
                        case SDLK_LEFT:
                        case SDLK_q:
                            if (cameraVelocity[0] >= -epsilon) {
                                cameraVelocity[0] = -cameraSpeed;
                            }
                            break;
                        case SDLK_RIGHT:
                        case SDLK_d:
                            if (cameraVelocity[0] <= epsilon) {
                                cameraVelocity[0] = cameraSpeed;
                            }
                            break;
                        case SDLK_UP:
                        case SDLK_z:
                            if (cameraVelocity[2] >= -epsilon) {
                                cameraVelocity[2] = -cameraSpeed;
                            }
                            break;
                        case SDLK_DOWN:
                        case SDLK_s:
                            if (cameraVelocity[2] <= epsilon) {
                                cameraVelocity[2] = cameraSpeed;
                            }
                            break;
                        case SDLK_LCTRL:
                        case SDLK_a:
                            if (cameraVelocity[1] >= -epsilon) {
                                cameraVelocity[1] = -cameraSpeed;
                            }
                            break;
                        case SDLK_LSHIFT:
                        case SDLK_e:
                            if (cameraVelocity[1] <= epsilon) {
                                cameraVelocity[1] = cameraSpeed;
                            }
                            break;
                    }
                }
                break;
            case SDL_KEYUP:
                if (!io.WantCaptureKeyboard) {
                    float epsilon = 0.0001f;
                    switch (curEvent.key.keysym.sym) {
                        case SDLK_LEFT:
                        case SDLK_q:
                            if (cameraVelocity[0] < -epsilon) {
                                cameraVelocity[0] = 0;
                            }
                            break;
                        case SDLK_RIGHT:
                        case SDLK_d:
                            if (cameraVelocity[0] > epsilon) {
                                cameraVelocity[0] = 0;
                            }
                            break;
                        case SDLK_UP:
                        case SDLK_z:
                            if (cameraVelocity[2] < -epsilon) {
                                cameraVelocity[2] = 0;
                            }
                            break;
                        case SDLK_DOWN:
                        case SDLK_s:
                            if (cameraVelocity[2] > epsilon) {
                                cameraVelocity[2] = 0;
                            }
                            break;
                        case SDLK_LCTRL:
                        case SDLK_a:
                            if (cameraVelocity[1] < -epsilon) {
                                cameraVelocity[1] = 0;
                            }
                            break;
                        case SDLK_LSHIFT:
                        case SDLK_e:
                            if (cameraVelocity[1] > epsilon) {
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

Sp_Geometry App::getGeometry(int geometryID) {
    return Sp_Geometry(geometries[geometryID]);
}

Sp_Texture App::getTexture(int textureID) {
    return Sp_Texture(textures[textureID]);
}

Sp_Camera App::getMainCamera() {
    return Sp_Camera(mainCamera);
}

Sp_EngineObject App::getObject(int i) {
    return Sp_EngineObject(objects[i]);
}

int App::getObjectsCount() {
    return objects.size();
}

vector<Sp_EngineObject>::iterator App::getObjectsBegin() {
    return objects.begin();
}

vector<Sp_EngineObject>::iterator App::getObjectsEnd() {
    return objects.end();
}

Sp_GameObject App::getObjectToRender(int i) {
    return Sp_GameObject(objectsToRender[i]);
}

int App::getObjectsToRenderCount() {
    return objectsToRender.size();
}

vector<Sp_GameObject>::iterator App::getObjectsToRenderBegin() {
    return objectsToRender.begin();
}

vector<Sp_GameObject>::iterator App::getObjectsToRenderEnd() {
    return objectsToRender.end();
}

int App::getDeltaTime() {
    return deltaTime;
}

GLuint App::getShaderID() {
    return shaderID;
}

void App::setUpGlobalUniforms() {
    // point light
    glUniform3fv(pointLightWorldPosID, 1, &pointLightWorldPos[0]);
    glUniform3fv(pointLightColorID, 1, &pointLightColor[0]);
    glUniform1f(pointLightPowerID, pointLightPower);

    // ambient light
    glUniform3fv(ambientLightColorID, 1, &ambientLightColor[0]);
    glUniform1f(ambientLightPowerID, ambientLightPower);

    // directional light (sun)
    glUniform3fv(directionalLightDirectionID, 1, &directionalLightDirection[0]);
    glUniform3fv(directionalLightColorID, 1, &directionalLightColor[0]);
    glUniform1f(directionalLightPowerID, directionalLightPower);

    //specular power
    glUniform1f(specularPowerID, specularPower);
}

void App::drawImGUI() {
    //Render Loop
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(win);

    ImGui::NewFrame();

    ImGui::Begin("Perfs");
    ImGui::Text("Frame Time (ms) new : %d", deltaTime);
    ImGui::Text("FPS : %f", 1.0 / (float) deltaTime * 1000);
    ImGui::End();

    ImGui::Begin("Rendering");
    ImGui::Text("Mouse sensitivity : ");
    ImGui::SameLine();
    ImGui::InputFloat("##1", &mouseSensitivity);
    ImGui::Text("Wireframe : ");
    ImGui::SameLine();
    ImGui::Checkbox("##2", &mainCamera->isWireframe);

    ImGui::Text("Point light power : ");
    ImGui::SameLine();
    ImGui::InputFloat("##3", &pointLightPower);
    ImGui::Text("Point light color : ");
    ImGui::SameLine();
    ImGui::ColorEdit3("##4", &pointLightColor[0]);
    ImGui::Text("Point light world pos : ");
    ImGui::SameLine();
    ImGui::InputFloat3("##5", &pointLightWorldPos[0]);

    ImGui::Text("Ambient light power : ");
    ImGui::SameLine();
    ImGui::InputFloat("##6", &ambientLightPower);
    ImGui::Text("Ambient light color : ");
    ImGui::SameLine();
    ImGui::ColorEdit3("##7", &ambientLightColor[0]);

    ImGui::Text("Enable day cycle : ");
    ImGui::SameLine();
    ImGui::Checkbox("##12", &isDayCycleEnabled);
    if (isDayCycleEnabled) {
        ImGui::Text("Day time : ");
        ImGui::SameLine();
        ImGui::SliderInt("##8", &dayTime, 0, dayTimeLength);
    } else {
        ImGui::Text("Directional light direction : ");
        ImGui::SameLine();
        ImGui::InputFloat3("##9", &directionalLightDirection[0]);
    }
    ImGui::Text("Directional light power : ");
    ImGui::SameLine();
    ImGui::InputFloat("##10", &directionalLightPower);
    ImGui::Text("Directional light color : ");
    ImGui::SameLine();
    ImGui::ColorEdit3("##11", &directionalLightColor[0]);

    ImGui::End();

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}