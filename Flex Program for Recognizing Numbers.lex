%{
#include <stdio.h>
%}

%%

[0-9]+           { printf("Integer: %s\n", yytext); }
[0-9]+\.[0-9]+   { printf("Float: %s\n", yytext); }
.                ; // Ignore other characters

%%

int main() {
    yylex();
    return 0;
}

int yywrap() {
    return 1;
}
