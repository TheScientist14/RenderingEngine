#include "AppTom.h"

#include <cstdio>

#ifdef _WIN32

#include <windows.h>

#endif

#include <gl/GL.h>
#include <SDL.h>

#include <type_traits>

#include <glm/vec3.hpp> // glm::vec3
#include <glm/vec4.hpp> // glm::vec4
#include <glm/mat4x4.hpp> // glm::mat4
#include <glm/ext/matrix_transform.hpp> // glm::translate, glm::rotate, glm::scale
#include <glm/ext/matrix_clip_space.hpp> // glm::perspective
#include <glm/ext/scalar_constants.hpp> // glm::pi

glm::mat4 camera(float Translate, glm::vec2 const& Rotate)
{
    glm::mat4 Projection = glm::perspective(glm::pi<float>() * 0.25f, 4.0f / 3.0f, 0.1f, 100.f);
    glm::mat4 View = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, -Translate));
    View = glm::rotate(View, Rotate.y, glm::vec3(-1.0f, 0.0f, 0.0f));
    View = glm::rotate(View, Rotate.x, glm::vec3(0.0f, 1.0f, 0.0f));
    glm::mat4 Model = glm::scale(glm::mat4(1.0f), glm::vec3(0.5f));
    return Projection * View * Model;
}

void AppTom::run() {
    SDL_Init(SDL_INIT_VIDEO);

    uint32_t windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;

    // SDL_GL_SetAttribute(SDL_GL_CONTEXT_FLAGS, SDL_GL_CONTEXT_DEBUG_

    SDL_Window *win = SDL_CreateWindow("Moteur",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       1024, 768, windowFlags
    );

    SDL_GLContext context = SDL_GL_CreateContext(win);
    SDL_GL_MakeCurrent(win, context);

    SDL_ShowCursor(0);
    //SDL_SetWindowGrab(win, SDL_TRUE);

    float cube_vertices[] = {
            1, 1, 1, 1, -1, 1, -1, -1, 1, -1, 1, 1,
            1, 1, 1, 1, -1, 1, 1, -1, -1, 1, 1, -1,
            1, 1, 1, 1, 1, -1, -1, 1, -1, -1, 1, 1,
            1, 1, -1, 1, -1, -1, -1, -1, -1, -1, 1, -1,
            -1, 1, 1, -1, -1, 1, -1, -1, -1, -1, 1, -1,
            1, -1, 1, 1, -1, -1, -1, -1, -1, -1, -1, 1
    };

    appRunning = true;
    cameraRotationX = 0;
    cameraRotationY = 0;
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    glFrustum(0, 1, 0, 1, 1, 5);

    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    float radius = 2;

    while (appRunning) {
        handle_events();
        glViewport(0, 0, 1024, 768);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);

        glLoadIdentity();
        glScalef(0.5f, 0.5f, 0.5f);
//        glRotatef(cameraRotationX, 0, 1, 0);
//        glRotatef(cameraRotationY, 1, 0, 0);
        glm::vec3 cameraPos = glm::vec3(1, 1, 1);
        glm::vec3 cameraTarget = glm::vec3(0.0, 0.0, 0.0);
        glm::mat4 camMatrix = glm::lookAt(cameraPos, cameraTarget, glm::vec3(0, 1, 0));
        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(&camMatrix[0][0]);

        for (int i = 0; i < std::extent<decltype(cube_vertices)>::value; i += 4 * 3) {
            glBegin(GL_QUADS);
            glColor4f((cube_vertices[i] + cube_vertices[i+3] + cube_vertices[i + 6] + cube_vertices[i + 9] + 4) / 8, (cube_vertices[i+1] + cube_vertices[i+4] + cube_vertices[i + 7] + cube_vertices[i + 10] + 4) / 8, (cube_vertices[i+2] + cube_vertices[i+5] + cube_vertices[i + 8] + cube_vertices[i + 11] + 4) / 8, 1.0);

            for (int j = 0; j < 4 * 3; j += 3) {
                glVertex3f(cube_vertices[i + j], cube_vertices[i + j + 1], cube_vertices[i + j + 2]);
            }
            glEnd();
        }

//        glBegin(GL_QUADS);
//        glColor4f( 1.0f, 1.0f,-1.0f, 1.0f);
//        glVertex3f( 1.0f, 1.0f,-1.0f);          // Top Right Of The Quad (Top)
//        glVertex3f(-1.0f, 1.0f,-1.0f);          // Top Left Of The Quad (Top)
//        glVertex3f(-1.0f, 1.0f, 1.0f);          // Bottom Left Of The Quad (Top)
//        glVertex3f( 1.0f, 1.0f, 1.0f);
//        glEnd();

        SDL_GL_SwapWindow(win);
    }
}

void AppTom::handle_events() {
    SDL_Event curEvent;
    while (SDL_PollEvent(&curEvent)) {
        switch (curEvent.type) {
            case SDL_QUIT:
                appRunning = false;
                return;
                break;
            case SDL_MOUSEBUTTONDOWN:
                isDragging = true;
                break;
            case SDL_MOUSEBUTTONUP:
                isDragging = false;
                break;
            case SDL_MOUSEMOTION:
                if(isDragging){
                    cameraRotationX -= curEvent.motion.xrel * 0.5f;
                    cameraRotationY -= curEvent.motion.yrel * 0.5f;
                }
        }
    }
}