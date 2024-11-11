#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

struct TreeNode {
char value;
struct TreeNode *left;
struct TreeNode *right;
};

typedef struct TreeNode node;

struct OperandStack {
node* items[100];
int top;
};

struct OperatorStack {
char items[100];
int top;
};

typedef struct OperandStack OperandStack;
typedef struct OperatorStack OperatorStack;

node* createNode(char val, node *leftNode, node *rightNode) {
node* newNode = (node*)malloc(sizeof(node));
newNode->value = val;
newNode->left = leftNode;
newNode->right = rightNode;
return newNode;
}

void initOperandStack(OperandStack* stack) {
stack->top = -1;
}

void initOperatorStack(OperatorStack* stack) {
stack->top = -1;
}

int isOperandStackEmpty(OperandStack* stack) {
return stack->top == -1;
}

int isOperatorStackEmpty(OperatorStack* stack) {
return stack->top == -1;
}

void pushOperand(OperandStack* stack, node* newNode) {
stack->items[++stack->top] = newNode;
}

node* popOperand(OperandStack* stack) {
if (isOperandStackEmpty(stack)) {
printf("Operand stack is empty!\n");
return NULL;
}
return stack->items[stack->top--];
}

void pushOperator(OperatorStack* stack, char value) {
stack->items[++stack->top] = value;
}

char popOperator(OperatorStack* stack) {
if (isOperatorStackEmpty(stack)) {
printf("Operator stack is empty!\n");
return '\0';
}
return stack->items[stack->top--];
}

int isOperator(char c) {
return (c == '+' || c == '-' || c == '*' || c == '/' || c == '=');
}
char peekOperator(OperatorStack* stack){
return stack->items[stack->top];
}
int precedence(char op) {
if (op == '=')
return 0;
if (op == '+' || op == '-')
return 1;
if (op == '*' || op == '/')
return 2;
return 0;
}

void displayTree(node* root) {
if (root != NULL) {
if (root->left || root->right) {
printf("(");
displayTree(root->left);
printf(" %c ", root->value);
displayTree(root->right);
printf(")");
} else {
printf("%c", root->value);
}
}
}

void buildSyntaxTree(char* expr) {
OperandStack* operandStack = (OperandStack*)malloc(sizeof(OperandStack));
OperatorStack* operatorStack = (OperatorStack*)malloc(sizeof(OperatorStack));

initOperatorStack(operatorStack);
initOperandStack(operandStack);

for (int i = 0; i < strlen(expr); i++) {
char ch = expr[i];

if (isspace(ch)) continue;
if (isalnum(ch)) {
pushOperand(operandStack, createNode(ch, NULL, NULL));
} else if (isOperator(ch)) {
while (!isOperatorStackEmpty(operatorStack) &&
precedence(peekOperator(operatorStack)) >= precedence(ch)) {
char op = popOperator(operatorStack);
node* rightNode = popOperand(operandStack);
node* leftNode = popOperand(operandStack);
pushOperand(operandStack, createNode(op, leftNode, rightNode));
}
pushOperator(operatorStack, ch);
}
}

while (!isOperatorStackEmpty(operatorStack)) {
char op = popOperator(operatorStack);
node* rightNode = popOperand(operandStack);
node* leftNode = popOperand(operandStack);
pushOperand(operandStack, createNode(op, leftNode, rightNode));
}


node* finalTree = popOperand(operandStack);

printf("The final syntax tree is: ");
displayTree(finalTree);
printf("\n");
}

int main() {
char inputString[199];
printf("Enter the input expression: ");
fgets(inputString, sizeof(inputString), stdin);


inputString[strcspn(inputString, "\n")] = '\0';

buildSyntaxTree(inputString);

return 0;
}
