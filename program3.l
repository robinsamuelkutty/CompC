%{
#include<stdio.h>
int line_count=0;
int word_count=0;
int space_count=0;
int char_count=0;
FILE *yyin;
%}
%%
[ \t]+ { space_count+=yyleng; char_count+=yyleng; }  
\n {line_count++; char_count++; }
[A-Za-z0-9_]+ { word_count++;char_count+=yyleng; }
. { char_count++; }

%%
int main(int argc, char **argv){
	if(argc>1){
		FILE *file = fopen(argv[1],"r");
		if(!file){
			perror("could not open file");
			return 1;
		}
		yyin=file;
	}
	yylex();
	printf("\n ---- Analysis Result ----\n");
	printf("Lines: %d\n",line_count);
	printf("Words: %d\n",word_count);
	printf("Spaces: %d\n",space_count);
	printf("Characters: %d\n",char_count);
	return 0;
}
int yywrap(){

}
