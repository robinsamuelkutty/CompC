%{
#include "y.tab.h"
%}

%%

[0-9]+(\.[0-9]+)?  {
    yylval.dval = atof(yytext);
    return NUMBER;
}
[ \t]               ;  // skip whitespace
\n                  return '\n';
"+"                 return '+';
"-"                 return '-';
"*"                 return '*';
"/"                 return '/';
"("                 return '(';
")"                 return ')';

.                   { printf("Unknown character: %s\n", yytext); }

%%

int yywrap() { return 1; }

