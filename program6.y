%{
    #include <stdio.h>
    int valid = 1;
    int yylex(void);
    void yyerror(const char*);
%}

%token num id

%%

start : id '=' s       
      | s              
      ;

s : id x
  | num x
  | '-' num x
  | '(' s ')' x
  ;

x : '+' s
  | '-' s
  | '*' s
  | '/' s
  | /* empty */
  ;

%%

void yyerror(const char *s) {
    valid = 0;
    printf("\nInvalid expression!\n");
}

int main() {
    printf("Enter the expression:\n");
    yyparse();
    if(valid) {
        printf("\nValid expression!\n");
    }
    return 0;
}

