#ifndef __MODELMANAGER_H__
#define __MODELMANAGER_H__

#include "Field.h"
#include "Bar.h"
#include "Ball.h"

class ModelManager {
private:    
    Field* field;
    Bar* bar;
    Ball* ball;

    bool isTouchOnRightSide(int);
    void moveBall(float);
    void moveBar(float);

public:
    ModelManager();
    void initialize();
    void progress(float delta);
    void onTouchBegan(int, int);
    void onTouchMoved(int, int);
    void onTouchEnded();
    void onCollisionBallAndBar();
};

#endif // __MODELMANAGER_H__
