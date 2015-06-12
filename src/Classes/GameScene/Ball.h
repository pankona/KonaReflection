#ifndef __BALL_H__
#define __BALL_H__

#include "Position.h"
#include <KonaVector.h>

class Ball {
private:    
    Position position;
    int radius;
    Kona::Vector vector;

public:
    Ball();
    void setPosition(Position);
    void setPosition(int, int);
    Position getPosition();
    void setDirection(int);
    int getDirection();
    void setSpeed(int);
    int getSpeed();
    void setRadius(int);
    int getRadius();
    void addVector(Kona::Vector);
    Kona::Vector& getVector();
    int getSpeedX();
    int getSpeedY();
};

#endif // __BALL_H__
