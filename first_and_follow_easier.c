#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>


#define MAX_PRODUCTIONS 10
#define MAX_SYMBOLS 20
char firstSets[26][MAX_SYMBOLS];
char followSets[26][MAX_SYMBOLS];
char productions[MAX_PRODUCTIONS][MAX_SYMBOLS] = {
    "E->E+T",
    "E->T",
    "T->i"
};

int numProductions = 3;


int isTerminal(char symbol){
    return (!isupper(symbol));
}

void addToSet(char* set, char symbol){
    if(!strchr(set,symbol)){
        int len = strlen(set);
        set[len] = symbol;
        set[len + 1] = '\0';
    }
}


int visited[26]; 

void computeFirst(char symbol) {
    if (isTerminal(symbol)) {
        addToSet(firstSets[symbol - 'A'], symbol);
        return;
    }

    if (visited[symbol - 'A']) return; 
    visited[symbol - 'A'] = 1;         

    for (int i = 0; i < numProductions; i++) {
        if (productions[i][0] == symbol) {
            char* rhs = strchr(productions[i], '>') + 1;

            int allNullable = 1; 
            for (int j = 0; rhs[j] != '\0'; j++) {
                if (isTerminal(rhs[j])) {
                    addToSet(firstSets[symbol - 'A'], rhs[j]);
                    allNullable = 0;
                    break;
                } else {
                    computeFirst(rhs[j]);
                    for (int k = 0; firstSets[rhs[j] - 'A'][k] != '\0'; k++) {
                        char current = firstSets[rhs[j] - 'A'][k];
                        if (current != '#' && isTerminal(current)) {
                            addToSet(firstSets[symbol - 'A'], current);
                        }
                    }
                    if (!strchr(firstSets[rhs[j] - 'A'], '#')) {
                        allNullable = 0;
                        break;
                    }
                }
            }

            
            if (allNullable) {
                addToSet(firstSets[symbol - 'A'], '#');
            }
        }
    }

    visited[symbol - 'A'] = 0; 
}

int followVisited[26]; 

void computeFollow(char symbol) {
    if (followVisited[symbol - 'A']) return; 
    followVisited[symbol - 'A'] = 1;         

    if (symbol == productions[0][0]) { 
        addToSet(followSets[symbol - 'A'], '$');
    }

    for (int i = 0; i < numProductions; i++) {
        char* rhs = strchr(productions[i], '>') + 1;

        for (int j = 0; rhs[j] != '\0'; j++) {
            if (rhs[j] == symbol) {
                if (rhs[j + 1] != '\0') { 
                    char nextSymbol = rhs[j + 1];
                    if (isTerminal(nextSymbol)) {
                        addToSet(followSets[symbol - 'A'], nextSymbol);
                    } else {
                        for (int k = 0; firstSets[nextSymbol - 'A'][k] != '\0'; k++) {
                            char current = firstSets[nextSymbol - 'A'][k];
                            if (current != '#' && isTerminal(current)) {
                                addToSet(followSets[symbol - 'A'], current);
                            }
                        }

                        
                        if (strchr(firstSets[nextSymbol - 'A'], '#')) {
                            computeFollow(productions[i][0]);
                            for (int k = 0; followSets[productions[i][0] - 'A'][k] != '\0'; k++) {
                                addToSet(followSets[symbol - 'A'], followSets[productions[i][0] - 'A'][k]);
                            }
                        }
                    }
                } else { 
                    computeFollow(productions[i][0]);
                    for (int k = 0; followSets[productions[i][0] - 'A'][k] != '\0'; k++) {
                        addToSet(followSets[symbol - 'A'], followSets[productions[i][0] - 'A'][k]);
                    }
                }
            }
        }
    }

    followVisited[symbol - 'A'] = 0; 
}



void main(){
    printf("Productions: \n");
    for(int i = 0; i < numProductions; i++){
        printf("%s\n",productions[i]);
    }

    memset(firstSets, 0 , sizeof(firstSets));
    memset(followSets, 0, sizeof(followSets));

    for(int i = 0; i < numProductions; i++){
        computeFirst(productions[i][0]);

    }

    printf("first Sets\n");
    for(int i = 0; i < 26; i++){
        if(strlen(firstSets[i]) > 0){
            printf("FIRST(%c) = {%s}\n",'A'+i,firstSets[i]);
        }
    }

    for(int i = 0; i < numProductions; i++){
        computeFollow(productions[i][0]);
    }

    printf("FOllow Sets:\n");
    for(int i = 0; i < 26; i++){
        if(strlen(followSets[i]) > 0){
            printf("Follow(%c): {%s}\n", 'A'+i, followSets[i]);
        }

    }
}
