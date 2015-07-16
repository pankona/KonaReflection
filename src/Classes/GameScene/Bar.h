#ifndef __BAR_H__
#define __BAR_H__

#include "Position.h"
#include "BarDirection.h"

class Bar {

private:    
    Position position;
    int width;
    int height;
    int direction;
    int speed;
    int angle;
    enum Pivot {
        LEFT,
        RIGHT,
        CENTER
    };
    Pivot currentPivot;
    bool is_swinging;

public:
    Bar();
    void setPosition(Position);
    void setPosition(int, int);
    Position getPosition();
    void setWidth(int);
    int getWidth();
    void setHeight(int);
    int getHeight();
    void setSpeed(int);
    int getSpeed();
    void setDirection(BarDirection);
    BarDirection getDirection();
    void setAngle(int);
    int getAngle();
    void setPivot(Pivot);
    Pivot getPivot();
    bool isSwinging();
    void startSwinging();
    void endSwinging();
};

#endif // __BAR_H__
