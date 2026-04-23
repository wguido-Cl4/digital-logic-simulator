#include <iostream>
#include <string>
#include "Circuit.h"

using namespace std;

int main() {
    cout << "Press <ENTER> only at prompt to quit program." << endl;

    while (true) {
        cout << "What is the name of the circuit test file (base name only):  ";
        string baseName;
        getline(cin, baseName);

        if (baseName.empty()) {
            break;
        }

        string circuitFile = baseName + ".txt";
        string vectorFile  = baseName + "_v.txt";

        cout << "\nSimulating " << circuitFile << ".\n" << endl;

        Circuit circuit;

        if (!circuit.loadCircuit(circuitFile)) {
            continue;
        }

        if (!circuit.loadVector(vectorFile)) {
            continue;
        }

        circuit.simulate();
        circuit.printResults();

        cout << endl;
    }

    return 0;
}