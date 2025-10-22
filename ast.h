// ast.h

#ifndef AST_H
#define AST_H

typedef struct ASTNode {
    char* type;
    struct ASTNode* left;
    struct ASTNode* right;
    int value; // For number literals
} ASTNode;

ASTNode* makeNode(char* type, ASTNode* left, ASTNode* right);
ASTNode* makeLeaf(int value);
void printAST(ASTNode* node, int level);

#endif

