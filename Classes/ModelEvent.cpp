
#include "ModelEvent.h"

void
ModelEvent::addObserver(ModelEventObserver *in_observer) {
    observers.push_back(in_observer);
}

void
ModelEvent::notify() {
    for (ModelEventObserver* observer : observers) {
        observer->onUpdate();
    }
}
