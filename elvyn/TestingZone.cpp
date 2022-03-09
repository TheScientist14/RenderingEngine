//
// Created by ewakeford on 09/03/2022.
//

#include "TestingZone.h"

#include <cstdio>
#ifdef _WIN32
#include <windows.h>
#endif

#include <gl/GL.h>
#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi
#include <SDL.h>
#include <chrono>
#include <type_traits>


#include "TestingZone.h"

void TestingZone::Run() {

    SDL_Init(SDL_INIT_VIDEO);

    uint32_t windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

    auto prevTime = std::chrono::steady_clock::now();

    bool appRunning = true;

    SDL_Window* win = SDL_CreateWindow("Moteur",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       1024, 768, windowFlags
    );

    while (appRunning)
    {
        SDL_Event curEvent;
        while (SDL_PollEvent(&curEvent))
        {
        }

        glViewport(0, 0, 1024, 768);
        glClearDepth(1.0);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();

        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);


        glBegin(GL_LINES);

        glColor4f(1.0,0.0,0.0,1.0);
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(1.0,0.0,0.0);

        glColor4f(0.0,1.0,0.0,1.0);
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(0.0,1.0,0.0);

        glColor4f(1.0,0.0,1.0,1.0);
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(0.0,0.0,1.0);

        glEnd();





        SDL_GL_SwapWindow(win);
    }
}
