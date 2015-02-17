#include "GameControl.h"

void
GameControl::update(float delta) {
    vm.progress(delta);
}

void
GameControl::initialize(Scene* baseScene) {
    vm.initialize(baseScene);
}
