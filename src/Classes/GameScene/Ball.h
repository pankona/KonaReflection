#ifndef __BALL_H__
#define __BALL_H__

#include "Position.h"
#include <KonaVector2D.h>
#include <KonaRect.h>

class Ball {
private:    
    int radius;
    Kona::Vector2D vector;

public:
    Ball();
    void setPosition(Position);
    void setPosition(float, float);
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
    Kona::Vector2D getVector2D();
    void setVector(Kona::Vector);
    bool isTowardRight();
    bool isTowardLeft();
    bool isTowardUp();
    bool isTowardDown();
    enum DIRECTION {
        UP,
        DOWN,
        RIGHT,
        LEFT
    };
    Kona::Vector2D getVector2DFromCircumference(DIRECTION);
    Kona::Rect getRectFromSpeedAndRadius();
};

#endif // __BALL_H__
