%{
#include "y.tab.h"    
#include <stdlib.h>
%}

%%

[a-zA-Z_][a-zA-Z0-9_]*    return id;           
[0-9]+(\.[0-9]+)?         return num;           
[=+\-*/()]                return yytext[0];     
[ \t]+                   ;                      
\n                        return 0;             
.                         { printf("Unknown character: %s\n", yytext); } 

%%

int yywrap() {
    return 1;
}

