#include "AppTom.h"

#include <cstdio>

#ifdef _WIN32

#include <windows.h>

#endif

#include <gl/GL.h>
#include <SDL.h>

#include <type_traits>
#include <chrono>

#include <glm/glm.hpp>
#include <glm/ext.hpp>

float cube_vertices[] = {
        1, 1, 1, 1, -1, 1, -1, -1, 1, -1, 1, 1,
        1, 1, 1, 1, -1, 1, 1, -1, -1, 1, 1, -1,
        1, 1, 1, 1, 1, -1, -1, 1, -1, -1, 1, 1,
        1, 1, -1, 1, -1, -1, -1, -1, -1, -1, 1, -1,
        -1, 1, 1, -1, -1, 1, -1, -1, -1, -1, 1, -1,
        1, -1, 1, 1, -1, -1, -1, -1, -1, -1, -1, 1
};

glm::vec3 vertices[]{
        {0,1,1}, {1,1,1}, {1,1,0}, {0,1,0}, // top
        {0,0,1}, {1,0,1}, {1,0,0}, {0,0,0}  // down
};
glm::vec3 colors[8];

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

void drawCube(){
    for (int i = 0; i < std::extent<decltype(cube_vertices)>::value; i += 4 * 3) {
        glBegin(GL_QUADS);
        glColor4f((cube_vertices[i] + cube_vertices[i+3] + cube_vertices[i + 6] + cube_vertices[i + 9] + 4) / 8, (cube_vertices[i+1] + cube_vertices[i+4] + cube_vertices[i + 7] + cube_vertices[i + 10] + 4) / 8, (cube_vertices[i+2] + cube_vertices[i+5] + cube_vertices[i + 8] + cube_vertices[i + 11] + 4) / 8, 1.0);

        for (int j = 0; j < 4 * 3; j += 3) {
            glVertex3f(cube_vertices[i + j], cube_vertices[i + j + 1], cube_vertices[i + j + 2]);
        }
        glEnd();
    }
}

void computeColor(glm::vec3 vertices[], glm::vec3 colors[], int nV) {
    glm::vec3 minCoord = {0,0,0};
    glm::vec3 maxCoord = {0,0,0};
    for(int i = 0; i < nV; i++){
        for(int j = 0; j < 3; j++){
            if(vertices[i][j] < minCoord[j]){
                minCoord[j] = vertices[i][j];
            }
            if(vertices[i][j] > maxCoord[j]){
                maxCoord[j] = vertices[i][j];
            }
        }
    } // getting rect bounds
    //for (int i = 0; i < nT; i++) {
    /*(vertices[triangles[i][0]][0] + vertices[triangles[i][1]][0] + vertices[triangles[i][2]][0] - 3 * minCoord[0]) / (3 * (maxCoord[0] - minCoord[0])),
        (vertices[triangles[i][0]][1] + vertices[triangles[i][1]][1] + vertices[triangles[i][2]][1] - 3 * minCoord[1]) / (3 * (maxCoord[1] - minCoord[1])),
        (vertices[triangles[i][0]][2] + vertices[triangles[i][1]][2] + vertices[triangles[i][2]][2] - 3 * minCoord[2]) / (3 * (maxCoord[2] - minCoord[2]))*/
}

void drawGeometry(glm::vec3 vertices[], glm::vec3 colors[], int nV, int triangles[][3], int nT, int edges[][2], int nE, bool drawnLines) {
    glVertexPointer(3, GL_FLOAT, 0, vertices);
    glColorPointer(3, GL_FLOAT, 0, colors);

    glDrawElements(GL_TRIANGLES, nT * 3, GL_UNSIGNED_INT, triangles);

    if(drawnLines){
        glDisableClientState(GL_COLOR_ARRAY);
        glColor3f(0, 0, 0);
        glDrawElements(GL_LINES, nE*2, GL_UNSIGNED_INT, edges);
        glEnableClientState(GL_COLOR_ARRAY);
    }
}

