#include "Circuit.h"
#include <iostream>
#include <fstream>
#include <sstream>

using namespace std;

Circuit::Circuit() {
    name = "";
}

Circuit::~Circuit() {
    for (int i = 0; i < gates.size(); i++) {
        delete gates[i];
    }
    for (int i = 0; i < wires.size(); i++) {
        delete wires[i];
    }
}

Wire* Circuit::getOrCreateWire(int index) {
    if (index >= (int)wires.size()) {
        wires.resize(index + 1, nullptr);
    }
    if (wires[index] == nullptr) {
        wires[index] = new Wire(index);
    }
    return wires[index];
}

bool Circuit::loadCircuit(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Error: could not open circuit file '" << filename << "'" << endl;
        return false;
    }

    string line = "";
    string type = "";

    while (getline(inFile, line)) {
        istringstream ss(line);
        ss >> type;

        if (type == "CIRCUIT") {
            ss >> name;

        } else if (type == "INPUT") {
            string padName = "";
            int wireNum = 0;
            ss >> padName >> wireNum;
            Wire* w = getOrCreateWire(wireNum);
            w->setName(padName);
            inputPads.push_back(w);

        } else if (type == "OUTPUT") {
            string padName = "";
            int wireNum = 0;
            ss >> padName >> wireNum;
            Wire* w = getOrCreateWire(wireNum);
            w->setName(padName);
            outputPads.push_back(w);

        } else if (type == "NOT") {
            string delayStr = "";
            ss >> delayStr;
            int delay = 0;
            istringstream ds(delayStr);
            ds >> delay;

            int w1 = 0, wout = 0;
            ss >> w1 >> wout;
            Wire* inWire = getOrCreateWire(w1);
            Wire* outWire = getOrCreateWire(wout);
            Gate* g = new Gate(type, delay, inWire, nullptr, outWire);
            gates.push_back(g);
            inWire->addDrivenGate(g);

        } else if (type == "AND") {
            string delayStr = "";
            ss >> delayStr;
            int delay = 0;
            istringstream ds(delayStr);
            ds >> delay;

            int w1 = 0, w2 = 0, wout = 0;
            ss >> w1 >> w2 >> wout;
            Wire* inWire1 = getOrCreateWire(w1);
            Wire* inWire2 = getOrCreateWire(w2);
            Wire* outWire = getOrCreateWire(wout);
            Gate* g = new Gate(type, delay, inWire1, inWire2, outWire);
            gates.push_back(g);
            inWire1->addDrivenGate(g);
            inWire2->addDrivenGate(g);

        } else if (type == "OR") {
            string delayStr = "";
            ss >> delayStr;
            int delay = 0;
            istringstream ds(delayStr);
            ds >> delay;

            int w1 = 0, w2 = 0, wout = 0;
            ss >> w1 >> w2 >> wout;
            Wire* inWire1 = getOrCreateWire(w1);
            Wire* inWire2 = getOrCreateWire(w2);
            Wire* outWire = getOrCreateWire(wout);
            Gate* g = new Gate(type, delay, inWire1, inWire2, outWire);
            gates.push_back(g);
            inWire1->addDrivenGate(g);
            inWire2->addDrivenGate(g);

        } else if (type == "XOR") {
            string delayStr = "";
            ss >> delayStr;
            int delay = 0;
            istringstream ds(delayStr);
            ds >> delay;

            int w1 = 0, w2 = 0, wout = 0;
            ss >> w1 >> w2 >> wout;
            Wire* inWire1 = getOrCreateWire(w1);
            Wire* inWire2 = getOrCreateWire(w2);
            Wire* outWire = getOrCreateWire(wout);
            Gate* g = new Gate(type, delay, inWire1, inWire2, outWire);
            gates.push_back(g);
            inWire1->addDrivenGate(g);
            inWire2->addDrivenGate(g);

        } else if (type == "NAND") {
            string delayStr = "";
            ss >> delayStr;
            int delay = 0;
            istringstream ds(delayStr);
            ds >> delay;

            int w1 = 0, w2 = 0, wout = 0;
            ss >> w1 >> w2 >> wout;
            Wire* inWire1 = getOrCreateWire(w1);
            Wire* inWire2 = getOrCreateWire(w2);
            Wire* outWire = getOrCreateWire(wout);
            Gate* g = new Gate(type, delay, inWire1, inWire2, outWire);
            gates.push_back(g);
            inWire1->addDrivenGate(g);
            inWire2->addDrivenGate(g);

        } else if (type == "NOR") {
            string delayStr = "";
            ss >> delayStr;
            int delay = 0;
            istringstream ds(delayStr);
            ds >> delay;

            int w1 = 0, w2 = 0, wout = 0;
            ss >> w1 >> w2 >> wout;
            Wire* inWire1 = getOrCreateWire(w1);
            Wire* inWire2 = getOrCreateWire(w2);
            Wire* outWire = getOrCreateWire(wout);
            Gate* g = new Gate(type, delay, inWire1, inWire2, outWire);
            gates.push_back(g);
            inWire1->addDrivenGate(g);
            inWire2->addDrivenGate(g);

        } else if (type == "XNOR") {
            string delayStr = "";
            ss >> delayStr;
            int delay = 0;
            istringstream ds(delayStr);
            ds >> delay;

            int w1 = 0, w2 = 0, wout = 0;
            ss >> w1 >> w2 >> wout;
            Wire* inWire1 = getOrCreateWire(w1);
            Wire* inWire2 = getOrCreateWire(w2);
            Wire* outWire = getOrCreateWire(wout);
            Gate* g = new Gate(type, delay, inWire1, inWire2, outWire);
            gates.push_back(g);
            inWire1->addDrivenGate(g);
            inWire2->addDrivenGate(g);
        }
    }

    inFile.close();
    return true;
}

