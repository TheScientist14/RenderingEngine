#include <iostream>

#include "SDL.h"
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "ScriptablePipeline/App.h"

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


    BaseApp* app = new App();
    app->run();

    return 0;
}