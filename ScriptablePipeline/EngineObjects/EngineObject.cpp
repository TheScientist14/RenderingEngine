//
// Created by tsaury on 14/03/2022.
//

#include "EngineObject.h"

#include <algorithm>

#include "Transform.h"

EngineObject::EngineObject(App* app) {

    this->app = app;

    this->transform = new Transform();
}

EngineObject::~EngineObject() {

}

void EngineObject::update(float deltaTime) {

}

// TODO : recompoute transform
void EngineObject::setParent(shared_ptr<EngineObject> newParent){
    if(parent != nullptr){
        parent->removeChild(shared_from_this());
    }
    parent = newParent;
    if(parent != nullptr){
        parent->addChild(shared_from_this());
    }
}

void EngineObject::addChild(shared_ptr<EngineObject> newChild){
    if(newChild != nullptr){
        children.insert(newChild);
    }
}

void EngineObject::removeChild(shared_ptr<EngineObject> removingChild){
    if(removingChild != nullptr){
        children.erase(removingChild);
    }
}

shared_ptr<EngineObject> EngineObject::getParent() {
    return shared_ptr<EngineObject>(parent);
}

set<shared_ptr<EngineObject>> EngineObject::getChildren() {
    set<shared_ptr<EngineObject>> childrenCopy;
    for_each(children.cbegin(), children.cend(), [&childrenCopy](shared_ptr<EngineObject> child) {
        childrenCopy.insert(shared_ptr<EngineObject>(child));
    });
    return childrenCopy;
}
