#ifndef EVENT_H
#define EVENT_H

#include "Wire.h"

using namespace std;

class Event {
public:
    Event(int time, Wire* wire, char newValue);

    int getTime() const;
    Wire* getWire() const;
    char getNewValue() const;

private:
    int   time;
    Wire* wire;
    char  newValue;
};

#endif // EVENT_H