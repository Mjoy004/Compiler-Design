%{
#include <stdio.h>
%}

%%

"+"   { printf("Operator: Addition\n"); }
"-"   { printf("Operator: Subtraction\n"); }
"*"   { printf("Operator: Multiplication\n"); }
"/"   { printf("Operator: Division\n"); }
.     ; // Ignore other characters

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
