%{
#include <stdio.h>

int vowel_count = 0;
int consonant_count = 0;
FILE *yyin;
%}

%%

[aeiouAEIOU]                           { vowel_count++; }
[bcdfghjklmnpqrstvwxyzBCDFGHJKLMNPQRSTVWXYZ] { consonant_count++; }
.                                      {  }

%%

int main(int argc, char **argv) {
    if (argc > 1) {
        yyin = fopen(argv[1], "r");
        if (!yyin) {
            perror("Could not open file");
            return 1;
        }
    }
    yylex();
    printf("Number of Vowels: %d\n", vowel_count);
    printf("Number of Consonants: %d\n", consonant_count);
    return 0;
}

int yywrap() {
    return 1;
}

