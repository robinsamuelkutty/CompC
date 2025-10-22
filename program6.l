%{
#include "y.tab.h"    // Token definitions from YACC
#include <stdlib.h>
%}

%%

[a-zA-Z_][a-zA-Z0-9_]*    return id;            // Identifiers
[0-9]+(\.[0-9]+)?         return num;           // Numbers (integers and floats)
[=+\-*/()]                return yytext[0];     // Single-character operators, now includes '='
[ \t]+                   ;                      // Ignore whitespace
\n                        return 0;             // End of input
.                         { printf("Unknown character: %s\n", yytext); } // Catch-all for invalid input

%%

int yywrap() {
    return 1;
}

