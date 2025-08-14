#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

int isKeyword(char buffer[]) 
{
	char Keyword[34][10] =
	{"auto", "break", "case", "char", "const", "continue", "default", "do", "double", "else", "enum", "extern", 
	"float", "for", "goto","if", "int", "long", "register", "return", "short", "signed", "sizeof", "static", "struct", 
	"switch", "typdef", "union", "unsigned", "void", "volatile", "while", "printf", "scanf"};
	
	int i,flag =0;
	for(i=0;i<34;i++)
	{
		if(strcmp(Keyword[i],buffer)==0)
		{
			flag=1;
			break;
		}
	}
	return flag;
}

void main()
{
	char ch,ch1, buffer[50], operator[]="+-*/%";
	FILE *fp,*fp2;
	int i, j=0, l=1, index = 1,z;
	char arr[1000][3],dig[20];
	fp=fopen("input.txt", "r");
	fp2=fopen("output.txt", "w+");
	if(fp==NULL)
	{
		printf("Error while opening file\n");
		exit(0);
	}
	else
	{
		printf("Lexeme: \t L.no:\t Token:");
		fprintf(fp2,"Lexeme: \t L.no:\t Token:");
		while((ch=fgetc(fp))!=EOF)
		{
			for(i=0;i<5;++i)
			{
				if(ch==operator[i])
				{
					printf("\n%c \t\t %d\t Arith OP ", ch,l);
					//fprintf(fp2,"\n%c \t\t %d\t arithmetic operator ", ch,l);
					break;
				}
			}
			if(i==5)
			{
				if(isalnum(ch))
				{
					if(isdigit(ch) && j==0)
					{ 
						//printf("\n%c \t\t %d\t number ", ch,l);
						//fprintf(fp2,"\n%c \t\t %d\t number ", ch,l);
						j=0;
					}
					else 
					{
						buffer[j++] = ch;
						ch1= fgetc(fp);
						if(isalnum(ch1))
							fseek(fp, -1, SEEK_CUR);
						else 
						{
							fseek (fp,-1,SEEK_CUR);
							buffer[j]='\0';
							//printf("%s",buffer);
							if(isKeyword(buffer)==1)
							{
								if(strcmp(buffer, "printf")==0){
								while((ch=fgetc(fp))!='\n'){
								
								}
								}
								printf("\n%s \t\t %d \t keyword ", buffer, l);
								//fprintf(fp2,"\n%s \t\t %d \t keyword ", buffer, l);
								j=0;
							}
							else
							{
								if(strcmp(buffer, "main")==0)
								{
								
								/*printf("\n%s \t\t %d\t Identifier", buffer, l);
								fprintf(fp2,"\n%s \t\t %d\t identifier", buffer, index);
								index++;*/
								}
								else
								{
								fseek(fp2, SEEK_SET, 0);
								char a[50], b[50], c[50], ch2, ch3;
								int flag1 = 0;
								while(!feof(fp2)){
								fscanf(fp2, "%s\t%s\t%s", a, b, c);
								if(strcmp(a, buffer) == 0){
								flag1 = 1;
								break;
								}
								}
								//printf("\n%s\n", b);
								if(flag1==0){
								ch2 = fgetc(fp);
								if(ch2=='=')
								{
									z=0;
									
									while(isdigit(ch3 = fgetc(fp)))
										dig[z++]=ch3;
									dig[z]='\0';
									fprintf(fp2,"\n%s \t\t %d\t identifier, %s", buffer, index, dig);
									fseek(fp,-z,SEEK_CUR);
								}
								else{
								fprintf(fp2,"\n%s \t\t %d\t identifier", buffer, index);
								}
								printf("\n%s \t\t %d\t Identifier, %d", buffer, l, index);	
								index++;
								}
								else{
								printf("\n%s \t\t %d\t Identifier, %s", buffer, l, b);
								}
								}
								j=0;
							}
						}
					}
				}
				if(ch=='<')
				{
					ch1= fgetc(fp);
					if(ch1=='=')
					{
						printf("\n%c%c \t\t %d \t Relop LE",ch,ch1,l);
						//fprintf(fp2,"\n%c%c \t\t %d \t relational operator",ch,ch1,l);
					}
					else
					{
						fseek(fp,-1,SEEK_CUR);
						printf("\n%c \t\t %d \t RelOP LT", ch,l);
						//fprintf(fp2,"\n%c \t\t %d \t relational operator", ch,l);
					}
				}
				else if(ch=='>')
				{
					ch1= fgetc(fp);
					if(ch1=='=')
					{
						printf("\n%c%c \t\t %d \t Relop GE",ch,ch1,l);
						//fprintf(fp2,"\n%c%c \t\t %d \t relational operator",ch,ch1,l);
					}
					else
					{
						fseek(fp,-1,SEEK_CUR);
						printf("\n%c \t\t %d \t Relop GT", ch,l);
						//fprintf(fp2,"\n%c \t\t %d \t relational operator", ch,l);
					}
				}
				else if(ch=='=')
				{
					ch1=fgetc(fp);
					if(ch1=='=') 
					{
						printf("\n%c%c \t\t %d \t Relop EQ", ch, ch1, l);
						//fprintf(fp2,"\n%c%c \t\t %d \t relational operator", ch, ch1, l);
					}
					else
					{
						fseek(fp, -1, SEEK_CUR);
						printf("\n%c \t\t %d \t Assgn OP, EQ",ch,l);
						//fprintf(fp2,"\n%c \t\t %d \t assignment operator",ch,l);
					}
				}
				if(ch=='\n'){
					l++;
				}
			}
		}
	}
	printf("\n");
}



