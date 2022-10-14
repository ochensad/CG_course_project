#ifndef TIMER_H
#define TIMER_H

#include "model.h"

#define HZ 2300000000

class Timer
{
public:
    Timer(int polygons);
    void calculate_time(void);
private:
    void create_model(int num);
    void func(void);
    int count;
    Model* model;
};

#endif // TIMER_H
