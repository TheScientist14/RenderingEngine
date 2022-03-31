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
#include "../../Minecraft/ChunkGeneration.h"

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

    mainCamera = make_shared<Camera>(this);
    mainCamera->transform->move(vec3(0, 0, 0));
// Draw some widgets
    Sp_Texture cube_texture = make_shared<Texture>("../Images/dirt.bmp");
    textures.push_back(cube_texture);

//    Sp_Geometry cubeMesh = make_shared<Geometry>(cubeVertexPos, cubeVertexPos, cubeVertexUv, 6*2*3, nullptr, 0);
//    geometries.push_back(cubeMesh);
//
    ModelLoader *loader = new ModelLoader();
    string str = getRootPath() + "/Models/untitled.obj";

    loader->import(&*str.begin());
    loader->loadMeshes(geometries);

//    for (int i = 0; i < loader->getNumMesh(); ++i) {
//
//        Sp_GameObject grass = make_shared<GameObject>(this, i, 0);
//        objects.push_back(grass);
//        objectsToRender.push_back(grass);
//    }

    //aiReleaseImport(loader->getAiScene());

    //Sp_Geometry cubeMesh = make_shared<Geometry>(cubeVertexPos, cubeVertexPos, cubeVertexUv, 6 * 2 * 3,
    //                                             nullptr, 0);
    //geometries.push_back(cubeMesh);

    renderingContext = new RenderingContext(this);
    loadChunk();
//
//    shared_ptr<ChunkGeneration> chunk0 = make_shared<ChunkGeneration>(this, 2, 0.5, 0, 0);
//
//    chunk0->generateWorld();
//    map.push_back(chunk0);
//    renderingContext->renderChunk(chunk0, renderMode);

    aiReleaseImport(loader->getAiScene());

//    Sp_Geometry cubeMesh = make_shared<Geometry>(cubeVertexPos, cubeVertexPos, cubeVertexUv, 6 * 2 * 3,
//                                                 nullptr, 0);
//    geometries.push_back(cubeMesh);


