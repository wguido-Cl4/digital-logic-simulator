#include <iostream>
#include <string>
#include "Circuit.h"

using namespace std;

int main() {
    string circuitFile, vectorFile;

    cout << "Enter circuit file name: ";
    cin >> circuitFile;

    cout << "Enter vector file name: ";
    cin >> vectorFile;

    Circuit circuit;

    if (!circuit.loadCircuit(circuitFile)) {
        return 1;
    }

    if (!circuit.loadVector(vectorFile)) {
        return 1;
    }

    circuit.simulate();
    circuit.printResults();

    return 0;
}
