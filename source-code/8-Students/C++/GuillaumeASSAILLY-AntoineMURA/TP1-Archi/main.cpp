#include <iostream>
#include "objects/World.h"

int main() {


    for(int i = 1; i <= 100; ++i) {
        auto* w = new World();
        w->launch(i);
        delete w;
    }


    return 0;
}
