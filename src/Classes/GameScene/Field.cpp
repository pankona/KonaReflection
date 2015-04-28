
#include "Field.h"

// public methods

Field::Field() {
}

int
Field::getWidth() {
    return width;
}

int
Field::getHeight() {
    return height;
}

void
Field::setFieldSize(int in_width, int in_height) {
    width = in_width;
    height = in_height;
}


