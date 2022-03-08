#pragma once

class AppTom
{
private:
    bool appRunning;
    float cameraRotationX;
    float cameraRotationY;

    void handle_events();

public:
    void run();
};

