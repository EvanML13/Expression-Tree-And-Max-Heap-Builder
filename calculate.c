#include "../src/binaryTree.h"

int main(int argc, char *argv[]){

    // Prints Syntax Error If There Is An Unexprected Argument
    if(argc < 2){
        fprintf( stderr, "Error: syntax error \n" );
        return 1;
    }

    // Creates Struct Of The Max Amount Of Variables That Could Be Used 
    struct variable variables[10];
    int variablesCount = 0;
    
    // Parses Variables If They Are Added In The Command Line
    if(argc >= 3){
        variablesCount = parseVariables(argv[2], variables);
        if(variablesCount == -1){
            return 1;
        }
    }

    // Creates Tree With The Entered Expression
    struct node *root = createTree(argv[1]);
    if(root == NULL){
        fprintf(stderr, "Error: syntax error.\n");
        return 1;    
    }
    
    // Calculates And Prints The Result
    double result = calculateTree(root, variables, variablesCount);

    // End The Program If An Error Occurs
    if(result == -999999){
        freeTree(root);
        return 1;
    }

    // Round The Result To Two Decmales 
    printf("%.2f\n", result);

    freeTree(root);
    return 0;
}

int parseVariables(char* assignments, struct variable variables[]){

    int count = 0;

    // Splits The String By ; Which We Know Will Be At The End Of Each Varaible Declaration
    char *ptr = strtok(assignments, ";");

    // Itterates Through Each Variable As Long As There Is No More Than 10
    while(ptr != NULL && count < 10){
        
        int nameLength;

        // Finds The Index Of The Equals Sign, Error If There Is No Equals Sign
        char *equalSign = strchr(ptr, '=');
        if(equalSign == NULL){
            fprintf(stderr, "Error: syntax error.\n");
            return -1;
        }

        // We Know The Variable Name Will Be To The Left Of The Equal Sign And Should Be Exactly 2 Charcters For It To Be Valid
        nameLength = equalSign - ptr;
        if(nameLength != 2){
            fprintf(stderr, "Error: syntax error.\n"); 
            return -1;   
        }

        // Adds The Variable Name To The Struct For The Count
        strncpy(variables[count].name, ptr, nameLength);
        variables[count].name[nameLength] = '\0';

        // Checks If The Variable Is Valid
        if(!isVariableValid(variables[count].name)){
           fprintf(stderr, "Error: syntax error.\n");  
           return -1;
        }

        // Gets The Value Of The Variable (Beyond The Equals Sign) And Verifies It
        char *value = equalSign + 1;
        if(!isValueValid(value)){
           fprintf(stderr, "Error: syntax error.\n");
           return -1; 
        }
        
        // Converts The String Value Into A Float
        variables[count].value = atof(value); 

        count++;

        // Moves To The Next Variable 
        ptr = strtok(NULL, ";");
    }
    return count;
}

double getVariableValue(char *name, struct variable variables[], int count){

    // Itterates Through Each Variable
    for(int i = 0; i < count; i++){

        // Once The Variable Name Is Found Return The Value
        if(strcmp(name, variables[i].name) == 0){
            return variables[i].value;
        }
    }
    
    // Prints Undefined Error If The Value For The Variable Is Not Found
    fprintf( stderr, "Error: undefined argument.\n");
    return -999999;
}

double calculateTree(struct node *root, struct variable variables[], int count){

    // Returns Invalid Value If There Is No Values
    if(root == NULL){
        return -999999;
    }

    // If The Value Is A Valid Leaf Node
    if(root->left == NULL && root->right == NULL){
        
        // If The Leaf Node Is A Variable Get The Value Of The Variable And Return It
        if(isVariableValid(root->data)){
            return getVariableValue(root->data, variables, count);
        } 

        // If The Leaf Node Is A Value Turn It Into A Float And Return It
        if(isValueValid(root->data)){
            return atof(root->data);
        }

        fprintf(stderr, "Error: syntax error.\n");
        return -999999;
    }

    // Recursivly Calculates The Values Of The Left And Right Subtrees
    double leftValue = calculateTree(root->left, variables, count);
    if(leftValue == -999999){
        return -999999;
    }
    double rightValue = calculateTree(root->right, variables, count);
    if(rightValue == -999999){
        return -999999;
    }

    // Add The Two Values If Root Is +
    if(strcmp(root->data, "+") == 0){
        return leftValue + rightValue;
    }
    // Subtracts The Two If Root Is -
    if(strcmp(root->data, "-") == 0){
        return leftValue - rightValue;
    }
    // Multiplies The Two If Root Is *
    if(strcmp(root->data, "*") == 0){
        return leftValue * rightValue;
    }
    // Divides The Two If Root Is /
    if(strcmp(root->data, "/") == 0){
        // First Checks For Division By 0
        if(rightValue == 0){
            fprintf( stderr, "Error: division by zero.\n");
            return -999999;
        }
        return leftValue / rightValue;
    }

    fprintf(stderr, "Error: syntax error.\n");
    return -999999;
}
