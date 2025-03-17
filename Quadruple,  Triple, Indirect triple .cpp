#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Quadruple {
    string op, arg1, arg2, result;
};

struct Triple {
    string op, arg1, arg2;
};

struct IndirectTriple {
    int index;
    Triple triple;
};

vector<Quadruple> quadruples;
vector<Triple> triples;
vector<IndirectTriple> indirectTriples;

void generateIntermediateCode(string op, string arg1, string arg2, string result) {
    Quadruple q = {op, arg1, arg2, result};
    quadruples.push_back(q);
    
    Triple t = {op, arg1, arg2};
    triples.push_back(t);
    
    IndirectTriple it = {static_cast<int>(triples.size()) - 1, t};
    indirectTriples.push_back(it);
}

void displayQuadruples() {
    cout << "\nQuadruple Representation:" << endl;
    for (const auto &q : quadruples) {
        cout << q.op << "\t" << q.arg1 << "\t" << q.arg2 << "\t" << q.result << endl;
    }
}

void displayTriples() {
    cout << "\nTriple Representation:" << endl;
    for (size_t i = 0; i < triples.size(); i++) {
        cout << i << ") " << triples[i].op << "\t" << triples[i].arg1 << "\t" << triples[i].arg2 << endl;
    }
}

void displayIndirectTriples() {
    cout << "\nIndirect Triple Representation:" << endl;
    for (const auto &it : indirectTriples) {
        cout << it.index << ") " << it.triple.op << "\t" << it.triple.arg1 << "\t" << it.triple.arg2 << endl;
    }
}

int main() {
    // Example expressions: T1 = A + B, T2 = T1 * C
    generateIntermediateCode("+", "A", "B", "T1");
    generateIntermediateCode("*", "T1", "C", "T2");
    generateIntermediateCode("-", "T2", "D", "T3");
    generateIntermediateCode("/", "T3", "E", "T4");
    
    displayQuadruples();
    displayTriples();
    displayIndirectTriples();
    
    return 0;
}
