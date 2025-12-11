#include "../src/binaryTree.h"

struct node *createNode(char *data){

    // Allocates Memory For A New Node
    struct node *newNode = malloc(sizeof(struct node));
    if(newNode == NULL){
        fprintf(stderr, "Error: syntax error.\n" );
        return NULL;
    }

    // Assigns Data To The New Node, Sets Its Left And Right Subchildren To NULL, And Returns It
    strcpy(newNode->data, data);
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

bool isValueValid(char *value){

    // If The Value Is Not 4 Characters Long (Y.YY) It Is Invalid
    if (strlen(value) != 4) {
        return false;
    }

    // If The Value Is In The Correct Format (Y.YY) Return True
    if (isdigit(value[0]) && value[1] == '.' && isdigit(value[2]) && isdigit(value[3])) {
        return true;
    }

    return false;
}

bool isOperatorValid(char operator){

    // If The Operator Is One Of +, -, *, Or / Return True
    if(operator == '+' || operator == '-' || operator == '*' || operator == '/'){
        return true;
    }

    return false;
}

bool isVariableValid(char *variableName){

    // If Variable Name Is One Of x1 - x9 Return True
    if(strlen(variableName) == 2 && variableName[0] == 'x' && isdigit(variableName[1]) && variableName[1] != '0'){
        return true;
    }

    return false;
}

void freeTree(struct node *root){
    
    // First Checks If The Root Is Empty
    if(root == NULL){
        return;
    }

    // Recursively Frees The Left And Right Subtrees
    freeTree(root->left);
    freeTree(root->right);

    // Frees The Root Node 
    free(root);
}

char *stripOuterBrackets(char *expression){

    int length = strlen(expression);
    int depth = 0;
    bool wrappedInBrackets = true;
    
    // Returns NULL If The Expression Is Not Wrapped In Brackets
    if(expression[0] != '(' || expression[length - 1] != ')'){
        return NULL;
    }

    // Iterates Through The Expression
    for(int i = 0; i < length; i++){

        // Increases Depth If An Opening Bracket ( Is Found
        if(expression[i] == '('){
            depth++;
        } 
        // Decreases Depth If A Closing Bracket ) Is Found
        else if(expression[i] == ')'){
            depth--;

            // If A Closing Bracket Not A The End Of The Expression Closes The First Opening Bracket The Expression Is Not Wrapped In Brackets
            if(depth == 0 && i < length - 1){
                wrappedInBrackets = false;
                break;
            }
        }
    }

    // If The Expression Is Not Wrapped In Brackets Return NULL
    if(!wrappedInBrackets){
        return NULL;
    }

    // Creates A New String Without The Outer Brackets And Returns It
    char *strippedExpression = malloc(length - 1);
    strncpy(strippedExpression, expression + 1, length - 2);
    strippedExpression[length - 2] = '\0';
    return strippedExpression;
}

int findRootIndex(char *expression){

    int rootIndex;
    int length = strlen(expression);
    int inBrackets = 0;

    // Strips The Outer Brackets To Return The Inner Expression
    char *innerExpression = stripOuterBrackets(expression);

    // Finds The Root Of The Inner Expression And Returns It  
    if(innerExpression != NULL){
        rootIndex = findRootIndex(innerExpression);

        // Frees The Allocated Memory For The Inner Expression
        free(innerExpression); 

        return rootIndex + 1; // Adjusts The Index To Account For The Removed Brackets
    }

    for(int i = 0; i < length; i++){

        // Gets The Current Character
        char currentChar = expression[i];

        // Increases The inBrackets Counter If An Opening Bracket ( Is Found
        if(currentChar == '('){
            inBrackets++;
        }
        // Decreases The inBrackets Counter If A Closing Bracket ) Is Found
        else if(currentChar == ')'){
            inBrackets--;
        }
        // If The Current Character Is An Operator And Not In Brackets Return Its Index
        else if(inBrackets == 0 && isOperatorValid(currentChar)){
            return i;
        }    
    }

    // -1 Is Returned If No Root Operator Is Found
    return -1;
}

struct node *createTree(char *expression){

    // Strips The Outer Brackets To Get The Inner Expression
    char *innerExpression = stripOuterBrackets(expression);
    
    if(innerExpression != NULL){
        // Recursively Creates The Tree From The Inner Expression
        struct node *result = createTree(innerExpression);
        free(innerExpression);
        return result;
    }

    // Deals With The Base Case Where The Expression Is A Variable Or Number And A Leaf Node Can Be Created
    if(isVariableValid(expression) || isValueValid(expression)){
        return createNode(expression);
    }

    // Finds The Root Index
    int rootIndex = findRootIndex(expression);
    if(rootIndex == -1){
        return NULL;
    }

    // Creates A String For The Root Opperator
    char rootOpperator[2];
    rootOpperator[0] = expression[rootIndex];
    rootOpperator[1] = '\0';

    // Adds The Root Opperator To The Tree
    struct node *root = createNode(rootOpperator);

    // Gets The Lengths Of The Left And Right Subtrees
    int leftSubtreeLength = rootIndex;
    int rightSubtreeLength = strlen(expression) - rootIndex - 1;

    // Allocates Memory For The Left And Right Subtree Expressions
    char *leftSubtree = malloc(leftSubtreeLength + 1);
    char *rightSubtree = malloc(rightSubtreeLength + 1);

    // Copies The Left Subtree Expression A String
    strncpy(leftSubtree, expression, leftSubtreeLength);
    leftSubtree[leftSubtreeLength] = '\0';

    // Copies The Right Subtree Expression A String
    strncpy(rightSubtree, expression + rootIndex + 1, rightSubtreeLength);
    rightSubtree[rightSubtreeLength] = '\0';

    // Recursively Creates The Left And Right Subtrees
    root->left = createTree(leftSubtree);
    root->right = createTree(rightSubtree);

    // Frees All Strings If Either Of The Subtrees Is Empty
    if(root->left == NULL || root->right == NULL){
        free(leftSubtree);
        free(rightSubtree);
        freeTree(root);
        return NULL;
    }

    // Frees Temporary Strings
    free(leftSubtree);
    free(rightSubtree);

    return root;
}
