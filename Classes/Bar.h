#ifndef __BAR_H__
#define __BAR_H__

#include "Position.h"

class Bar {
private:    
    Position position;
    int width;
    int height;
public:
    Bar();
    void setPosition(Position);
    Position getPosition();
    void setWidth(int);
    int getWidth();
    void setHeight(int);
    int getHeight();
};

#endif // __BAR_H__
