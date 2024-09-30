#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#define MAX_STATES 100
#define MAX_INPUTS 10

int transition[MAX_STATES][MAX_INPUTS];
bool final_states[MAX_STATES];
bool marked[MAX_STATES][MAX_STATES];
int num_states, num_inputs, num_final_states;
int final[MAX_STATES];
int input_symbols[MAX_INPUTS];

void initialize() {
    for (int i = 0; i < MAX_STATES; i++) {
        for (int j = 0; j < MAX_INPUTS; j++) {
            transition[i][j] = -1;
        }
        final_states[i] = false;
    }
}

void mark_final_states() {
    for (int i = 0; i < num_final_states; i++) {
        final_states[final[i]] = true;
    }
}

void minimize() {
    for (int i = 0; i < num_states; i++) {
        for (int j = 0; j < num_states; j++) {
            if (final_states[i] != final_states[j]) {
                marked[i][j] = marked[i][j] = true;
            }
        }
    }
    bool changed = true;
    while (changed) {
        changed = false;
        for (int i = 0; i < num_states; i++) {
            for (int j = 0; j < num_states; j++) {
                if (!marked[i][j]) {
                    for (int k = 0; k < num_inputs; k++) {
                        int t1 = transition[i][k];
                        int t2 = transition[j][k];
                        if ((t1 != -1 && t2 != -1 && marked[t1][t2]) || (t1 == -1 && t2 != -1) || (t2 == -1 && t1 != -1)) {
                            marked[i][j] = marked[i][j] = true;
                            changed = true;
                            break;
                        }
                    }
                }
            }
        }
    }
}

void display_initial_dfa() {
    printf("\nInitial DFA state table:\n");
    printf("State ");
    for (int i = 0; i < num_inputs; i++) {
        printf("%d ", input_symbols[i]);
    }
    printf("\n");
    for (int i = 0; i < num_states; i++) {
        printf("%d    ", i);
        for (int j = 0; j < num_inputs; j++) {
            if (transition[i][j] != -1) {
                printf("%d ", transition[i][j]);
            } else {
                printf("- ");
            }
        }
        printf("\n");
    }
}

void display_minimized_dfa() {
    printf("\nMinimized DFA state table:\n");
    printf("State ");
    for (int i = 0; i < num_inputs; i++) {
        printf("%d ", input_symbols[i]);
    }
    printf("\n");
    for (int i = 0; i < num_states; i++) {
        bool unique = true;
        for (int j = 0; j < i; j++) {
            if (!marked[i][j]) {
                unique = false;
                break;
            }
        }
        if (unique) {
            printf("%d    ", i);
            for (int k = 0; k < num_inputs; k++) {
                if (transition[i][k] != -1) {
                    printf("%d ", transition[i][k]);
                } else {
                    printf("- ");
                }
            }
            printf("\n");
        }
    }
}

int main() {
    initialize();
    
    printf("Enter the number of states: ");
    scanf("%d", &num_states);
    
    printf("Enter the number of inputs: ");
    scanf("%d", &num_inputs);
    
    printf("Enter the input symbols (space-separated): ");
    for (int i = 0; i < num_inputs; i++) {
        scanf("%d", &input_symbols[i]);
    }
    
    printf("Enter the state transition table:\n");
    for (int i = 0; i < num_states; i++) {
        for (int j = 0; j < num_inputs; j++) {
            printf("Transition from state %d with input %d: ", i, input_symbols[j]);
            scanf("%d", &transition[i][j]);
        }
    }
    
    printf("Enter the number of final states: ");
    scanf("%d", &num_final_states);
    
    printf("Enter the final states (space-separated): ");
    for (int i = 0; i < num_final_states; i++) {
        scanf("%d", &final[i]);
    }
    
    display_initial_dfa();
    
    mark_final_states();
    minimize();
    
    display_minimized_dfa();
    
    return 0;
}
