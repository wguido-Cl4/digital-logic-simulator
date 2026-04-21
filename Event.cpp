#include "Event.h"

using namespace std;

Event::Event(int time, Wire* wire, char newValue)
    : time(time), wire(wire), newValue(newValue) {
}

int Event::getTime() const {
    return time;
}

Wire* Event::getWire() const {
    return wire;
}

char Event::getNewValue() const {
    return newValue;
}
