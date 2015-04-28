#ifndef __SELFTIMERLISTENER_H__
#define __SELFTIMERLISTENER_H__

class SelfTimerListener {
public:
    virtual void onTimerExpired(int) = 0;
};

#endif /* __SELFTIMERLISTENER_H__ */
