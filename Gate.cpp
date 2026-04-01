#include "Gate.h"
#include <iostream>

using namespace std;


Gate::Gate(const string& type, int delay, Wire* input1, Wire* input2, Wire* output)
    : type(type), delay(delay), output(output) {
    inputs_[0] = input1;
    inputs_[1] = input2;
}

string Gate::getType() const {
    return type;
}

int Gate::getDelay() const {
    return delay;
}

Wire* Gate::getInput(int n) const {
    if (n == 0 || n == 1)
        return inputs[n];
    return nullptr;
}

Wire* Gate::getOutput() const {
    return output;
}

char Gate::triAND(char a, char b) const {
    if (a == '0' || b == '0') return '0';
    if (a == '1' && b == '1') return '1';
    return 'X';
}

char Gate::triOR(char a, char b) const {
    if (a == '1' || b == '1') return '1';
    if (a == '0' && b == '0') return '0';
    return 'X';
}

char Gate::triNOT(char a) const {
    if (a == '0') return '1';
    if (a == '1') return '0';
    return 'X';
}

char Gate::triXOR(char a, char b) const {
    if (a == 'X' || b == 'X') {
        return 'X';
    }
    if (a != b) {
        return '1';
    }
    else {
        return '0';
    }
}


char Gate::evaluate() const {
    char a = inputs[0] ? inputs[0]->getValue() : 'X';
    char b = inputs[1] ? inputs[1]->getValue() : 'X';

    if (type == "NOT")  return triNOT(a);
    if (type == "AND")  return triAND(a, b);
    if (type == "OR")   return triOR (a, b);
    if (type == "XOR")  return triXOR(a, b);
    if (type == "NAND") return triNOT(triAND(a, b));
    if (type == "NOR")  return triNOT(triOR (a, b));
    if (type == "XNOR") return triNOT(triXOR(a, b));

    cout << "Unknown gate type '" << type << "'" << endl;
    return 'X';
}
