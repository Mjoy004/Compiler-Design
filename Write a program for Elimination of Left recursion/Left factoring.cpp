#include <iostream>
#include <vector>
#include <string>
#include <sstream>
using namespace std;

// Function to eliminate left recursion
void eliminateLeftRecursion(string nonTerminal, vector<string> productions) {
    vector<string> alpha, beta;
    for (string prod : productions) {
        if (prod[0] == nonTerminal[0]) {
            alpha.push_back(prod.substr(1));
        } else {
            beta.push_back(prod);
        }
    }
    
    if (!alpha.empty()) {
        string newNonTerminal = nonTerminal + "'";
        cout << nonTerminal << " -> ";
        for (size_t i = 0; i < beta.size(); i++) {
            cout << beta[i] << newNonTerminal;
            if (i != beta.size() - 1) cout << " | ";
        }
        cout << endl;

        cout << newNonTerminal << " -> ";
        for (size_t i = 0; i < alpha.size(); i++) {
            cout << alpha[i] << newNonTerminal << " | ";
        }
        cout << "ε" << endl;
    } else {
        cout << nonTerminal << " -> ";
        for (size_t i = 0; i < productions.size(); i++) {
            cout << productions[i];
            if (i != productions.size() - 1) cout << " | ";
        }
        cout << endl;
    }
}

// Function to perform left factoring
void leftFactor(string nonTerminal, vector<string> productions) {
    string prefix = productions[0];
    for (size_t i = 1; i < productions.size(); i++) {
        size_t j = 0;
        while (j < prefix.length() && j < productions[i].length() && prefix[j] == productions[i][j]) {
            j++;
        }
        prefix = prefix.substr(0, j);
    }

    if (prefix.empty()) {
        cout << nonTerminal << " -> ";
        for (size_t i = 0; i < productions.size(); i++) {
            cout << productions[i];
            if (i != productions.size() - 1) cout << " | ";
        }
        cout << endl;
        return;
    }

    string newNonTerminal = nonTerminal + "'";
    cout << nonTerminal << " -> " << prefix << newNonTerminal << endl;
    cout << newNonTerminal << " -> ";
    for (size_t i = 0; i < productions.size(); i++) {
        if (productions[i].substr(0, prefix.length()) == prefix) {
            string suffix = productions[i].substr(prefix.length());
            cout << (suffix.empty() ? "ε" : suffix);
            if (i != productions.size() - 1) cout << " | ";
        }
    }
    cout << endl;
}

int main() {
    string nonTerminal, input;
    vector<string> productions;
    cout << "Enter Non-Terminal: ";
    cin >> nonTerminal;
    cin.ignore();
    cout << "Enter Productions (separated by '|'): ";
    getline(cin, input);

    stringstream ss(input);
    string token;
    while (getline(ss, token, '|')) {
        productions.push_back(token);
    }

    cout << "\nAfter Eliminating Left Recursion:" << endl;
    eliminateLeftRecursion(nonTerminal, productions);

    cout << "\nAfter Left Factoring:" << endl;
    leftFactor(nonTerminal, productions);

    return 0;
}
