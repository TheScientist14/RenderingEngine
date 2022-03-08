#include "AppAntoine.h"
#include <cstdio>
#ifdef _WIN32
#include <windows.h>
#endif

#include <gl/GL.h>
#include <SDL.h>
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <chrono>

void AppAntoine::run() {

    SDL_Init(SDL_INIT_VIDEO);

    uint32_t windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_

    SDL_Window* win = SDL_CreateWindow("Moteur",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       1024, 768, windowFlags
    );

    SDL_GLContext context = SDL_GL_CreateContext(win);
    SDL_GL_MakeCurrent(win, context);

    float rquad = 0;
    bool appRunning = true;


    while (appRunning) {
        SDL_Event curEvent;
        while (SDL_PollEvent(&curEvent)) {

        }
        glViewport(0, 0, 1024, 768);
        glLoadIdentity();
        glScaled(.5, .5, .5);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT);
        glRotatef(rquad, 1.0f, 1.0f, 1.0f);

        glColor4f(0.0, 1.0, 0.0, 1.0);
        glBegin(GL_QUADS);
        glVertex3f(-1, 1, 1.0);
        glVertex3f(1, 1, 1.0);
        glVertex3f(1, -1, 1.0);
        glVertex3f(-1, -1, 1.0);

        glColor4f(0.0, 1.0, 1.0, 1.0);
        glVertex3f(-1, -1, -1);
        glVertex3f(1, -1, -1);
        glVertex3f(1, -1, 1);
        glVertex3f(-1, -1, 1);

        glColor4f(1.0, 0.0, 0.0, 1.0);
        glVertex3f(1, 1, 1);
        glVertex3f(1, 1, -1.0);
        glVertex3f(1, -1, -1);
        glVertex3f(1, -1, 1);

        rquad-=0.15f;
        glEnd();

        SDL_GL_SwapWindow(win);
    }
}
