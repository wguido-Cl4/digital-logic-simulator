#include "Wire.h"
#include <iostream>

using namespace std;

Wire::Wire(int index, const string& name, char value)
    : index(index), name(name), value(value) {
}

void Wire::setValue(char val) {
    value = val;
}

void Wire::setName(const string& nameSet) {
    name = nameSet;
}

void Wire::addDrivenGate(Gate* gate) {
    drives.push_back(gate);
}

void Wire::appendHistory(char symbol) {
    history += symbol;
}

char Wire::getValue() const {
    return value;
}

string Wire::getName() const {
    return name;
}

int Wire::getIndex() const {
    return index;
}

const vector<Gate*>& Wire::getDrives() const {
    return drives;
}

string Wire::getHistory() const {
    return history;
}

void Wire::printHistory() const {
    string label;
    if (name.empty()) {
        label = "Wire" + to_string(index);
    } else {
        label = name;
    }
    cout << label << "\t" << history << endl;
}
