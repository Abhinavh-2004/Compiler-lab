#include <stdio.h>
#include <string.h>
#include <string.h>
#include <ctype.h>

#define MAX_SYMBOLS 100

struct symbol{
    char symbol[50];
    int type;
    char description[100];
};

typedef struct symbol symbol;



symbol symbolTable[MAX_SYMBOLS];
int symbolCount = 0;


void addToSymbolTable(char* symbol, char* description){
    strcpy(symbolTable[symbolCount].symbol, symbol);
    symbolTable[symbolCount].type = symbolCount+1;
    strcpy(symbolTable[symbolCount].description, description);
    symbolCount++;
}


void printSymbolTable() {
    printf("\nSymbol Table:\n");
    printf("-----------------------------------------------------\n");
    printf("| Symbol       | Type   | Description              |\n");
    printf("-----------------------------------------------------\n");
    for (int i = 0; i < symbolCount; i++) {
        printf("| %-12s | %-6d | %-22s |\n",
               symbolTable[i].symbol,
               symbolTable[i].type,
               symbolTable[i].description);
    }
    printf("-----------------------------------------------------\n");
}


void analyseStatement(char* statement){
    printf("Analysing, statement: %s\n",statement);

    char buffer[100];
    int index = 0;

    char* keywords[] = {"int", "float", "char", "double", "void"};
    char* operators = "+-/%=";
    char* delimitiers = " ;";

    for(int i = 0; statement[i] != '\0'; i++){
        char ch = statement[i];

        if(strchr(delimitiers,ch) || strchr(operators, ch)){
            if(index> 0){
                buffer[index] = '\0';
                int isKeyword = 0;
                for(int k = 0; k < 5; k++){
                    if(strcmp(buffer, keywords[k] )==0){
                        isKeyword =1 ;
                        break;
                    }

                }
                if(isKeyword){
                    addToSymbolTable(buffer, "keyword");
                }
                else if(isdigit(buffer[0])){
                    addToSymbolTable(buffer, "constant");
                }
                else{
                    addToSymbolTable(buffer, "Identifier");
                }
                index = 0;
            }
            if(strchr(operators, ch)){
                char operatorStr[2] = {ch, '\0'};
                addToSymbolTable(operatorStr, "operator");
            }
            else if(ch == ';'){
                addToSymbolTable(";","semicolon");
            }
        }
        else if(!isspace(ch)){
            buffer[index++] = ch;
        }
    }

    if(index > 0){
        buffer[index] = '\0';
        if(isdigit(buffer[0])){
            addToSymbolTable(buffer, "constatn");
        }
        else{
            addToSymbolTable(buffer, "identifier");
        }
    }
    

}
void main(){
    char statement[100];
    printf("Enter your statement: ");
    fgets(statement, sizeof(statement), stdin);
    for(int i = 0; statement[i] != '\0';i++){
        if(statement[i] == '\n'){
            statement[i] = '\0';
        }
    }

    analyseStatement(statement);
    printSymbolTable();

}
