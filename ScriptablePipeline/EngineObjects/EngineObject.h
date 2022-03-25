//
// Created by tsaury on 14/03/2022.
//

#pragma once

#include <memory>
#include <set>

#include <glm/mat4x4.hpp>

using namespace std;
using namespace glm;

class App;
class Transform;

// TODO : test set of shared pointer

class EngineObject : public enable_shared_from_this<EngineObject> {

protected:
    App* app;
    shared_ptr<EngineObject> parent;
    set<shared_ptr<EngineObject>> children;

    void addChild(shared_ptr<EngineObject> newChild);
    void removeChild(shared_ptr<EngineObject> removingChild);

public:

    Transform* transform;

    EngineObject(App* app);
    virtual ~EngineObject();

    virtual void update(int deltaTime);
    void setParent(shared_ptr<EngineObject> newParent);

    shared_ptr<EngineObject> getParent() const;
    set<shared_ptr<EngineObject>> getChildren() const;
};


