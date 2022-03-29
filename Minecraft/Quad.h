//
// Created by avarnier-navarro on 28/03/2022.
//

#pragma once


#include <vector>
#include "../ScriptablePipeline/EngineObjects/RenderedObject.h"

class Geometry;
class App;

class Quad : public RenderedObject{

public:

    Quad(App *app, int height, int width, vec3 direction);
    vector<unsigned int> getTriangles();
    vector<float> getTrianglesPos();
    shared_ptr<Geometry> getGeometryPtr();
    vector<float> getUVVector();
    vector<float> getNormalsVector();
    void fastRender() const override;
    void createTrianglesX();
    void createTrianglesY();
    void createTrianglesZ();

protected:
    int height = 1;
    int width = 0;
    vec3 direction;
    vector<float> trianglesPos;
    vector<unsigned int> triangles;
    vector<float> uvVector;
    vector<float> normalsVector;
};
