#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define MAX_PRODUCTIONS 10
#define MAX_SYMBOLS 10
#define MAX_STATES 10

typedef struct {
    char lhs;
    char rhs[10];
} Production;

Production productions[MAX_PRODUCTIONS];
int numProductions = 0;

char symbols[MAX_SYMBOLS];
int numSymbols = 0;

int actionTable[MAX_STATES][MAX_SYMBOLS];
int gotoTable[MAX_STATES][MAX_SYMBOLS];

void initializeGrammarFromInput() {
    printf("Enter the number of productions: ");
    scanf("%d", &numProductions);

    for (int i = 0; i < numProductions; i++) {
        printf("Enter production %d (format: E->E+T): ", i + 1);
        char input[20];
        scanf("%s", input);

        // Parse the input into lhs and rhs
        productions[i].lhs = input[0];  // Left-hand side
        strcpy(productions[i].rhs, &input[3]);  // Right-hand side (skip "->")

        // Add LHS to symbols if not already present
        int exists = 0;
        for (int j = 0; j < numSymbols; j++) {
            if (symbols[j] == productions[i].lhs) {
                exists = 1;
                break;
            }
        }
        if (!exists) {
            symbols[numSymbols++] = productions[i].lhs;
        }

        // Add RHS symbols to symbols array if not present
        for (int j = 0; j < strlen(productions[i].rhs); j++) {
            char sym = productions[i].rhs[j];
            if (sym >= 'A' && sym <= 'Z') { // Consider non-terminals
                exists = 0;
                for (int k = 0; k < numSymbols; k++) {
                    if (symbols[k] == sym) {
                        exists = 1;
                        break;
                    }
                }
                if (!exists) {
                    symbols[numSymbols++] = sym;
                }
            }
        }
    }
    
    // Add terminal symbols (assume lowercase letters and symbols like +, *)
    symbols[numSymbols++] = '+';  // Example terminal
    symbols[numSymbols++] = '*';  // Example terminal
    symbols[numSymbols++] = '(';  // Example terminal
    symbols[numSymbols++] = ')';  // Example terminal
    symbols[numSymbols++] = 'i';  // Representing 'id' as 'i'
    symbols[numSymbols++] = '$';  // End of input
}

void initializeParsingTable() {
    // Fill with -1 to denote errors or empty entries
    for (int i = 0; i < MAX_STATES; i++) {
        for (int j = 0; j < MAX_SYMBOLS; j++) {
            actionTable[i][j] = -1;
            gotoTable[i][j] = -1;
        }
    }
    
    // Example of setting actions for state 0 (for demonstration)
    actionTable[0][3] = 5;  // shift '('
    actionTable[0][7] = 4;  // shift 'id'
    gotoTable[0][0] = 1;    // goto E
    gotoTable[0][1] = 2;    // goto T
    gotoTable[0][2] = 3;    // goto F
    
    // Continue filling actionTable and gotoTable for other states...

    // Example of adding reductions
    actionTable[1][8] = 0;  // Accept
    actionTable[2][4] = -2; // Reduce by T -> F
    // Add more actions based on the grammar states and transitions
}

void printParsingTable() {
    printf("\nAction Table:\n");
    for (int i = 0; i < MAX_STATES; i++) {
        for (int j = 0; j < numSymbols; j++) {
            if (actionTable[i][j] != -1) {
                if (actionTable[i][j] > 0) {
                    printf(" S%-2d", actionTable[i][j]);  // Shift
                } else if (actionTable[i][j] < 0) {
                    printf(" R%-2d", -actionTable[i][j]); // Reduce
                } else {
                    printf(" Acc");                      // Accept
                }
            } else {
                printf("    "); // No action
            }
        }
        printf("\n");
    }

    printf("\nGoto Table:\n");
    for (int i = 0; i < MAX_STATES; i++) {
        for (int j = 0; j < numSymbols; j++) {
            if (gotoTable[i][j] != -1) {
                printf(" %-3d", gotoTable[i][j]);
            } else {
                printf("    ");
            }
        }
        printf("\n");
    }
}

int main() {
    initializeGrammarFromInput();
    initializeParsingTable();
    printParsingTable();
    // Add input parsing and stack handling here to complete the SLR parsing
    return 0;
}