#include <stdio.h>
#include <string.h>
#include <stdlib.h>

int PRICE_LENGTH = 17161; //csv.length - header
int STRING_MAX_SIZE = 1024;

// void readPriceCsv(char* from, char* to, int* adult, int* elder, int* child) {
void readPriceCsv() {
    FILE* price = fopen("price.csv", "r");
    //for storage // TODO put it in main? or just return result only

    char from[PRICE_LENGTH][50], to[PRICE_LENGTH][50];
    char useless[5][STRING_MAX_SIZE]; // For Header
    int adult[PRICE_LENGTH], elder[PRICE_LENGTH], child[PRICE_LENGTH];

    // handle FileNotFoundException
    if(!price){fprintf(stderr, "file to open csv file"); return 1;}
    

    fseek(price, 0, SEEK_SET);

    char line[STRING_MAX_SIZE]; // for storage csv.eachLine
    char* result = NULL; // for storage csv.eachLine.split(',')
    int count = 0; // while loop indicator
    while(fgets(line, STRING_MAX_SIZE, price) != NULL){
        result = strtok(line, ","); 
        for(int i=0; i<5; i++){
            if(count == 0){
                strncpy(useless[i], result, strlen(result) + 1); // Header
            } else {
                switch(i) {
                    case 0: // From
                        strcpy(&from[count-1], result);
                        break;
                    case 1: // To
                        strcpy(to[count-1], result);
                        break;
                    case 2: // Price of Adult
                        adult[count-1] = atoi(result);
                        break;
                    case 3: // Price of Elder
                        elder[count-1] = atoi(result);
                        break;
                    case 4: // Price of Children
                        child[count-1] = atoi(result);
                        break;
                }
            }
            result = strtok(NULL, ",");
        }
        count++; // Indicator++ : prevent infinity loop
    }

    fclose(price);
}

int main() {
    //init - params

    // if parameters are created in main =>
    // readPriceCsv(from, to, adult, elder, child);

    // if parameters are created in function =>
    readPriceCsv();
    
}