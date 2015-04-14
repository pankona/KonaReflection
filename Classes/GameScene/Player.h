#ifndef __PLAYER_H__
#define __PLAYER_H__

class Player {

private:    
    int life; 

public:
    Player();
    Player(int);

    int getLife();
    void setLife(int);
    void decreaseLife();
    bool isStillAlive();
};

#endif // __PLAYER_H__
