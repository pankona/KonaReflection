#include "DrawableLabel.h"
#include "Position.h"

// private methods

void
DrawableLabel::createLabel(Position in_p, std::string in_text) {
    label = Label::createWithSystemFont(in_text, "HiraKakuProN-W6", 48);
    label->setPosition(in_p.x, in_p.y);
    label->setColor(Color3B::BLACK);
}

Node*
DrawableLabel::getNode() {
    return label;
}

// public methods

DrawableLabel::DrawableLabel(Position in_p, std::string in_text) {
    createLabel(in_p, in_text);
}