bool Circuit::loadVector(const string& filename) {
    ifstream inFile(filename);
    if (!inFile.is_open()) {
        cout << "Error: could not open vector file '" << filename << "'" << endl;
        return false;
    }

    string line = "";
    string type = "";

    while (getline(inFile, line)) {
        istringstream ss(line);
        ss >> type;

        if (type == "INPUT") {
            string padName = "";
            int time = 0;
            string valStr = "";
            ss >> padName >> time >> valStr;

            Wire* target = nullptr;
            for (int i = 0; i < inputPads.size(); i++) {
                if (inputPads[i] != nullptr && inputPads[i]->getName() == padName) {
                    target = inputPads[i];
                    break;
                }
            }

            if (target != nullptr) {
                char val = 'X';
                if (valStr == "0") {
                    val = '0';
                } else if (valStr == "1") {
                    val = '1';
                } else {
                    val = 'X';
                }
                eventQueue.push(Event(time, target, val));
            }
        }
    }

    inFile.close();
    return true;
}

void Circuit::simulate() {
    int currentTime = 0;
    int maxTime = 60;

    for (int i = 0; i < inputPads.size(); i++) {
        if (inputPads[i] != nullptr) {
            inputPads[i]->appendHistory('X');
        }
    }
    for (int i = 0; i < outputPads.size(); i++) {
        if (outputPads[i] != nullptr) {
            outputPads[i]->appendHistory('X');
        }
    }

    while (currentTime < maxTime) {
        bool anyChange = false;

        vector<Wire*> wireList;
        vector<char> valList;

        while (!eventQueue.empty() && eventQueue.top().getTime() == currentTime) {
            Event e = eventQueue.top();
            eventQueue.pop();

            bool alreadyThere = false;
            for (int i = 0; i < wireList.size(); i++) {
                if (wireList[i] == e.getWire()) {
                    valList[i] = e.getNewValue();
                    alreadyThere = true;
                    break;
                }
            }
            if (alreadyThere == false) {
                wireList.push_back(e.getWire());
                valList.push_back(e.getNewValue());
            }
        }

        for (int i = 0; i < wireList.size(); i++) {
            wireList[i]->setValue(valList[i]);
            anyChange = true;
        }

        vector<Gate*> gateList;
        for (int i = 0; i < wireList.size(); i++) {
            const vector<Gate*>& drivenGates = wireList[i]->getDrives();
            for (int j = 0; j < drivenGates.size(); j++) {
                bool found = false;
                for (int k = 0; k < gateList.size(); k++) {
                    if (gateList[k] == drivenGates[j]) {
                        found = true;
                        break;
                    }
                }
                if (found == false) {
                    gateList.push_back(drivenGates[j]);
                }
            }
        }

        for (int i = 0; i < gateList.size(); i++) {
            Gate* g = gateList[i];
            char oldVal = g->getOutput()->getValue();
            char newVal = g->evaluate();

            if (newVal != oldVal) {
                int futureTime = currentTime + g->getDelay();
                if (futureTime < maxTime) {
                    eventQueue.push(Event(futureTime, g->getOutput(), newVal));
                }
            }
        }

        currentTime++;

        for (int i = 0; i < inputPads.size(); i++) {
            if (inputPads[i] != nullptr) {
                inputPads[i]->appendHistory(inputPads[i]->getValue());
            }
        }
        for (int i = 0; i < outputPads.size(); i++) {
            if (outputPads[i] != nullptr) {
                outputPads[i]->appendHistory(outputPads[i]->getValue());
            }
        }

        if (eventQueue.empty() && anyChange == false) {
            break;
        }
    }
}