//    Sp_GameObject cube = make_shared<GameObject>(this, 1, 0);
//    objects.push_back(cube);
//    objectsToRender.push_back(cube);
//
//    for (int i = 0; i < geometries.size(); i++) {
//        geometries[i]->bind();
//    }
//    for (int i = 0; i < textures.size(); i++) {
//        textures[i]->bind();
//    }


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

    renderingContext->renderEntities();
    renderingContext->renderTerrain(map, renderMode);

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
                    if (isMouseCaptured) {
                        HitInfo hitInfo = raycastFromCamera();
                        if (hitInfo.hasHit) {
                            vec3 chunkCoords;
                            vec3 blockChunkCoords;

                            switch (curEvent.button.button) {
                                case SDL_BUTTON_LEFT:
                                    chunkCoords = vec3((int) hitInfo.blockHitPos.x / ChunkGeneration::size,
                                                       (int) hitInfo.blockHitPos.y / ChunkGeneration::size,
                                                       (int) hitInfo.blockHitPos.z / ChunkGeneration::size);
                                    chunkCoords -= hitInfo.faceHit * 0.5f;
                                    blockChunkCoords = map[0 * trunc(sqrt(nbChunk) + 0)]->worldToChunkCoords(
                                            hitInfo.blockHitPos - hitInfo.faceHit * 0.5f);
                                    if (blockChunkCoords != vec3(-1)) {
                                        /*printf("deleted %d %d %d\n", (int) blockChunkCoords.x, (int) blockChunkCoords.y,
                                               (int) blockChunkCoords.z);*/
                                        getChunk(0,0)->setCube(0, blockChunkCoords.x, blockChunkCoords.y, blockChunkCoords.z);

                                    }
                                    break;
                                case SDL_BUTTON_RIGHT:
                                    chunkCoords = vec3((int) hitInfo.blockHitPos.x / ChunkGeneration::size,
                                                       (int) hitInfo.blockHitPos.y / ChunkGeneration::size,
                                                       (int) hitInfo.blockHitPos.z / ChunkGeneration::size);
                                    chunkCoords += hitInfo.faceHit * 0.5f;
                                    blockChunkCoords = map[0 * trunc(sqrt(nbChunk) + 0)]->worldToChunkCoords(
                                            hitInfo.blockHitPos + hitInfo.faceHit * 0.5f);
                                    if (blockChunkCoords != vec3(-1)) {
                                        /*printf("placed %d %d %d\n", (int) blockChunkCoords.x, (int) blockChunkCoords.y,
                                               (int) blockChunkCoords.z);*/

                                        getChunk(0,0)->setCube(1, blockChunkCoords.x, blockChunkCoords.y, blockChunkCoords.z);

                                    }
                                    break;
                            }
                        }
                    } else {
                        isMouseCaptured = true;
                        SDL_ShowCursor(SDL_DISABLE);
                        SDL_SetWindowGrab(win, SDL_TRUE);
                        break;
                    }
                }
                break;
            case SDL_MOUSEMOTION:
                if (!io.WantCaptureMouse) {
                    if (isMouseCaptured) {
                        vec3 eulerAngles = mainCamera->transform->getEulerAngles();

                        if (abs(eulerAngles.z) < 90) {
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

                        // recentering cursor and avoiding reverse mouse motion
                        SDL_EventState(SDL_MOUSEMOTION, SDL_IGNORE);
                        SDL_WarpMouseInWindow(win, width / 2, height / 2);
                        SDL_EventState(SDL_MOUSEMOTION, SDL_ENABLE);
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
                        case SDLK_ESCAPE:
                            isMouseCaptured = false;
                            SDL_ShowCursor(SDL_ENABLE);
                            SDL_SetWindowGrab(win, SDL_FALSE);
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
    const char *error = SDL_GetError();
    if (error != NULL && *error != '\0') {
        printf("%s\n", error);
        SDL_ClearError();
    }
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

Sp_RenderedObject App::getObjectToRender(int i) {
    return Sp_RenderedObject(objectsToRender[i]);
}

int App::getObjectsToRenderCount() {
    return objectsToRender.size();
}

vector<Sp_RenderedObject>::iterator App::getObjectsToRenderBegin() {
    return objectsToRender.begin();
}

vector<Sp_RenderedObject>::iterator App::getObjectsToRenderEnd() {
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

    {
        ImGui::Begin("Perfs");
        ImGui::Text("Frame Time (ms) new : %d", deltaTime);
        ImGui::Text("FPS : %f", 1.0 / (float) deltaTime * 1000);
        ImGui::End();
    };
    {
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

        ImGui::InputInt("nb chunk : ", &nbChunk);
        ImGui::SameLine();
        if (ImGui::Button("Reload")) {
            loadChunk();
        }

        ImGui::Text("Opti : ");
        ImGui::SameLine();
        if (ImGui::Button("Opti")) {
            renderMode = RenderingContext::TerrainRenderMode::Opti;
        }
        ImGui::SameLine();
        if (ImGui::Button("SemiOpti")) {
            renderMode = RenderingContext::TerrainRenderMode::SemiOpti;
        }
        ImGui::SameLine();
        if (ImGui::Button("Brutus")) {
            renderMode = RenderingContext::TerrainRenderMode::Brut;
        }

        ImGui::End();
    };
    {
        ImGui::Begin("Info");

        vec3 cameraEulerAngles = mainCamera->transform->getEulerAngles();
        ImGui::Text("Camera euler angles : %f %f %f", cameraEulerAngles.x, cameraEulerAngles.y, cameraEulerAngles.z);

        vec3 cameraChunkPos = getChunk(0,0)->worldToChunkCoords(
                mainCamera->transform->getPosition());
        ImGui::Text("Camera chunk position : %f %f %f", cameraChunkPos.x, cameraChunkPos.y, cameraChunkPos.z);


        ImGui::End();
    }

    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
}

App::HitInfo App::raycastFromCamera() {
    HitInfo hitInfo;
    hitInfo.hasHit = false;
    vec3 rayDirection = mainCamera->transform->getForward();
    vec3 origin = mainCamera->transform->getPosition() - vec3(0.5f, 0.5f, 0.5f);
    int xDirection = ((rayDirection.x == 0) ? 0 : -rayDirection.x / abs(rayDirection.x));
    int yDirection = ((rayDirection.y == 0) ? 0 : -rayDirection.y / abs(rayDirection.y));
    int zDirection = ((rayDirection.z == 0) ? 0 : -rayDirection.z / abs(rayDirection.z));
    vec3 nextIntersectionX = (xDirection != 0) ? (origin + rayDirection *
                                                           ((xDirection == -1) ? (1 - (origin.x - trunc(origin.x))) : (
                                                                   origin.x - trunc(origin.x))) / rayDirection.x)
                                               : vec3(0);
    vec3 nextIntersectionY = (yDirection != 0) ? (origin + rayDirection *
                                                           ((yDirection == -1) ? (1 - (origin.y - trunc(origin.y))) : (
                                                                   origin.y - trunc(origin.y))) / rayDirection.y)
                                               : vec3(0);
    vec3 nextIntersectionZ = (zDirection != 0) ? (origin + rayDirection *
                                                           ((zDirection == -1) ? (1 - (origin.z - trunc(origin.y))) : (
                                                                   origin.z - trunc(origin.z))) / rayDirection.z)
                                               : vec3(0);
    vector<vec3 *> intersections;
    if (xDirection != 0) {
        intersections.push_back(&nextIntersectionX);
    } else {
        intersections.push_back(nullptr);
    }
    if (yDirection != 0) {
        intersections.push_back(&nextIntersectionY);
    } else {
        intersections.push_back(nullptr);
    }
    if (zDirection != 0) {
        intersections.push_back(&nextIntersectionZ);
    } else {
        intersections.push_back(nullptr);
    }
    vec3 *closestIntersection = nullptr;
    float closestDistance;
    float maxDistance = 6;
    do {
        closestIntersection = nullptr;
        closestDistance = maxDistance;
        int closestIntersectionIndex = -1;
        for (int i = 0; i < intersections.size(); i++) {
            vec3 *intersection = intersections[i];
            if (intersection != nullptr) {
                float distance = (origin - *intersection).length();
                if (distance < closestDistance) {
                    closestDistance = distance;
                    closestIntersection = intersection;
                    closestIntersectionIndex = i;
                }
            }
        }
        if (closestIntersection == nullptr) {
            closestDistance = -1;
        } else {
            if ((*closestIntersection).x < ChunkGeneration::size - 0.5f && (*closestIntersection).x >= -0.5 &&
                (*closestIntersection).y < ChunkGeneration::size - 0.5f && (*closestIntersection).y >= -0.5 &&
                (*closestIntersection).z < ChunkGeneration::size - 0.5f && (*closestIntersection).z >= -0.5) {
                vec3 chunkCoords = vec3((int) ((*closestIntersection).x + 0.5f) / ChunkGeneration::size,
                                        (int) ((*closestIntersection).y + 0.5f) / ChunkGeneration::size,
                                        (int) ((*closestIntersection).z + 0.5f) / ChunkGeneration::size);
                shared_ptr<ChunkGeneration> chunk = map[chunkCoords.z * trunc(sqrt(nbChunk) + chunkCoords.x)];
                vec3 intersectionChunkCoords = chunk->worldToChunkCoords(*closestIntersection + vec3(0.5f));
                if (chunk->getCubesInt()[chunk->getBlockIndex(intersectionChunkCoords.x, intersectionChunkCoords.y,
                                                              intersectionChunkCoords.z)] != 0) {
                    hitInfo.hasHit = true;
                    hitInfo.blockHitPos = *closestIntersection + vec3(0.5f);
                    switch (closestIntersectionIndex) {
                        case 0:
                            hitInfo.faceHit = vec3(-xDirection, 0, 0);
                            break;
                        case 1:
                            hitInfo.faceHit = vec3(0, -yDirection, 0);
                            break;
                        case 2:
                            hitInfo.faceHit = vec3(0, 0, -zDirection);
                            break;
                        default:
                            printf("shouldn't happen, the heck ?\n");
                            break;
                    }
                }
            }
        }
        switch (closestIntersectionIndex) {
            case 0:
                *closestIntersection += rayDirection * (xDirection / rayDirection.x);
                break;
            case 1:
                *closestIntersection += rayDirection * (yDirection / rayDirection.y);
                break;
            case 2:
                *closestIntersection += rayDirection * (zDirection / rayDirection.z);
                break;
            default:
                break;
        }
    } while (!hitInfo.hasHit && closestDistance <= maxDistance && closestDistance >= 0);
    return hitInfo;
}

void App::loadChunk() {
    mapReload = map;
    int sqrNbChunk = trunc(sqrt(nbChunk));
    shared_ptr<ChunkGeneration> Chunk;
    if (map.empty()) {
        for (int x = 0; x < sqrNbChunk; x++) {
            for (int z = 0; z < sqrNbChunk; z++) {
                printf("new chunk \n");
                Chunk = make_shared<ChunkGeneration>(this, 2, 0.5, x, z);

                Chunk->generateWorld();
                map.push_back(Chunk);

                printf("chunk %d %d\n", x, z);
            }
        }
    } else if (map.size() > nbChunk){
        map.clear();
        for(int x = 0; x < sqrNbChunk; x++){
            for(int z = 0; z < sqrNbChunk; z++){
                map.push_back(mapReload[z*sqrNbChunk + x]);
            }
        }
    } else {
        for (int z = mapReload.size()/2; z < sqrNbChunk; ++z) {
            for (int x = 0; x < sqrNbChunk; x++) {
                printf("new chunk \n");
                Chunk = make_shared<ChunkGeneration>(this, 2, 0.5, x, z);

                Chunk->generateWorld();
                map.push_back(Chunk);

                printf("chunk %d %d\n", x, 0);
            }
        }
        for (int x = mapReload.size()/2; x < sqrNbChunk; ++x) {
            for (int z = 0; z < sqrNbChunk; z++) {
                printf("new chunk \n");
                Chunk = make_shared<ChunkGeneration>(this, 2, 0.5, x, z);

                Chunk->generateWorld();
                map.push_back(Chunk);

                printf("chunk %d %d\n", 0, z);
            }
        }
    }


}

shared_ptr<ChunkGeneration> App::getChunk(int prmX, int prmY){
    if(!map.empty()) {
        return map[prmY * trunc(sqrt(nbChunk))];
    }
    return nullptr;
}

RenderingContext::TerrainRenderMode App::getRenderMode() {
    return renderMode;
}
