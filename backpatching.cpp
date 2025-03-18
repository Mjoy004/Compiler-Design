#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

// Structure to represent a list of addresses for backpatching
struct BackpatchList {
    vector<int> addresses;
};

// Class to simulate backpatching in three-address code (TAC)
class Backpatching {
public:
    vector<string> code;  // Stores the generated three-address code
    unordered_map<int, string> patchTable; // Stores jump locations for patching

    // Generate a label (line number) where the jump will occur
    int nextInstr() {
        return code.size();
    }

    // Emit an instruction and return its address
    void emit(string instruction) {
        code.push_back(instruction);
    }

    // Create a new backpatch list with a single entry
    BackpatchList makeList(int addr) {
        return BackpatchList{{addr}};
    }

    // Merge two backpatch lists
    BackpatchList merge(BackpatchList l1, BackpatchList l2) {
        l1.addresses.insert(l1.addresses.end(), l2.addresses.begin(), l2.addresses.end());
        return l1;
    }

    // Backpatch the given list of addresses with the target label
    void backpatch(BackpatchList &list, int target) {
        for (int addr : list.addresses) {
            code[addr] += " " + to_string(target); // Patch the jump address
        }
    }

    // Print generated TAC code
    void printCode() {
        for (int i = 0; i < code.size(); i++) {
            cout << i << ": " << code[i] << endl;
        }
    }
};

int main() {
    Backpatching compiler;

    // Example: Handling an "if (a < b) goto L1" statement
    int instr1 = compiler.nextInstr();
    compiler.emit("if a < b goto"); // This needs backpatching

    BackpatchList trueList = compiler.makeList(instr1);

    // Some intermediate code
    compiler.emit("c = c + 1");

    int instr2 = compiler.nextInstr();
    compiler.emit("goto"); // This also needs backpatching

    BackpatchList falseList = compiler.makeList(instr2);

    // Label L1 (target address for "if")
    int L1 = compiler.nextInstr();
    compiler.emit("L1: d = d + 2");

    // Backpatching
    compiler.backpatch(trueList, L1);
    compiler.backpatch(falseList, compiler.nextInstr());

    // Print the generated code
    compiler.printCode();

    return 0;
}
