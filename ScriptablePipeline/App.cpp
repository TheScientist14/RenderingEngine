//
// Created by tsaury on 11/03/2022.
//

#include "App.h"

#include <string>

#include "SDL.h"
#include <GL/glew.h>
#include "../helper/stb_image.h"
#include "../Shaders/loadShader.h"
#include "EngineObjects/GameObject.h"
#include <imgui.h>
#include "imgui_impl_sdl.h"
#include "imgui_impl_opengl3.h"

using namespace std;

void App::gl_init(){

#pragma region cube_vertex
    static const float cubeVertexPos[] = {
            -1.0f,-1.0f,-1.0f, // triangle 1 : begin
            -1.0f,-1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f, // triangle 1 : end
            1.0f, 1.0f,-1.0f, // triangle 2 : begin
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f, // triangle 2 : end
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            -1.0f,-1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            -1.0f,-1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f,-1.0f,
            1.0f,-1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f,-1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f,-1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f, 1.0f, 1.0f,
            -1.0f, 1.0f, 1.0f,
            1.0f,-1.0f, 1.0f
    };
#pragma endregion cube_vertex

#pragma region UV_buffer
    // Two UV coordinatesfor each vertex. They were created with Blender. You'll learn shortly how to do this yourself.
    static const GLfloat cubeVertexUv[] = {
            0.000059f, 1.0f-0.000004f,
            0.000103f, 1.0f-0.336048f,
            0.335973f, 1.0f-0.335903f,
            1.000023f, 1.0f-0.000013f,
            0.667979f, 1.0f-0.335851f,
            0.999958f, 1.0f-0.336064f,
            0.667979f, 1.0f-0.335851f,
            0.336024f, 1.0f-0.671877f,
            0.667969f, 1.0f-0.671889f,
            1.000023f, 1.0f-0.000013f,
            0.668104f, 1.0f-0.000013f,
            0.667979f, 1.0f-0.335851f,
            0.000059f, 1.0f-0.000004f,
            0.335973f, 1.0f-0.335903f,
            0.336098f, 1.0f-0.000071f,
            0.667979f, 1.0f-0.335851f,
            0.335973f, 1.0f-0.335903f,
            0.336024f, 1.0f-0.671877f,
            1.000004f, 1.0f-0.671847f,
            0.999958f, 1.0f-0.336064f,
            0.667979f, 1.0f-0.335851f,
            0.668104f, 1.0f-0.000013f,
            0.335973f, 1.0f-0.335903f,
            0.667979f, 1.0f-0.335851f,
            0.335973f, 1.0f-0.335903f,
            0.668104f, 1.0f-0.000013f,
            0.336098f, 1.0f-0.000071f,
            0.000103f, 1.0f-0.336048f,
            0.000004f, 1.0f-0.671870f,
            0.336024f, 1.0f-0.671877f,
            0.000103f, 1.0f-0.336048f,
            0.336024f, 1.0f-0.671877f,
            0.335973f, 1.0f-0.335903f,
            0.667969f, 1.0f-0.671889f,
            1.000004f, 1.0f-0.671847f,
            0.667979f, 1.0f-0.335851f
    };

#pragma endregion UV_buffer



// Draw some widgets



    shared_ptr<Geometry> cubeMesh = make_shared<Geometry>(cubeVertexPos, cubeVertexPos, cubeVertexUv, 6*2*3, nullptr, 0);
    geometries.push_back(cubeMesh);

    shared_ptr<Texture> cube_texture = make_shared<Texture>("../Images/uvtemplate.bmp");
    textures.push_back(cube_texture);

    for(int i = 0; i < geometries.size(); i++){
        geometries[i]->bind();
    }
    for(int i = 0; i < textures.size(); i++){
        textures[i]->bind();
    }

//    shared_ptr<EngineObject> cube = make_shared<GameObject>(this, 0, 0);
//    objects.push_back(cube);
//    cube->transform.rotation = vec3(30, 45, 0);
//    shared_ptr<EngineObject> cube2 = make_shared<GameObject>(this, 0, 0);
//    objects.push_back(cube2);
//    cube2->transform.position = vec3(2, 0, 0);
//    cube2->transform.rotation = vec3(30, 45, 0);

    int n = 10;
    float gap = 0.5;
    float cubeSize = 2;
    vector<int> cubesIndex;
    for(int i = 0; i < n; i++){
        shared_ptr<EngineObject> cube = make_shared<GameObject>(this, 0, 0);
        cube->transform.rotation = vec3(0, 10 * i, 0);
        cube->transform.position = vec3(-i * (cubeSize + gap), 0, -i * (cubeSize + gap));
        cubesIndex.push_back(objects.size());
        objects.push_back(cube);
        for(int j = 0; j < i; j++){
            shared_ptr<EngineObject> cube1 = make_shared<GameObject>(this, 0, 0);
            shared_ptr<EngineObject> cube2 = make_shared<GameObject>(this, 0, 0);
            cube1->transform.rotation = vec3(0, i * 10, 0);
            cube1->transform.position = vec3(-j * (cubeSize + gap), 0, -i * (cubeSize + gap));
            cube2->transform.rotation = vec3(0, i * 10, 0);
            cube2->transform.position = vec3(-i * (cubeSize + gap), 0, -j * (cubeSize + gap));
            cubesIndex.push_back(objects.size());
            objects.push_back(cube1);
            cubesIndex.push_back(objects.size());
            objects.push_back(cube2);
        }
    }

    mainCamera = make_shared<Camera>(this);
    mainCamera->transform.position += vec3(0, 5, 0);

    shaderID = loadShader::LoadShaders( "/Shaders/ColoredCube.vertexshader" , "/Shaders/ColoredCube.fragmentshader" );
    glUseProgram(shaderID);
}

