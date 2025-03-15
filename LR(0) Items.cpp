#include <iostream>
#include <vector>
#include <set>
#include <map>
#include <queue>
#include <string>

using namespace std;

struct Item {
    string lhs;
    string rhs;
    int dotPosition;
};

struct State {
    set<Item> items;
};

vector<string> productions;
vector<State> states;
map<pair<int, char>, int> transitions;
set<char> symbols;

bool itemExistsInState(const set<Item>& items, const Item& item) {
    return items.find(item) != items.end();
}

set<Item> closure(set<Item> I) {
    queue<Item> q;
    for (auto item : I) {
        q.push(item);
    }
    while (!q.empty()) {
        Item current = q.front();
        q.pop();
        if (current.dotPosition < current.rhs.length()) {
            char nextSymbol = current.rhs[current.dotPosition];
            for (string production : productions) {
                if (production[0] == nextSymbol) {
                    Item newItem = {production.substr(0, 1), production.substr(2), 0};
                    if (!itemExistsInState(I, newItem)) {
                        I.insert(newItem);
                        q.push(newItem);
                    }
                }
            }
        }
    }
    return I;
}

set<Item> gotoFunction(set<Item> I, char X) {
    set<Item> J;
    for (auto item : I) {
        if (item.dotPosition < item.rhs.length() && item.rhs[item.dotPosition] == X) {
            J.insert({item.lhs, item.rhs, item.dotPosition + 1});
        }
    }
    return closure(J);
}

void constructLR0Items() {
    set<Item> startState;
    startState.insert({productions[0].substr(0, 1), productions[0].substr(2), 0});
    startState = closure(startState);
    states.push_back({startState});
    
    queue<int> q;
    q.push(0);
    
    while (!q.empty()) {
        int stateIndex = q.front();
        q.pop();
        
        set<char> seenSymbols;
        for (auto item : states[stateIndex].items) {
            if (item.dotPosition < item.rhs.length()) {
                seenSymbols.insert(item.rhs[item.dotPosition]);
            }
        }
        
        for (char X : seenSymbols) {
            set<Item> newStateItems = gotoFunction(states[stateIndex].items, X);
            if (!newStateItems.empty()) {
                bool exists = false;
                int existingIndex = 0;
                
                for (int i = 0; i < states.size(); i++) {
                    if (states[i].items == newStateItems) {
                        exists = true;
                        existingIndex = i;
                        break;
                    }
                }
                
                if (!exists) {
                    states.push_back({newStateItems});
                    existingIndex = states.size() - 1;
                    q.push(existingIndex);
                }
                
                transitions[{stateIndex, X}] = existingIndex;
            }
        }
    }
}

void printLR0Items() {
    cout << "\nCanonical Collection of LR(0) Items:\n";
    for (size_t i = 0; i < states.size(); i++) {
        cout << "State " << i << ":\n";
        for (auto item : states[i].items) {
            cout << item.lhs << " -> " << item.rhs.substr(0, item.dotPosition) << "." << item.rhs.substr(item.dotPosition) << "\n";
        }
        cout << "-------------------\n";
    }
}

int main() {
    int n;
    cout << "Enter the number of productions: ";
    cin >> n;
    cout << "Enter the productions (e.g., S=AB, A=a):\n";
    
    for (int i = 0; i < n; i++) {
        string prod;
        cin >> prod;
        productions.push_back(prod);
        for (char c : prod) {
            if (!isupper(c) && c != '=' && c != '|') {
                symbols.insert(c);
            }
        }
    }
    
    constructLR0Items();
    printLR0Items();
    
    return 0;
}
