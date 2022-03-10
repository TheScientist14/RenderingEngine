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

    uint32_t windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN;

    const int windowWidth = 1024;
    const int windowHeight = 768;
    // creation de window
    SDL_Window* win = SDL_CreateWindow("Moteur",
                                       SDL_WINDOWPOS_UNDEFINED,
                                       SDL_WINDOWPOS_UNDEFINED,
                                       windowWidth, windowHeight, windowFlags
    );

    SDL_RaiseWindow(win);

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
    int triangles[][3]{
            {0, 1, 2}, {0, 2, 3}, // top
            {0, 1, 4}, {1, 4, 5}, // front
            {0, 3, 4}, {3, 4, 7}, // left
            {4, 5, 6}, {4, 6, 7}, // down
            {2, 3, 6}, {3, 6, 7}, // back
            {1, 2, 5}, {2, 5, 6}  // right
    };

    int edges[][2]{
            {0, 1}, {1, 2}, {2, 3}, {3, 0}, // top edges
            {0, 4}, {1, 5}, {2, 6}, {3, 7}, // vertical edges
            {4, 5}, {5, 6}, {6, 7}, {7, 4}  // down edges
    };

    //Pointers
    glm::vec3 vertices[]{
            {-1,1,1}, {1,1,1}, {1,1,-1}, {-1,1,-1}, // top
            {-1,-1,1}, {1,-1,1}, {1,-1,-1}, {-1,-1,-1}  // down
    };

    while (appRunning) {
        HandleEvent();

        //set viewport and clear
        glViewport(0, 0, windowWidth, windowHeight);
        glClearDepth(1.0);
        glClearColor(0.0, 0.0, 0.0, 0.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glLoadIdentity();

        glScalef(0.5f,0.5f,0.5f);

        //enable depth buffer
        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);

        glMatrixMode(GL_PROJECTION);
        glm::mat4 projMat = glm::frustum(-((float)(windowWidth)/2000),(float)(windowWidth)/2000,-((float)(windowHeight)/2000),(float)(windowHeight)/2000,1.0f,100.0f);
        glLoadMatrixf(glm::value_ptr(projMat));

        const float radius = 5;

        //camera
        auto curTime = std::chrono::steady_clock::now();
        std::chrono::duration<float> fTime = curTime - prevTime;
        float camX = glm::sin(fTime.count()/5) * radius;
        float camZ = glm::cos(fTime.count()/5) * radius;

        glm::vec3 cameraPos = glm::vec3(camX, 2.0, camZ);
        glm::vec3 cameraTarget = glm::vec3(0.0, 0.0, 0.0);

        // Creation de la camera
        glm::mat4 view;
        view = glm::lookAt(    cameraPos, //Position de la camera
                               cameraTarget, //Cible à regarder
                               glm::vec3(0.0, 1.0, 0.0)); //position vertical

        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(&view[0][0]);

//        glEnable(GL_LIGHTING);
//        glEnable(GL_LIGHT0);
//        glLightfv(GL_LIGHT0,GL_LINEAR_ATTENUATION,)

        glEnableClientState(GL_COLOR_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);


        glVertexPointer(3,GL_FLOAT,sizeof(glm::vec3),vertices);
        glColorPointer(3,GL_FLOAT, sizeof(glm::vec3), vertices);
        glDrawElements(GL_TRIANGLES,12*3,GL_UNSIGNED_INT,triangles);

        glDisableClientState(GL_COLOR_ARRAY);


        glColor3f(0.0,0.0,0.0);
        glDrawElements(GL_LINES,12*2,GL_UNSIGNED_INT,edges);


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