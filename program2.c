%{
#include <stdio.h>
#include <string.h>
%}


keyword     (int|float|char|double|if|else|for|while|do|return|void|main)
identifier  [a-zA-Z_][a-zA-Z0-9_]*
number      [0-9]+
operator    [+\-*/%]
relop       (<=|>=|==|!=|<|>)
symbol      [;{}(),]

%%


{keyword}      { printf("Keyword: %s\n", yytext); }
{identifier}   { printf("Identifier: %s\n", yytext); }
{number}       { printf("Number: %s\n", yytext); }
{operator}     { printf("Arithmetic Operator: %s\n", yytext); }
{relop}        { printf("Relational Operator: %s\n", yytext); }
{symbol}       { printf("Special Symbol: %s\n", yytext); }
[ \t\n]+       { /* Ignore whitespace */ }
.              { printf("Unknown: %s\n", yytext); }

%%

int main()
{
    printf("Lexical Analysis Output:\n\n");
    yylex();  
    return 0;
}

int yywrap()
{
    return 1;
}
