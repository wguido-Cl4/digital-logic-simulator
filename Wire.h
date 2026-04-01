#ifndef WIRE_H
#define WIRE_H

#include <string>
#include <vector>

using namespace std;

class Gate;

class Wire {
public:

    Wire(int index = 0, const string& name = "", char value = 'X');

    void setValue(char val);
    void setName(const string& name);
    void addDrivenGate(Gate* gate);
    void appendHistory(char symbol);

    char getValue() const;
    string getName() const;
    int getIndex() const;
    const vector<Gate*>& getDrives() const;
    string getHistory() const;

    void printHistory() const;

private:
    int            index;
    string         name;
    char           value;
    vector<Gate*>  drives;
    string         history;
};

#endif // WIRE_H#endif // WIRE_H
