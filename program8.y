%{
#include <stdio.h>
#include <stdlib.h>

int yylex(void);
void yyerror(const char *s);

double result;
%}

%union {
    double dval;
}

%token <dval> NUMBER

%type <dval> expr

%left '+' '-'
%left '*' '/'

%%

input:
      /* empty */
    | input line
    ;

line:
      '\n'
    | expr '\n'  { 
        printf("Result = %lf\n", $1); 
        result = $1; 
      }
    ;

expr:
      NUMBER          { $$ = $1; }
    | expr '+' expr   { $$ = $1 + $3; }
    | expr '-' expr   { $$ = $1 - $3; }
    | expr '*' expr   { $$ = $1 * $3; }
    | expr '/' expr   { 
        if ($3 == 0) {
            yyerror("division by zero");
            $$ = 0;
        } else {
            $$ = $1 / $3;
        }
      }
    | '(' expr ')'    { $$ = $2; }
    ;

%%

void yyerror(const char *s) {
    fprintf(stderr, "Error: %s\n", s);
}

int main(void) {
    printf("Enter expressions to evaluate or Ctrl+C to exit.\n");
    yyparse();
    return 0;
}

