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
#include <glm/ext.hpp>
#include <SDL.h>
#include <chrono>
#include <type_traits>




void AppElvyn::Run() {

    SDL_Init(SDL_INIT_VIDEO); // init

    uint32_t windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE;


    // creation de window
    SDL_Window* win = SDL_CreateWindow("Moteur",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       1024, 768, windowFlags
    );

    //Create and make current context
    SDL_GLContext context = SDL_GL_CreateContext(win);
    SDL_GL_MakeCurrent(win, context);

    //variables
    const int row = 6*4;
    const int col = 3;
    cameraRotationX = 0;
    cameraRotationY = 0;
    //Time
    auto prevTime = std::chrono::steady_clock::now();

    //array of points
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

        //set viewport and clear
        glViewport(0, 0, 1024, 768);
        glClearDepth(1.0);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();

        glScalef(0.5f,0.5f,0.5f);

        //enable depth buffer
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);


        const float radius = 0.5;

        //camera
        auto curTime = std::chrono::steady_clock::now();
        std::chrono::duration<float> fTime = curTime - prevTime;
        float camX = glm::sin(fTime.count()/5) * radius;
        float camZ = glm::cos(fTime.count()/5) * radius;

        glm::vec3 cameraPos = glm::vec3(camX, 1.0, camZ);
        glm::vec3 cameraTarget = glm::vec3(0.0, 0.0, 0.0);

        // Creation de la camera
        glm::mat4 view;
        view = glm::lookAt(    cameraPos, //Position de la camera
                               cameraTarget, //Cible à regarder
                               glm::vec3(0.0, 1.0, 0.0)); //position vertical

        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(&view[0][0]);

        glMatrixMode(GL_PROJECTION);
        glm::mat4 projMat = glm::frustum(-1,1,-1,1,1,100);
        glLoadMatrixf(glm::value_ptr(projMat));



        // generate axis
        glBegin(GL_LINES);

        glColor4f(1.0,0.0,0.0,1.0);
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(10.0,0.0,0.0);

        glColor4f(0.0,1.0,0.0,1.0);
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(0.0,10.0,0.0);

        glColor4f(0.0,0.0,1.0,1.0);
        glVertex3f(0.0,0.0,0.0);
        glVertex3f(0.0,0.0,10.0);

        glEnd();

        glTranslatef(0.0f,0.0f,-2.0f);
        glScalef(0.5f,0.5f,0.5f);


        //generate cube
        glBegin(GL_QUADS);


        for (int i = 0; i < row; ++i) {
            glColor4f(cube_vertices[i][0], cube_vertices[i][1], cube_vertices[i][2], 1.0f);
            glVertex3f(cube_vertices[i][0],cube_vertices[i][1],cube_vertices[i][2]);
        }


        // Bottom Right Of The Quad (Right)
        glEnd();                        // Done Drawing The Quad


        //generate cube lines
        glBegin(GL_LINES);
        glColor4f(0.0f, 0.0f, 0.0f,0.0f);

        for (int i = 0; i < row; i++) {
            glVertex3f(cube_vertices[i][0],cube_vertices[i][1],cube_vertices[i][2]);
            glVertex3f(cube_vertices[i+1][0],cube_vertices[i+1][1],cube_vertices[i+1][2]);
            i++;
            glVertex3f(cube_vertices[i][0],cube_vertices[i][1],cube_vertices[i][2]);
            glVertex3f(cube_vertices[i+1][0],cube_vertices[i+1][1],cube_vertices[i+1][2]);
            i++;
            glVertex3f(cube_vertices[i][0],cube_vertices[i][1],cube_vertices[i][2]);
            glVertex3f(cube_vertices[i+1][0],cube_vertices[i+1][1],cube_vertices[i+1][2]);
            i++;
            glVertex3f(cube_vertices[i][0],cube_vertices[i][1],cube_vertices[i][2]);
            glVertex3f(cube_vertices[i-3][0],cube_vertices[i-3][1],cube_vertices[i-3][2]);
        }


        glEnd();

        SDL_GL_SwapWindow(win);

    }

    printf("Done");
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