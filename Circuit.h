#ifndef CIRCUIT_H
#define CIRCUIT_H

#include <string>
#include <vector>
#include <queue>
#include "Gate.h"
#include "Wire.h"
#include "Event.h"

using namespace std;

struct EventComparator {
    bool operator()(const Event& a, const Event& b) {
        if (a.getTime() > b.getTime()) {
            return true;
        } else {
            return false;
        }
    }
};

class Circuit {
public:

    Circuit();
    ~Circuit();

    bool loadCircuit(const string& filename);
    bool loadVector(const string& filename);

    void simulate();

    void printResults() const;

private:
    string name;

    vector<Wire*> wires;
    vector<Gate*> gates;
    vector<Wire*> inputPads;
    vector<Wire*> outputPads;

    priority_queue<Event, vector<Event>, EventComparator> eventQueue;

    Wire* getOrCreateWire(int index);
};

#endif // CIRCUIT_H
