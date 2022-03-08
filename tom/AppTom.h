#pragma once

class AppTom
{
private:
    bool appRunning;

    float cameraRotationX;
    float cameraRotationY;

    bool isDragging;

    void handle_events();

public:
    void run();
};

