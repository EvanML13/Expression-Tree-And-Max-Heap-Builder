#include "../src/binaryTree.h"

int main(int argc, char *argv[]){

    // Prints Syntax Error If There Is An Unexprected Argument
    if(argc < 2){
        fprintf( stderr, "Error: syntax error.\n" );
        return 1;
    }

    // Creates Tree With The Entered Expression
    struct node *root = createTree(argv[1]);

    // Traverses The Tree In Inorder
    inorderTraversal(root);
    printf("\n");

    // Frees The Tree
    freeTree(root);

    return 0;
}

void inorderTraversal(struct node *root){
    
    // Returns If The Root Is NULL
    if(root == NULL){
        return;
    }

    // Ensures The A Left Or Right Child Exists
    if(root->left != NULL || root->right != NULL){
        printf("(");
    }

    // Traverses The Left Subtree
    inorderTraversal(root->left);
    printf("%s", root->data);

    // Traverses The Right Subtree
    inorderTraversal(root->right);
        
    // Ensures The A Left Or Right Child Exists
    if(root->left != NULL || root->right != NULL){
        printf(")");
    }   
}
