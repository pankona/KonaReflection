#include "TitleControl.h"
#include <stdio.h>

void
TitleControl::initialize(Scene* baseScene) {
    tvm.initialize(baseScene);
    tvm.addViewManagerEventListener(this);

    Size screenSize = Director::getInstance()->getVisibleSize();
    tvm.initializeTitle((int) screenSize.width, (int) screenSize.height);
}

void
TitleControl::onViewManagerEvent(ViewManagerEvent in_event, void* arg) {
    log ("event fired");
}
