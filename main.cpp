#include <iostream>
#include "ScriptablePipeline/AppTriangle.h"
#include "ScriptablePipeline/AppCube.h"

#include "SDL.h"
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "imgui.h"
#include "backends/imgui_impl_sdl.h"
#include "backends/imgui_impl_opengl2.h"

int main(int argc, char *argv[]) {

//    SDL_Init(SDL_INIT_VIDEO);
//
//
//    uint32_t windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN;
//
//    SDL_Window* win = SDL_CreateWindow("Moteur",
//                           SDL_WINDOWPOS_UNDEFINED,
//                           SDL_WINDOWPOS_UNDEFINED,
//                           1024,768, windowFlags
//    );
//
//    SDL_GLContext context = SDL_GL_CreateContext(win);
//    SDL_GL_MakeCurrent(win, context);
//
//    glewInit();
//
//    IMGUI_CHECKVERSION();
//    ImGui::CreateContext();
//    ImGuiIO& io = ImGui::GetIO();
//    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;  // Enable Keyboard Controls
//
//    ImGui_ImplSDL2_InitForOpenGL(win, context);
//    ImGui_ImplOpenGL2_Init();
//
//    ImGui::StyleColorsDark();

    BaseApp* app = new AppCube;
    app->run();

    return 0;
}