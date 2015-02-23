#ifndef __FIELD_H__
#define __FIELD_H__

class Field {
private:
    int width;
    int height;

public:
    Field();
    int getWidth();
    int getHeight();
    void setFieldSize(int, int);
};

#endif // __FIELD_H__