// nV = nSlices * nSlices / 2 + 2
void computeSphereVertices(glm::vec3 vertices[], glm::vec3 triangles[], int nSlices) {
    vertices[0] = glm::vec3(0, 1, 0);
    for (float i = 1; i < nSlices / 2; i++) {
        float radius = glm::cos(glm::pi<float>() * i / nSlices);
        for (float j = 0; j < nSlices; j++) {
            vertices[(int)(i-1) * nSlices + (int)j + 1] = glm::vec3(radius * glm::cos(j), glm::sin(glm::pi<float>() * i / nSlices), radius * glm::sin(j));
        }
    }
    vertices[nSlices * (nSlices-1) / 2 + 1] = glm::vec3(0, -1, 0);
}

glm::vec3 sphereVertices[16*15+2];

SDL_Window* init_window() {
    SDL_Init(SDL_INIT_VIDEO);

    uint32_t windowFlags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_SHOWN;

    SDL_Window* win = SDL_CreateWindow("Moteur",
        SDL_WINDOWPOS_UNDEFINED,
        SDL_WINDOWPOS_UNDEFINED,
        1024, 768, windowFlags
    );

    SDL_GLContext context = SDL_GL_CreateContext(win);
    SDL_GL_MakeCurrent(win, context);

    SDL_ShowCursor(0);
    //SDL_SetWindowGrab(win, SDL_TRUE);

    glEnableClientState(GL_VERTEX_ARRAY);
    glEnableClientState(GL_COLOR_ARRAY);

    return win;
}

void AppTom::run() {

    SDL_Window *win = init_window();

    appRunning = true;
    cameraPos = {0,0,10};
    cameraRot = {0,0,0};
    std::chrono::time_point<std::chrono::steady_clock> prevTime = std::chrono::steady_clock::now();

    computeSphereVertices(sphereVertices, nullptr, 16);

    while (appRunning) {
        handle_events();
        glViewport(0, 0, 1024, 768);
        glClearColor(0.0f, 0.0f, 0.0f, 0.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

        glEnable(GL_DEPTH_TEST);
        glDepthMask(GL_TRUE);
        glDepthFunc(GL_LEQUAL);

        glMatrixMode(GL_PROJECTION);
//        glFrustum(-1,1,-1,1,1,100);
        glm::mat4 projMat = glm::frustum(-1.024f,1.024f,-0.768f,0.768f,1.0f,100.0f);
        glLoadMatrixf(glm::value_ptr(projMat));

        glMatrixMode(GL_MODELVIEW);
        const float radius = 2;

        //camera
        std::chrono::time_point<std::chrono::steady_clock> curTime = std::chrono::steady_clock::now();
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
        glLoadIdentity();
        glLoadMatrixf(&view[0][0]);

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

        glTranslatef(-0.5f, -0.5f, -0.5f);
        drawGeometry(vertices, vertices, 8, triangles, 12, edges, 12, true);
        glTranslatef(1, 1, 1);
        glVertexPointer(3, GL_FLOAT, 0, sphereVertices);
        glColorPointer(3, GL_FLOAT, 0, sphereVertices);

        glDrawArrays(GL_TRIANGLE_STRIP, 0, 16 * 15 + 2);
        //drawCube();

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
                    cameraRot[0] -= curEvent.motion.xrel * 0.5f;
                    cameraRot[1] -= curEvent.motion.yrel * 0.5f;
                }
            case SDL_KEYDOWN:
                float cameraSpeed = 0.01f;
                if(curEvent.key.keysym.sym == SDLK_LEFT || curEvent.key.keysym.sym == SDLK_q){
                    cameraPos[0] -= cameraSpeed;
                }
                if(curEvent.key.keysym.sym == SDLK_RIGHT || curEvent.key.keysym.sym == SDLK_d){
                    cameraPos[0] += cameraSpeed;
                }
                if(curEvent.key.keysym.sym == SDLK_UP || curEvent.key.keysym.sym == SDLK_z){
                    cameraPos[2] -= cameraSpeed;
                }
                if(curEvent.key.keysym.sym == SDLK_DOWN || curEvent.key.keysym.sym == SDLK_s){
                    cameraPos[2] += cameraSpeed;
                }
                if(curEvent.key.keysym.sym == SDLK_SPACE){
                    if(curEvent.key.keysym.mod == KMOD_SHIFT || curEvent.key.keysym.mod == KMOD_CTRL){
                        cameraPos[1] -= cameraSpeed;
                    }
                    else{
                        cameraPos[1] += cameraSpeed;
                    }
                }
        }
    }
}
