#ifndef __GAMECONTROL_H__
#define __GAMECONTROL_H__

#include "DrawableBall.h"
#include "Field.h"
#include "Ball.h"

class GameControl {
private:
    Field field;
    DrawableBall* dball;

public:
    void update(float);
    void addDBall(DrawableBall*);

};

#endif // __FIELD_H__
