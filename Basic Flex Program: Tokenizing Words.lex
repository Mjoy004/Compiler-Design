%{
#include <stdio.h>
%}

%%

[a-zA-Z]+    { printf("Word: %s\n", yytext); }
[^a-zA-Z\n]  ;  // Ignore non-word characters

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
