#include <iostream>
#include "ScriptablePipeline/AppTriangle.h"

int main(int argc, char *argv[]) {

    BaseApp* app = new AppTriangle();
    app->run();

    return 0;
}

