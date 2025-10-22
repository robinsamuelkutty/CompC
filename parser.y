%{
#include <stdio.h>
int valid = 1;
int yylex(void);  
void yyerror(const char *s);
%}

%token digit letter

%%

start : letter s
      ;

s : letter s
  | digit s
  | /* empty */
  ;

%%

void yyerror(const char *s)
{
    printf("\n%s", s);
    valid = 0;
}

int main()
{
    printf("\nEnter a name to be tested for identifier: ");
    yyparse();
    if(valid)
        printf("\nIt is an identifier!\n");
    else
        printf("\nIt is not an identifier!\n");
    return 0;
}

