#include "../src/binaryTree.h"

int main(int argc, char *argv[]){

    // Prints Syntax Error If There Is An Unexprected Argument
    if(argc < 2){
        fprintf( stderr, "Error: syntax error.\n" );
        return 1;
    }

    // Creates Tree With The Entered Expression
    struct node *root = createTree(argv[1]);

    // Traverses The Tree In Preorder
    preorderTraversal(root);
    printf("\n");

    // Frees The Tree
    freeTree(root);

    return 0;
}

void preorderTraversal(struct node *root){

    // Returns If The Root Is NULL
    if(root == NULL){
        return;
    }

    // Visits And Prints The Root Node With A Space In Between Data
    printf("%s ", root->data);

    // Recursively Traverses The Left Subtree
    preorderTraversal(root->left);

    // Recursively Traverses The Right Subtree
    preorderTraversal(root->right);
}
