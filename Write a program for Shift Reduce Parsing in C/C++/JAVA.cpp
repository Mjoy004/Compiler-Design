#include <iostream>
#include <stack>
#include <vector>

using namespace std;

bool shiftReduceParse(string input) {
    stack<string> parseStack;
    vector<string> grammar = {"E+E", "E*E", "(E)", "id"};

    string action;
    int index = 0;

    cout << "Stack\t\tInput\t\tAction" << endl;
    cout << "--------------------------------------" << endl;

    while (index < input.size() || !parseStack.empty()) {
        // Print current stack and remaining input
        string stackContent;
        stack<string> tempStack = parseStack;
        vector<string> reversedStack;
        while (!tempStack.empty()) {
            reversedStack.push_back(tempStack.top());
            tempStack.pop();
        }
        for (auto it = reversedStack.rbegin(); it != reversedStack.rend(); ++it) {
            stackContent += *it;
        }
        cout << stackContent << "\t\t" << input.substr(index) << "\t\t";

        // Shift operation
        if (index < input.size()) {
            string shiftSymbol(1, input[index]);
            parseStack.push(shiftSymbol);
            index++;
            cout << "Shift '" << shiftSymbol << "'" << endl;
            continue;
        }

        // Reduce operation
        bool reduced = false;
        for (const string &rule : grammar) {
            string topElements;
            stack<string> temp = parseStack;
            vector<string> tempVec;
            while (!temp.empty()) {
                tempVec.push_back(temp.top());
                temp.pop();
            }
            for (auto it = tempVec.rbegin(); it != tempVec.rend(); ++it) {
                topElements += *it;
            }

            size_t pos = topElements.rfind(rule);
            if (pos != string::npos) {
                // Reduce the stack
                for (size_t i = 0; i < rule.size(); i++) {
                    parseStack.pop();
                }
                parseStack.push("E");
                cout << "Reduce '" << rule << "' → 'E'" << endl;
                reduced = true;
                break;
            }
        }

        if (!reduced) {
            cout << "Parsing Failed!" << endl;
            return false;
        }

        if (parseStack.size() == 1 && parseStack.top() == "E" && index == input.size()) {
            cout << "Accepted: Successfully parsed!" << endl;
            return true;
        }
    }

    cout << "Parsing Failed!" << endl;
    return false;
}

int main() {
    string input;
    cout << "Enter input string: ";
    cin >> input;
    
    if (!shiftReduceParse(input)) {
        cout << "The given input does not match the grammar." << endl;
    }

    return 0;
}
