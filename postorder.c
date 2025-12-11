#include "../src/binaryTree.h"

int main(int argc, char *argv[]){
    
    // Prints Syntax Error If There Is An Unexprected Argument
    if(argc < 2){
        fprintf( stderr, "Error: syntax error.\n" );
        return 1;        
    }

    // Creates Tree With The Entered Expression
    struct node *root = createTree(argv[1]);

    // Traverses The Tree In Postorder
    postorderTraversal(root);
    printf("\n");

    // Frees The Tree
    freeTree(root);

    return 0;
}

void postorderTraversal(struct node *root){

    // Returns If The Root Is NULL
    if(root == NULL){
        return;
    }

    // Traverses The Left Subtree
    postorderTraversal(root->left);

    // Traverses The Right Subtree
    postorderTraversal(root->right);

    // Visits And Prints The Root Node
    printf("%s ", root->data);

}
