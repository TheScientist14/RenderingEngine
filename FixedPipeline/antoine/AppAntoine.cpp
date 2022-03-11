#include "AppAntoine.h"
#include <cstdio>
#ifdef _WIN32
#include <Windows.h>
#endif

#include <gl/GL.h>
#include "SDL.h"
#include "glm/glm.hpp"
#include "glm/ext.hpp"
#include "glm/gtc/matrix_transform.hpp"
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

    appRunning = true;
    auto prevTime = std::chrono::steady_clock::now();

    glm::vec3 vertex[] = {
            {-1,1,1}, {1,1,1}, {1,1,-1}, {-1,1,-1}, // top
            {-1,-1,1}, {1,-1,1}, {1,-1,-1}, {-1,-1,-1},// down
            {-1,1,1}, {1,1,1}, {1,1,-1}, {-1,1,-1}, // top
            {-1,-1,1}, {1,-1,1}, {1,-1,-1}, {-1,-1,-1}, // down
            {-1,1,1}, {1,1,1}, {1,1,-1}, {-1,1,-1}, // top
            {-1,-1,1}, {1,-1,1}, {1,-1,-1}, {-1,-1,-1} // down
    };
    glm::vec3 verticesNormal[]{
            {0,1,0}, {0,1,0}, {0,1,0}, {0,1,0}, // top
            {0,-1,0}, {0,-1,0}, {0,-1,0}, {0,-1,0},  // down
            {-1,0,0}, {1,0,0}, {1,0,0}, {-1,0,0},// left right right left
            {-1,0,0}, {1,0,0}, {1,0,0}, {-1,0,0},// left right right left
            {0,0,1}, {0,0,1}, {0,0,-1}, {0,0,-1}, // front back
            {0,0,1}, {0,0,1}, {0,0,-1}, {0,0,-1} // front back
    };

    int triangles[][3]{
            {0, 1, 2}, {0, 2, 3}, // top
            {4, 5, 6}, {4, 6, 7}, // down

            {9, 10, 13}, {10, 13, 14}, // right
            {8, 11, 12}, {11, 12, 15}, // left

            {18, 19, 22}, {19, 22, 23}, // back
            {16, 17, 20}, {17, 20, 21}  // front

    };

    int edges[][2]{
            {0, 1}, {1, 2}, {2, 3}, {3, 0}, // top edges
            {0, 4}, {1, 5}, {2, 6}, {3, 7}, // vertical edges
            {4, 5}, {5, 6}, {6, 7}, {7, 4}  // down edges
    };

    const int windowWidth = 1024;
    const int windowHeight = 768;

    while (appRunning) {
        HandleEvent();
        glViewport(0, 0, 1024, 768);
        glMatrixMode(GL_MODELVIEW);
        glLoadIdentity();
        //glTranslatef(0,0,-0.5);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);
        //glScaled(.5, .5, .5);
        glClearColor(0.0, 0.0, 0.0, 0.0);

        glMatrixMode(GL_PROJECTION);
        glm::mat4 projMat = glm::frustum(-((float)(windowWidth)/1000),(float)(windowWidth)/1000,-((float)(windowHeight)/1000),(float)(windowHeight)/1000,1.0f,100.0f);
        glLoadMatrixf(glm::value_ptr(projMat));

        const float radius = 5;

        //camera
        auto curTime = std::chrono::steady_clock::now();
        std::chrono::duration<float> fTime = curTime - prevTime;
        float camX = glm::sin(fTime.count()/2) * radius;
        float camZ = glm::cos(fTime.count()/2) * radius;

        glm::vec3 cameraPos = glm::vec3(camX, 2.0, camZ);
        glm::vec3 cameraTarget = glm::vec3(0.0, 0.0, 0.0);

        // Creation de la camera
        glm::mat4 view;
        view = glm::lookAt(    cameraPos, //Position de la camera
                               cameraTarget, //Cible à regarder
                               glm::vec3(0.0, 1.0, 0.0)); //position vertical

        glMatrixMode(GL_MODELVIEW);
        glLoadMatrixf(&view[0][0]);
        glEnable(GL_LIGHTING);
        glEnable(GL_LIGHT0);


        glEnableClientState(GL_NORMAL_ARRAY);
        glEnableClientState(GL_VERTEX_ARRAY);
        glEnableClientState(GL_COLOR_ARRAY);


        glVertexPointer(3, GL_FLOAT, sizeof(glm::vec3), vertex);
        glColorPointer(3, GL_FLOAT, sizeof(glm::vec3), vertex);
        glNormalPointer(GL_FLOAT, sizeof(glm::vec3), verticesNormal);
        glDrawElements(GL_TRIANGLES, 12*3, GL_UNSIGNED_INT, triangles);


        glDisableClientState(GL_COLOR_ARRAY);
        glColor3f(0.0, 0.0, 0.0);
        glDrawElements(GL_LINES, 12*2, GL_UNSIGNED_INT, edges);

        SDL_GL_SwapWindow(win);
    }
}
void AppAntoine::HandleEvent() {

    SDL_Event curEvent;
    while (SDL_PollEvent(&curEvent)) {
        switch (curEvent.type) {
            case SDL_QUIT:
                appRunning = false;
                return;
        }
    }
}