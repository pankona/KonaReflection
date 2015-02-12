#ifndef __BALL_H__
#define __BALL_H__

#include "Position.h"

class Ball {
private:    
    int direction;
    int speed;
    Position position;
    int radius;
public:
    Ball();
    void setPosition(Position);
    Position getPosition();
    void setDirection(int);
    int getDirection();
    void setSpeed(int);
    int getSpeed();
    void setRadius(int);
    int getRadius();
};

#endif // __BALL_H__
