#include <iostream>
#include <vector>
#include <set>
#include <map>
using namespace std;

map<char, set<char>> leading, trailing;
vector<string> productions;

void computeLeading(char nonTerminal) {
    for (const string &prod : productions) {
        if (prod[0] == nonTerminal) {
            for (size_t i = 1; i < prod.length(); i++) {
                if (isupper(prod[i])) {
                    leading[nonTerminal].insert(prod[i]);
                    break;
                } else {
                    leading[nonTerminal].insert(prod[i]);
                    break;
                }
            }
        }
    }
}

void computeTrailing(char nonTerminal) {
    for (const string &prod : productions) {
        if (prod[0] == nonTerminal) {
            for (int i = prod.length() - 1; i > 0; i--) {
                if (isupper(prod[i])) {
                    trailing[nonTerminal].insert(prod[i]);
                    break;
                } else {
                    trailing[nonTerminal].insert(prod[i]);
                    break;
                }
            }
        }
    }
}

int main() {
    int n;
    cout << "Enter the number of productions: ";
    cin >> n;
    cout << "Enter the productions (e.g., A=aB, B=b):" << endl;
    
    for (int i = 0; i < n; i++) {
        string prod;
        cin >> prod;
        productions.push_back(prod);
    }
    
    for (const string &prod : productions) {
        char nonTerminal = prod[0];
        computeLeading(nonTerminal);
        computeTrailing(nonTerminal);
    }
    
    cout << "\nLEADING and TRAILING sets:\n";
    for (const auto &entry : leading) {
        cout << "LEADING(" << entry.first << ") = { ";
        for (char c : entry.second) {
            cout << c << " ";
        }
        cout << "}\n";
    }
    
    for (const auto &entry : trailing) {
        cout << "TRAILING(" << entry.first << ") = { ";
        for (char c : entry.second) {
            cout << c << " ";
        }
        cout << "}\n";
    }
    
    return 0;
}
