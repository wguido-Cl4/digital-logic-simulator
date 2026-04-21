#include "Circuit.h"
#include <iostream>
#include <fstream>
#include <sstream>
 
using namespace std;
 
Circuit::Circuit() {
}
// Below is our destructor
Circuit::~Circuit() {
    for (Gate* g : gates) delete g;
    for (Wire* w : wires) delete w;
}
//finds and converts info to use to create wire
Wire* Circuit::getOrCreateWire(int index) {
    if (index >= (int)wires.size()) {
        wires.resize(index + 1, nullptr);
    }
    if (wires[index] == nullptr) {
        wires[index] = new Wire(index);
    }
    return wires[index];
}
 // opens .txt file and gathers all info by searching up keywords
bool Circuit::loadCircuit(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: could not open circuit file '" << filename << "'" << endl;
        return false;
    }
 
    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string keyword;
        ss >> keyword;
 
        if (keyword == "CIRCUIT") {
            ss >> name;
 
        } else if (keyword == "INPUT") {
            string padName;
            int wireNum;
            if (ss >> padName >> wireNum) {
                Wire* w = getOrCreateWire(wireNum);
                w->setName(padName);
                inputPads.push_back(w);
            }
 
        } else if (keyword == "OUTPUT") {
            string padName;
            int wireNum;
            if (ss >> padName >> wireNum) {
                Wire* w = getOrCreateWire(wireNum);
                w->setName(padName);
                outputPads.push_back(w);
            }
 
        } else if (keyword == "NOT" || keyword == "AND" || keyword == "OR"  ||
                   keyword == "XOR" || keyword == "NAND"|| keyword == "NOR" ||
                   keyword == "XNOR") {
 
            string delayStr;
            ss >> delayStr;
            //gets rid of ns
            int delay = 0;
            istringstream delayStream(delayStr);
            delayStream >> delay;

 
            if (keyword == "NOT") {
                int in1Num, outNum;
                if (ss >> in1Num >> outNum) {
                    Wire* in1 = getOrCreateWire(in1Num);
                    Wire* out = getOrCreateWire(outNum);
                    //creates the gate
                    Gate* g = new Gate(keyword, delay, in1, nullptr, out);
                    gates.push_back(g);
                    in1->addDrivenGate(g);
                }
            } else {
                int in1Num, in2Num, outNum;
                if (ss >> in1Num >> in2Num >> outNum) {
                    Wire* in1 = getOrCreateWire(in1Num);
                    Wire* in2 = getOrCreateWire(in2Num);
                    Wire* out = getOrCreateWire(outNum);
                    Gate* g = new Gate(keyword, delay, in1, in2, out);
                    gates.push_back(g);
                    in1->addDrivenGate(g);
                    in2->addDrivenGate(g); 
                }
            }
        }
    }
 
    file.close();
    return true;
}

// reads vector and gathers relevant info
bool Circuit::loadVector(const string& filename) {
    ifstream file(filename);
    if (!file.is_open()) {
        cout << "Error: could not open vector file '" << filename << "'" << endl;
        return false;
    }
 
    string line;
    while (getline(file, line)) {
        istringstream ss(line);
        string keyword;
        ss >> keyword;
 
        if (keyword == "INPUT") {
            string padName;
            int time, value;
            if (ss >> padName >> time >> value) {
                Wire* targetWire = nullptr;
                for (Wire* w : inputPads) {
                    if (w != nullptr && w->getName() == padName) {
                        targetWire = w;
                        break;
                    }
                }
                if (targetWire != nullptr) {
                    char val = (value == 0) ? '0' : '1';
                    eventQueue.push(Event(time, targetWire, val));
                }
            }
        }
    }
 
    file.close();
    return true;
}
 
void Circuit::simulate() {
    int currentTime = 0;
    int maxTime = 60;
 
    for (Wire* w : inputPads)  if (w) w->appendHistory('X');
    for (Wire* w : outputPads) if (w) w->appendHistory('X');
 
    while (currentTime < maxTime) {
        bool anyChange = false;
 
        while (!eventQueue.empty() && eventQueue.top().getTime() == currentTime) {
            Event e = eventQueue.top();
            eventQueue.pop();
 
            Wire* w = e.getWire();
            char newVal = e.getNewValue();
 
            for (Gate* g : w->getDrives()) {
                char oldOutput = g->getOutput()->getValue();
 
                char savedVal = w->getValue();
                w->setValue(newVal);
                char newOutput = g->evaluate();
                w->setValue(savedVal);
 
                if (newOutput != oldOutput) {
                    int futureTime = currentTime + g->getDelay();
                    if (futureTime < maxTime) {
                        eventQueue.push(Event(futureTime, g->getOutput(), newOutput));
                    }
                }
            }
 
            w->setValue(newVal);
            anyChange = true;
        }
 
        currentTime++;
 
        for (Wire* w : inputPads)  if (w) w->appendHistory(w->getValue());
        for (Wire* w : outputPads) if (w) w->appendHistory(w->getValue());
 
        if (eventQueue.empty() && !anyChange) {
            break;
        }
    }
}
 
void Circuit::printResults() const {
    cout << "\nSimulation Results for: " << name << endl;
    cout << "--------------------------------------------" << endl;
    cout << "Inputs:" << endl;
    for (Wire* w : inputPads) {
        if (w) w->printHistory();
    }
    cout << "Outputs:" << endl;
    for (Wire* w : outputPads) {
        if (w) w->printHistory();
    }
}
