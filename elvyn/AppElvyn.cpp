//
// Created by ewakeford on 08/03/2022.
//

#include "AppElvyn.h"

#include <cstdio>
#ifdef _WIN32
#include <windows.h>
#endif

#include <gl/GL.h>
#include <glm/glm.hpp>
#include <SDL.h>
#include <chrono>
#include <type_traits>




void AppElvyn::Run() {

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

    float rtri = 0;

    const int row = 6*4;
    const int col = 3;

    float cube_vertices[row][col] = {
            1, 1, 1, 1, -1, 1, -1, -1, 1, -1, 1, 1,
            1, 1, 1, 1, -1, 1, 1, -1, -1, 1, 1, -1,
            1, 1, 1, 1, 1, -1, -1, 1, -1, -1, 1, 1,
            1, 1, -1, 1, -1, -1, -1, -1, -1, -1, 1, -1,
            -1, 1, 1, -1, -1, 1, -1, -1, -1, -1, 1, -1,
            1, -1, 1, 1, -1, -1, -1, -1, -1, -1, -1, 1
    };

    while (appRunning) {
        HandleEvent();

        glViewport(0, 0, 1024, 768);
        glClearDepth(1.0);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();

        glScalef(0.5f,0.5f,0.5f);
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);
        //glTranslatef(0.0f,0.0f,1.0f);              // Move Right And Into The Screen

        glRotatef(cameraRotationX, 0, 1, 0);
        glRotatef(cameraRotationY, 1, 0, 0);            // Rotate The Cube On X, Y & Z

        //glColor4f(1.0, 1.0, 1.0, 1.0);

        glBegin(GL_QUADS);


        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; j+=3) {

                glColor4f(cube_vertices[i][j], cube_vertices[i][j+1], cube_vertices[i][j+2], 1.0f);
                glVertex3f(cube_vertices[i][j],cube_vertices[i][j+1],cube_vertices[i][j+2]);


            }
        }


                  // Bottom Right Of The Quad (Right)
        glEnd();                        // Done Drawing The Quad
        glBegin(GL_LINES);

        for (int i = 0; i < row; ++i) {
            for (int j = 0; j < col; j+=3) {

                glColor4f(0.0f, 0.0f, 0.0f,0.0f);
                glVertex3f(cube_vertices[i][j],cube_vertices[i][j+1],cube_vertices[i][j+2]);
            }
        }
        glEnd();

        //rtri+=0.2f;                     // Increase The Rotation Variable For The Triangle
        // Decrease The Rotation Variable For The Quad

        SDL_GL_SwapWindow(win);

    }

    printf("Hello world");
}

void AppElvyn::HandleEvent() {

    SDL_Event curEvent;
    while (SDL_PollEvent(&curEvent)) {
        switch (curEvent.type) {
            case SDL_QUIT:
                appRunning = false;
                return;
            case SDL_MOUSEMOTION:
                cameraRotationX -= curEvent.motion.xrel * 0.5f;
                cameraRotationY -= curEvent.motion.yrel * 0.5f;
        }
    }


}
