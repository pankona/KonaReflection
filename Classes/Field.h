#ifndef __FIELD_H__
#define __FIELD_H__

#include "Ball.h"
#include "Bar.h"

class Field {
private:
    int width;
    int height;
    Ball* ball;
    Bar* bar;
    void moveBall(float);
    bool isTouchOnRightSide(int);
    void moveBar(float delta);

public:
    Field();
    int getWidth();
    int getHeight();
    void setFieldSize(int, int);
    void addBall(Ball*);
    Ball* getBall();
    void setBar(Bar*);
    Bar* getBar();
    void progress(float);
    void onTouchBegan(int, int);
    void onTouchEnded();
};

#endif // __FIELD_H__
