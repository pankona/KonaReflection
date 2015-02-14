#ifndef __FIELD_H__
#define __FIELD_H__

#include "Ball.h"

class Field {
private:
    int width;
    int height;
    Ball* ball;
    void moveBall(float);
public:
    void setFieldSize(int, int);
    void addBall(Ball*);
    Ball* getBall();
    void progress(float);
};

#endif // __FIELD_H__
