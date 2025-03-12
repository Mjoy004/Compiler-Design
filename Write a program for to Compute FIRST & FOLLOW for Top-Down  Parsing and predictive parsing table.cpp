#include <iostream>
#include <map>
#include <set>
#include <vector>
#include <cctype>
#include <sstream>
using namespace std;

map<char, set<char>> first, follow;
map<char, vector<string>> grammar;
set<char> terminals, nonTerminals;

void computeFirst(char symbol);
void computeFollow(char symbol);
void constructParsingTable();

// Function to find FIRST of a non-terminal
void computeFirst(char symbol) {
    if (!isupper(symbol)) {
        first[symbol].insert(symbol);
        return;
    }

    for (string prod : grammar[symbol]) {
        if (prod == "ε") {
            first[symbol].insert('ε');
        } else {
            for (char ch : prod) {
                computeFirst(ch);
                first[symbol].insert(first[ch].begin(), first[ch].end());
                if (first[ch].find('ε') == first[ch].end()) break;
            }
        }
    }
}

// Function to compute FOLLOW set
void computeFollow(char symbol) {
    if (symbol == *nonTerminals.begin()) {
        follow[symbol].insert('$');
    }

    for (auto &[lhs, productions] : grammar) {
        for (string prod : productions) {
            size_t pos = prod.find(symbol);
            while (pos != string::npos) {
                if (pos + 1 < prod.size()) {
                    char next = prod[pos + 1];
                    follow[symbol].insert(first[next].begin(), first[next].end());
                    follow[symbol].erase('ε');
                    if (first[next].find('ε') != first[next].end()) {
                        follow[symbol].insert(follow[lhs].begin(), follow[lhs].end());
                    }
                } else {
                    if (symbol != lhs) follow[symbol].insert(follow[lhs].begin(), follow[lhs].end());
                }
                pos = prod.find(symbol, pos + 1);
            }
        }
    }
}

// Function to construct predictive parsing table
void constructParsingTable() {
    cout << "\nPredictive Parsing Table:\n";
    for (auto &[lhs, productions] : grammar) {
        for (string prod : productions) {
            set<char> firstSet;
            if (prod == "ε") {
                firstSet = follow[lhs];
            } else {
                for (char ch : prod) {
                    firstSet.insert(first[ch].begin(), first[ch].end());
                    if (first[ch].find('ε') == first[ch].end()) break;
                }
            }
            for (char terminal : firstSet) {
                if (terminal != 'ε') {
                    cout << lhs << " -> " << prod << " [ " << terminal << " ]\n";
                }
            }
        }
    }
}

int main() {
    int numProductions;
    cout << "Enter number of productions: ";
    cin >> numProductions;
    cin.ignore();

    cout << "Enter productions (e.g., A -> aB | ε):\n";
    for (int i = 0; i < numProductions; i++) {
        string line, lhs, rhs;
        getline(cin, line);
        stringstream ss(line);
        ss >> lhs;
        ss.ignore(3); // Ignore '->'
        while (getline(ss, rhs, '|')) {
            grammar[lhs[0]].push_back(rhs);
            for (char ch : rhs) {
                if (!isupper(ch) && ch != 'ε') terminals.insert(ch);
            }
        }
        nonTerminals.insert(lhs[0]);
    }

    cout << "\nComputing FIRST sets...\n";
    for (char nt : nonTerminals) computeFirst(nt);
    for (auto &[nt, firstSet] : first) {
        cout << "FIRST(" << nt << ") = { ";
        for (char ch : firstSet) cout << ch << " ";
        cout << "}\n";
    }

    cout << "\nComputing FOLLOW sets...\n";
    for (char nt : nonTerminals) computeFollow(nt);
    for (auto &[nt, followSet] : follow) {
        cout << "FOLLOW(" << nt << ") = { ";
        for (char ch : followSet) cout << ch << " ";
        cout << "}\n";
    }

    constructParsingTable();

    return 0;
}
