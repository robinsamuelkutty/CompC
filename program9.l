%{
#include "y.tab.h"
#include <stdlib.h>
%}

%%

[0-9]+          { yylval.num = atoi(yytext); return NUMBER; }
[ \t\n]+        ; // Ignore whitespace
"+"             return '+';
"-"             return '-';
"*"             return '*';
"/"             return '/';
"("             return '(';
")"             return ')';

.               { printf("Unknown character: %s\n", yytext); }

%%

int yywrap() {
    return 1;
}

