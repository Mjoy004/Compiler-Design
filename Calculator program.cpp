#include <iostream>
using namespace std;

int main() {
    char op;
    double num1, num2, result;

    cout << "Enter an operator (+, -, *, /): ";
    cin >> op;

    cout << "Enter two numbers: ";
    cin >> num1 >> num2;

    switch (op) {
        case '+': result = num1 + num2; break;
        case '-': result = num1 - num2; break;
        case '*': result = num1 * num2; break;
        case '/': 
            if (num2 != 0)
                result = num1 / num2;
            else {
                cout << "Error! Division by zero.\n";
                return 1;
            }
            break;
        default: 
            cout << "Invalid operator!\n";
            return 1;
    }

    cout << "Result: " << result << endl;
    return 0;
}
