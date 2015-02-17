#include "ModelManager.h"

ModelManager::ModelManager() {
}

void
ModelManager::initialize() {
    field = new Field();
}

void
ModelManager::progress(float delta) {
    field->progress(delta);
}

Field*
ModelManager::getField() {
    return field;
}
