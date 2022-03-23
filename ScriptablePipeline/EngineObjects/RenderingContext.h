//
// Created by tsaury on 21/03/2022.
//

#pragma once

#include <memory>
#include <vector>
#include <map>

class Geometry;
class GameObject;
class App;
class ModelShaderData;

using namespace std;

class RenderingContext {

protected:
    App* app;

    shared_ptr<Geometry> selectedGeometry = nullptr;

public:
    RenderingContext(App* app);
    virtual ~RenderingContext();

    void render();
};