void App::main_loop() {
    mainCamera->update(deltaTime);
//Render Loop
    ImGui_ImplOpenGL3_NewFrame();
    ImGui_ImplSDL2_NewFrame(win);

    ImGui::NewFrame();

    ImGui::Begin("Perfs");
    ImGui::LabelText("Frame Time (ms) : ", "%f", deltaTime * 1e-3);
    ImGui::LabelText("FPS : ", "%f", 1.0 / deltaTime);
    ImGui::End();


    ImGui::Render();
    ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());


    for(int i = 0; i < objects.size(); i++){
        objects[i]->update(deltaTime);
    }
}

void App::handle_events() {
    SDL_Event curEvent;
    while (SDL_PollEvent(&curEvent)) {
        switch (curEvent.type) {
            case SDL_QUIT:
                app_running = false;
                return;
            case SDL_MOUSEBUTTONDOWN:
                isDragging = true;
                break;
            case SDL_MOUSEBUTTONUP:
                isDragging = false;
                break;
            case SDL_MOUSEMOTION:
                if(isDragging){
                    mainCamera->transform.rotation[1] -= curEvent.motion.xrel * 0.5f;
                    mainCamera->transform.rotation[0] -= curEvent.motion.yrel * 0.5f;
                }
            case SDL_KEYDOWN:
                float cameraSpeed = 0.08f;
                if(curEvent.key.keysym.sym == SDLK_LEFT || curEvent.key.keysym.sym == SDLK_q){
                    mainCamera->transform.position[0] -= cameraSpeed;
                }
                if(curEvent.key.keysym.sym == SDLK_RIGHT || curEvent.key.keysym.sym == SDLK_d){
                    mainCamera->transform.position[0] += cameraSpeed;
                }
                if(curEvent.key.keysym.sym == SDLK_UP || curEvent.key.keysym.sym == SDLK_z){
                    mainCamera->transform.position[2] -= cameraSpeed;
                }
                if(curEvent.key.keysym.sym == SDLK_DOWN || curEvent.key.keysym.sym == SDLK_s){
                    mainCamera->transform.position[2] += cameraSpeed;
                }
                if(curEvent.key.keysym.sym == SDLK_SPACE){
                    if(curEvent.key.keysym.mod == KMOD_SHIFT || curEvent.key.keysym.mod == KMOD_CTRL){
                        mainCamera->transform.position[1] -= cameraSpeed;
                    }
                    else{
                        mainCamera->transform.position[1] += cameraSpeed;
                    }
                }
        }
    }
}

void App::clean(){
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