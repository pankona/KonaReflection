#ifndef __FIELD_H__
#define __FIELD_H__

#include "DrawableBall.h"

class Field {
private:
    int width;
    int height;
    DrawableBall *dBall;
    void moveDBall(float);
public:
    void addDBall(DrawableBall*);
    DrawableBall* getDBall();
    void progress(float);
};

#endif // __FIELD_H__
