//
// Created by tsaury on 14/03/2022.
//

#pragma once

#include <memory>
#include <set>

using namespace std;

class App;
class Transform;

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

    virtual void update(float deltaTime);
    void setParent(shared_ptr<EngineObject> newParent);
    shared_ptr<EngineObject> getParent();
    set<shared_ptr<EngineObject>> getChildren();
};


