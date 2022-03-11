#include <iostream>
#include "ScriptablePipeline/AppTriangle.h"
#include "ScriptablePipeline/AppCube.h"

int main(int argc, char *argv[]) {

    BaseApp* app = new AppCube();
    app->run();

    return 0;
}