#include <iostream>
#include <stack>
#include <vector>
#include <string>
using namespace std;

struct Production {
    string lhs;
    string rhs;
};

vector<Production> grammar = {
    {"E", "E+T"},
    {"E", "T"},
    {"T", "T*F"},
    {"T", "F"},
    {"F", "(E)"},
    {"F", "id"}
};

bool canReduce(string &stackContent, string &reducedTo) {
    for (auto &prod : grammar) {
        if (stackContent.size() >= prod.rhs.size() &&
            stackContent.substr(stackContent.size() - prod.rhs.size()) == prod.rhs) {
            stackContent.erase(stackContent.size() - prod.rhs.size());
            stackContent += prod.lhs;
            reducedTo = prod.lhs;
            return true;
        }
    }
    return false;
}

void shiftReduceParse(string input) {
    stack<char> parseStack;
    string stackContent = "";
    int i = 0;
    cout << "Stack\tInput\tAction" << endl;
    while (i < input.size() || !stackContent.empty()) {
        if (i < input.size()) {
            parseStack.push(input[i]);
            stackContent += input[i];
            cout << stackContent << "\t" << input.substr(i + 1) << "\tShift " << input[i] << endl;
            i++;
        }
        
        string reducedTo;
        while (canReduce(stackContent, reducedTo)) {
            cout << stackContent << "\t" << input.substr(i) << "\tReduce to " << reducedTo << endl;
        }
    }
    if (stackContent == "E") {
        cout << "Accepted: Successfully parsed input!" << endl;
    } else {
        cout << "Rejected: Parsing failed!" << endl;
    }
}

int main() {
    string input;
    cout << "Enter input string (e.g., id+id*id): ";
    cin >> input;
    shiftReduceParse(input);
    return 0;
}
