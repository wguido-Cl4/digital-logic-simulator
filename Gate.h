#ifndef GATE_H
#define GATE_H

#include <string>
#include "Wire.h"

using namespace std;

class Gate {
public:

    Gate(const string& type, int delay, Wire* input1, Wire* input2, Wire* output);

    string getType()       const;
    int    getDelay()      const;
    Wire*  getInput(int n) const;
    Wire*  getOutput()     const;

    char evaluate() const;

private:
    string type;
    int    delay;
    Wire*  inputs[2];
    Wire*  output;

    char triAND(char a, char b) const;
    char triOR (char a, char b) const;
    char triNOT(char a)         const;
    char triXOR(char a, char b) const;
};

#endif // GATE_H
