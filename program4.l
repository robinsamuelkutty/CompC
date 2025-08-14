%{
#include<stdio.h>
%}
%%
abc { printf("ABC"); }
. { printf("%s",yytext); }
\n { printf("\n"); }
%%
int main(){
	yylex();
	return 0;
}
int yywrap(){

}
