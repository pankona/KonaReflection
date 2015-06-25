#ifndef __BALL_H__
#define __BALL_H__

#include "Position.h"
#include <KonaVector2D.h>

class Ball {
private:    
    Position position;
    int radius;
    Kona::Vector2D vector;

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
    float getSpeedX();
    float getSpeedY();
    Kona::Vector getVector();
    void setVector(Kona::Vector);
    bool isTowardRight();
    bool isTowardLeft();
    bool isTowardUp();
    bool isTowardDown();
    enum DIRECTION {
        BALL_UP,
        BALL_DOWN,
        BALL_RIGHT,
        BALL_LEFT
    };
    Kona::Vector2D getVector2DFromCircumference(DIRECTION);
};

#endif // __BALL_H__