void Circuit::printResults() const {
    vector<Wire*> allWires;
    for (int i = 0; i < inputPads.size(); i++) {
        if (inputPads[i] != nullptr) {
            allWires.push_back(inputPads[i]);
        }
    }
    for (int i = 0; i < outputPads.size(); i++) {
        if (outputPads[i] != nullptr) {
            allWires.push_back(outputPads[i]);
        }
    }

    if (allWires.size() == 0) {
        return;
    }

    int histLength = (int)allWires[0]->getHistory().size();

    int longestName = 0;
    for (int i = 0; i < allWires.size(); i++) {
        int nameLen = (int)allWires[i]->getName().size();
        if (nameLen > longestName) {
            longestName = nameLen;
        }
    }

    cout << "\nWire traces:" << endl;

    for (int i = 0; i < allWires.size(); i++) {
        Wire* w = allWires[i];

        string label = w->getName();
        while ((int)label.size() < longestName) {
            label = " " + label;
        }

        string waveform = "";
        string history = w->getHistory();
        for (int j = 0; j < history.size(); j++) {
            if (history[j] == '0') {
                waveform = waveform + '_';
            } else if (history[j] == '1') {
                waveform = waveform + '-';
            } else {
                waveform = waveform + 'x';
            }
        }

        cout << label << " | " << waveform << endl;

        string spaces = "";
        for (int j = 0; j < longestName; j++) {
            spaces = spaces + " ";
        }

        if (i < (int)allWires.size() - 1) {
            cout << spaces << " | " << endl;
        } else {
            string bottomLine = "";
            for (int j = 0; j < histLength + 1; j++) {
                bottomLine = bottomLine + '_';
            }
            cout << spaces << " |" << bottomLine << endl;
        }
    }

    string spaces2 = "";
    for (int i = 0; i < longestName; i++) {
        spaces2 = spaces2 + " ";
    }

    string topRuler = spaces2 + "   ";
    string botRuler = spaces2 + "   ";

    int t = 0;
    while (t < histLength) {
        if (t % 5 == 0) {
            string tStr = to_string(t);
            if (tStr.size() == 1) {
                topRuler = topRuler + '0';
                botRuler = botRuler + tStr[0];
            } else {
                topRuler = topRuler + tStr[tStr.size() - 2];
                botRuler = botRuler + tStr[tStr.size() - 1];
            }
            int nextT = ((t / 5) + 1) * 5;
            int fillAmt = nextT - t - 1;
            if (nextT > histLength) {
                fillAmt = histLength - t - 1;
            }
            for (int i = 0; i < fillAmt; i++) {
                topRuler = topRuler + '-';
                botRuler = botRuler + ' ';
            }
            t = nextT;
        } else {
            t++;
        }
    }

    cout << topRuler << endl;
    cout << botRuler << endl;

    cout << "\nCircuit Name: " << name << endl;
    cout << "Time elapsed: " << histLength << "ns" << endl;
}