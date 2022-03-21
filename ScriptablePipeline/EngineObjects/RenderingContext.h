//
// Created by tsaury on 21/03/2022.
//

#pragma once

#include <memory>

class Geometry;
class App;

using namespace std;

class RenderingContext {

protected:
    Geometry* selectedGeometry;
    App* app;

public:
    RenderingContext(App* app);
    virtual ~RenderingContext();

    void render();
};
