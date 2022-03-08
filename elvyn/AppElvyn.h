//
// Created by ewakeford on 08/03/2022.
//

#pragma once



class AppElvyn {

public:

    bool appRunning = true;

    float cameraRotationX;
    float cameraRotationY;

    void Run();
    void HandleEvent();

};
