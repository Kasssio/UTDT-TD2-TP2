#include "utils.h"

int strLen(char* src) {
    int len = 0; // longitud
    while (src[len] != '\0'){ // Mientras el caracter actual no sea el último de un char, incrementar a len en 1
        len++;
    }
    return len;
}

char* strDup(char* src) {
    int size = strLen(src); // calculo la longitud de src
    char* str2 = (char*) malloc(sizeof(char) * size); // dedico los size espacios de memoria necesarios para copiar src
    for(int i=0; i<size; i++){
        str2[i] = src[i]; // Copio el i-ésimo caracter de mi string en la copia
    }
    return str2;
}

// Keys Predict

struct keysPredict* keysPredictNew() {
    struct keysPredict* kt = (struct keysPredict*)malloc(sizeof(struct keysPredict));
    kt->first = 0;
    kt->totalKeys = 0;
    kt->totalWords = 0;
    return kt;
}

void keysPredictAddWord(struct keysPredict* kt, char* word) {

    // COMPLETAR

}

void keysPredictRemoveWord(struct keysPredict* kt, char* word) {

    // COMPLETAR
}

struct node* keysPredictFind(struct keysPredict* kt, char* word) {

    // COMPLETAR

    return 0;
}

char** keysPredictRun(struct keysPredict* kt, char* partialWord, int* wordsCount) {

    // COMPLETAR

    return 0;
}

int keysPredictCountWordAux(struct node* n) {

    // COMPLETAR
}

char** keysPredictListAll(struct keysPredict* kt, int* wordsCount) {

    // COMPLETAR

    return 0;
}

void keysPredictDelete(struct keysPredict* kt) {

    // COMPLETAR

}

void keysPredictPrint(struct keysPredict* kt) {
    printf("--- Predict --- Keys: %i Words: %i\n", kt->totalKeys, kt->totalWords);
    keysPredictPrintAux(kt->first, 0);
    printf("---\n");
}

void keysPredictPrintAux(struct node* n, int level) {
    if(!n) return;
    struct node* current = n;
    while(current) {
        for(int i=0; i<level;i++) printf(" |   ");
        if(current->end) {
            printf("[%c]\n",current->character);
        } else  {
            printf(" %c \n",current->character);
        }
        keysPredictPrintAux(current->down, level+1);
        current = current->next;
    }
}

// Auxiliar functions

struct node* findNodeInLevel(struct node** list, char character) {
    struct node* lista = list; // Hago una copia de la lista
    struct node* coincidencia = NULL; // Acá guardo el nodo que contenga el caracter
    while(lista != NULL){ // Recorre cada nodo en la lista hasta llegar a NULL
        if(lista->character == character){ // Si el caracter del nodo actual coincide con el buscado...
            coincidencia = lista; // ...guardamos el nodo en coincidencia
        }
        lista = lista->next; // Avanzamos
    }
    return coincidencia;
}

struct node* addSortedNewNodeInLevel(struct node** list, char character) {

    // COMPLETAR

    return 0;
}

void deleteArrayOfWords(char** words, int wordsCount) {

    // COMPLETAR
}