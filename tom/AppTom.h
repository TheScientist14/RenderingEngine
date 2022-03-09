#pragma once

#include <glm/vec3.hpp>

class AppTom
{
private:
    bool appRunning;

    glm::vec3 cameraPos;
    glm::vec3 cameraRot;

    bool isDragging;

    void handle_events();

public:
    void run();
};

