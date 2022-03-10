#include <iostream>
#include "elvyn/AppElvyn.h"
#include "tom/AppTom.h"
#include "antoine/AppAntoine.h"
#include "elvyn/TestingZone.h"

int main(int argc, char *argv[]) {

    int x;

    std::cout << "App number :";
    std::cin >> x;
    AppTom *appTom = new AppTom();
    AppAntoine *appAntoine = new AppAntoine();
    AppElvyn *appElvyn = new AppElvyn();
    switch (x) {
        case 1:

            appTom->run();
            break;
        case 2:

            appAntoine->run();
            break;
        default:

            appElvyn->Run();
            break;

    }


    return 0;
}

