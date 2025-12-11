#ifndef BINARYTREE_H
#define BINARYTREE_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>

// Binary Tree Structure
struct node{
    char data[5];
    struct node *left;
    struct node *right;
};

// Function To Create A New Node On The Binary Tree
struct node *createNode(char *data);
// Function To Create The Binary Tree From A Given Expression
struct node *createTree(char *expression);

// Function To Find The Root Index Of The Expression
int findRootIndex(char *expression);
// Function To Strip The Outer Brackets Of The Expression
char *stripOuterBrackets(char *expression);

// Function To Validate A Value
bool isValueValid(char *value);
// Function To Validate A Operator
bool isOperatorValid(char operator);
// Function To Validate A Variable Name
bool isVariableValid(char *variableName);

// Function To Free The Binary Tree
void freeTree(struct node *root);

// Function To Traverse The Binary Tree Inorder 
void inorderTraversal(struct node *root);
// Function To Traverse The Binary Tree In Preorder
void preorderTraversal(struct node *root);
// Function To Traverse The Binary Tree In Postorder
void postorderTraversal(struct node *root);

// Struct To Hold The 10 Possible Variables Entered Along With A Expression
struct variable{
    char name[3];
    double value;
};

// Function To Parse Variables Entered On argv[2] Into The Binary Tree Expression, Returning The Number Of Variables 
int parseVariables(char *assignments, struct variable variables[]); 
// Function To Return The Value Of A Given Variable
double getVariableValue(char *name, struct variable variables[], int count);

// Function To Calculate The Value Of The Binary Tree Expression With Or Without Variable Declarations
double calculateTree(struct node *root, struct variable variables[], int count);

#endif // BINARYTREE_H
