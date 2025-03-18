import subprocess

# C code to be compiled
c_code = """ 
#include <stdio.h>

int add(int a, int b) {
    return a + b;
}
"""

# Save C code to a file
with open("simple.c", "w") as f:
    f.write(c_code)

# Compile the C file to an object file
subprocess.run(["gcc", "-c", "simple.c", "-o", "simple.o"])

# Extract machine code using objdump
result = subprocess.run(["objdump", "-d", "simple.o"], capture_output=True, text=True)

# Print the machine code
print(result.stdout)
