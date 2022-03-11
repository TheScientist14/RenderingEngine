//
// Created by tsaury on 11/03/2022.
//

#include "BaseApp.h"

#include "SDL.h"
#include <GL/glew.h>
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include <gl/GL.h>

void BaseApp::run(){
    win = init_window();
    gl_init();
    app_running = true;
    while(app_running){
        handle_events();
        main_loop();
        SDL_GL_SwapWindow(win);
    }
    clean();
}

SDL_Window* BaseApp::init_window() {

    SDL_Init(SDL_INIT_VIDEO);

    uint32_t windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN;

    win = SDL_CreateWindow("Moteur",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       width,height, windowFlags
    );

    SDL_GLContext context = SDL_GL_CreateContext(win);
    SDL_GL_MakeCurrent(win, context);

    SDL_ShowCursor(0);
    //SDL_SetWindowGrab(win, SDL_TRUE);

    GLenum err = glewInit();
    if (GLEW_OK != err)
    {
        /* Problem: glewInit failed, something is seriously wrong. */
        fprintf(stderr, "Error: %s\n", glewGetErrorString(err));

    }

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