//
// Created by tsaury on 14/03/2022.
//

#pragma once

#include <memory>

#include "Transform.h"

using namespace std;

class App;

class EngineObject : public enable_shared_from_this<EngineObject> {

protected:

    App* app;

public:
    Transform transform;
    EngineObject(App* app);
    virtual void update(float deltaTime);
    virtual ~EngineObject();
};


