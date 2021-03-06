//
// Created by tsaury on 11/03/2022.
//

#include "BaseApp.h"

#include <cstdio>
#include "SDL.h"
#include <GL/glew.h>
#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "backends/imgui_impl_opengl3.h"
#include "glm/glm.hpp"

void BaseApp::run(){
    win = init_window();
    gl_init();
    app_running = true;
    while(app_running){
        Uint64 nextTime = SDL_GetTicks64();
        deltaTime = nextTime - curTime;
        handle_events();
        main_loop();
        SDL_GL_SwapWindow(win);
        curTime = nextTime;
    }

    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplSDL2_Shutdown();
    ImGui::DestroyContext();

    clean();
}

void GLAPIENTRY glDebugOutput(GLenum source, GLenum type, GLuint id,
GLenum severity, GLsizei length, const GLchar* message, const void* userParam)
{
    if(type == GL_DEBUG_TYPE_ERROR) {
        printf(message);
    }
}

SDL_Window* BaseApp::init_window() {

    SDL_Init(SDL_INIT_VIDEO);

    uint32_t windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN;

    win = SDL_CreateWindow("Moteur",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       width,height, windowFlags
    );

    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 3);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_MAJOR_VERSION, 2);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_PROFILE_MASK, SDL_GL_CONTEXT_PROFILE_CORE);
    SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_FLAG);

    SDL_GLContext context = SDL_GL_CreateContext(win);
    SDL_GL_MakeCurrent(win, context);

    SDL_ShowCursor(SDL_DISABLE);
    SDL_SetWindowGrab(win, SDL_TRUE);


    curTime = SDL_GetTicks64();

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    //io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls

    ImGui_ImplSDL2_InitForOpenGL(win, context);
    ImGui_ImplOpenGL3_Init();

    ImGui::StyleColorsDark();


    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));
    }

    glDebugMessageCallback(&glDebugOutput, nullptr);
    glDebugMessageControl(
            GL_DEBUG_SOURCE_API, GL_DEBUG_TYPE_ERROR, GL_DONT_CARE, 0, NULL, GL_TRUE);
    return win;
}

void BaseApp::handle_events() {
    SDL_Event curEvent;
    while (SDL_PollEvent(&curEvent)) {
        switch (curEvent.type) {
            case SDL_QUIT:
                app_running = false;
                return;
        }
    }
}