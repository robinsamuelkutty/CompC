#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>

int main(void) {
    FILE *fp;
    char ch;
    int i,j=0,k=0;
    int opIndex = 0;
    char bufferop[100];
	char buffer[100];
    char operator[] = "*%+-";
    char keyword[100][100]={"int","float","if","else","return","char"};
    fp = fopen("text.txt", "r");
    
    while ((ch = fgetc(fp)) != EOF) {
        for (i = 0; i < strlen(operator); i++) {
            if (ch == operator[i]) {
                bufferop[opIndex++] = ch;
                break; 
            }
			
        }
		
    }
	buffer[j]='\0';		
    bufferop[opIndex] = '\0'; 
    printf("Operators in the file: ");
    for (i = 0; i < opIndex; i++) {
        printf("%c ", bufferop[i]);
    }
    printf("\n");
	printf("Keywords in the file: ");
	ch=getc(fp);
	while(isalnum(ch) || ch=="_"){
		if(strcmp(keyword,buffer))
		buffer[k++]=ch;
		ch=getc(fp);
	}
	buffer[k]='/0'
	
	for( i=0;i<j;i++){
		if(strcmp(keyword[i],buffer)){
			printf("%s ",buffer);
			
			
		}
	}
    fclose(fp);
    return 0;
}

