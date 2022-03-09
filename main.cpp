#include "elvyn/AppElvyn.h"
#include "tom/AppTom.h"
#include "antoine/AppAntoine.h"
#include "elvyn/TestingZone.h"

int main(int argc, char* argv[])
{
    AppTom* app = new AppTom();
    app->run();

    return 0;
}

