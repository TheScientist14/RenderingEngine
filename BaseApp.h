//
// Created by tsaury on 11/03/2022.
//

#pragma once

#include "SDL_stdinc.h"

struct SDL_Window;
struct ImGuiIO;

class BaseApp {

public:
    virtual void run();

    SDL_Window* init_window();
    virtual void gl_init() = 0;
    virtual void handle_events();
    virtual void main_loop() = 0;

protected:
    virtual void clean() = 0;

    bool app_running = false;
    int width = 1024;
    int height = 768;

    Uint64 curTime = 0;
    int deltaTime = 0;

    SDL_Window* win = nullptr;
    //ImGuiIO &io;
};
