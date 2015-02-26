#ifndef __BLOCK_H__
#define __BLOCK_H__

#include "Position.h"

class Block {
private:    
    int width;
    int height;
    Position position;
    int life;

public:
    Block();

    void setSize(int, int);
    int getWidth();
    int getHeight();

    void setPosition(Position);
    void setPosition(int, int);
    Position getPosition();

    void setLife(int);
    int getLife();
    void decreaseLife(int);
    bool stillAlive();
};

#endif // __BLOCK_H__
