%{
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// === AST Node Definition ===
typedef struct ASTNode {
    char* type;
    struct ASTNode* left;
    struct ASTNode* right;
    int value; // For number literals
} ASTNode;

ASTNode* makeNode(char* type, ASTNode* left, ASTNode* right);
ASTNode* makeLeaf(int value);
void printAST(ASTNode* node, int level);
void yyerror(const char* s);
int yylex();

ASTNode* root;  // Global root pointer for AST
%}

%union {
    int num;
    ASTNode* node;
}

%token <num> NUMBER
%type <node> expr term factor

%%

expr: expr '+' term       { $$ = makeNode("+", $1, $3); root = $$; }
    | expr '-' term       { $$ = makeNode("-", $1, $3); root = $$; }
    | term                { $$ = $1; root = $$; }
    ;

term: term '*' factor     { $$ = makeNode("*", $1, $3); }
    | term '/' factor     { $$ = makeNode("/", $1, $3); }
    | factor              { $$ = $1; }
    ;

factor: '(' expr ')'      { $$ = $2; }
      | NUMBER            { $$ = makeLeaf($1); }
      ;

%%

void yyerror(const char* s) {
    fprintf(stderr, "Syntax Error: %s\n", s);
}

ASTNode* makeNode(char* type, ASTNode* left, ASTNode* right) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = strdup(type);
    node->left = left;
    node->right = right;
    node->value = 0;
    return node;
}

ASTNode* makeLeaf(int value) {
    ASTNode* node = (ASTNode*)malloc(sizeof(ASTNode));
    node->type = strdup("NUM");
    node->left = node->right = NULL;
    node->value = value;
    return node;
}

void printAST(ASTNode* node, int level) {
    if (!node) return;
    for (int i = 0; i < level; ++i) printf("  ");
    if (strcmp(node->type, "NUM") == 0)
        printf("%s: %d\n", node->type, node->value);
    else {
        printf("%s\n", node->type);
        printAST(node->left, level + 1);
        printAST(node->right, level + 1);
    }
}

