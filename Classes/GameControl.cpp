#include "GameControl.h"
#include <stdio.h>

void
GameControl::update(float delta) {
    mm.progress(delta);
    vm.updateView();
}

void
GameControl::initialize(Scene* baseScene) {
    mm.initialize();
    vm.initialize(baseScene);
}
