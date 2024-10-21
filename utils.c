#include "utils.h"

int strLen(char* src) {
    int len = 0; // Longitud
    while (src[len] != '\0'){ // Mientras el carácter actual no sea el nulo, incrementar a len en 1
        len++;
    }
    return len;
}

char* strDup(char* src) {
    int size = strLen(src); // Calculo la longitud de src
    char* str2 = (char*) malloc(sizeof(char) * size); // Dedico los size espacios de memoria necesarios para copiar src
    for(int i=0; i<size; i++){
        str2[i] = src[i]; // Copio el i-ésimo caracter de mi string
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
    struct node* currentNode = kt->first; // Nodo actual, empieza en el inicio
    for(int i=0; word[i] != 0; i++){
        char letter = word[i]; // Carácter actual

        if(currentNode == NULL){ // Caso vacío
            currentNode = addSortedNewNodeInLevel(&kt->first, letter); // Añado la letra actual como nodo, uso & para cumplir con el doble puntero
            kt->totalKeys++; // Como hay una nueva letra, aumentamos totalKeys
        }
        else { // Si hay algo, vemos si la letra actual está en la lista en la que estamos parados
            struct node* coincidence = findNodeInLevel(&currentNode, letter); // Analizamos la coincidencia
            if (coincidence == NULL){ // Si no hay coincidencia...
                currentNode = addSortedNewNodeInLevel(&currentNode, letter); // ...tenemos una nueva letra para añadir a este nivel.
                kt->totalKeys++;
            } else { // Sino...
                currentNode = coincidence; // ...nos posicionamos en el nodo que sea igual a nuestra letra. No hay nuevas letras, así que no sumamos a totalKeys.
            }
        }

        if(i == strLen(word) - 1){ // Si estamos en el final...
            if(word[i] == '\0'){ // ... y llegamos al fin de word...
                currentNode->end = 1; // Marcamos el fin
                currentNode->word = word;
                kt->totalWords++; // Una palabra más al total
            } else if (currentNode->down == NULL){ // Como no se cumplió lo anterior, tenemos que añadir una letra debajo de currentNode
                currentNode->down = addSortedNewNodeInLevel(&currentNode->down, word[i+1]); // Añadimos el caracter que falta
            }
        }
        currentNode = currentNode->down; // Bajo un nivel
    }


}

void keysPredictRemoveWord(struct keysPredict* kt, char* word) {
    kt->totalWords--; // Quito una palabra de la cantidad total

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
    return 0;
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

int findPosInAlphabet(char character){ // Esta función nos permite encontrar la posición del caracter en el abecedario
    int pos = 0;
    char* alphabet = "abcdefghijklmnopqrstuvwxyz";
    for(int i = 0; i<26; i++){
        if(alphabet[i] == character){
            return i;
        }
    }
    return 26;
}

struct node* findNodeInLevel(struct node** list, char character) {
    struct node* lista = *list; // Hago una reasignación de la lista (desreferenciamos el doble puntero ya que está de más)
    while(lista != NULL){ // Recorre cada nodo en la lista hasta llegar a 0
        if(lista->character == character){ // Si el caracter del nodo actual coincide con el buscado...
            return lista; // ...retornamos el nodo en el cual se encuentra la coincidencia
        }
        lista = lista->next; // Avanzamos
    }
    return NULL; // Retornamos 0 si no encontramos ninguna coincidencia
}

struct node* addSortedNewNodeInLevel(struct node** list, char character) {
    struct node* newNode = (struct node*) malloc(sizeof(struct node));
    newNode->character = character;
    newNode->next = NULL;

    struct node* lista = *list; // reasignación de list

    int charPos = findPosInAlphabet(character);

    if(lista == 0){ // posible caso en el cual la lista esté vacía
       *list = newNode;
        return newNode;
    }

    if(charPos < findPosInAlphabet(lista->character)) { // Posible caso en el cual character es el más chico
        newNode->next = lista;
        *list = newNode;
        return *list;
    }

    while(lista->next != NULL){
        if(findPosInAlphabet(lista->character) < charPos && findPosInAlphabet(lista->next->character) > charPos){ // Si el caracter esta más adelante en el abecedario...
                newNode->next = lista->next; // el siguiente de newNode va a ser el nodo actual
                lista->next = newNode; // el siguiente nodo del acutal será newNode
                return *list; // Cortamos ahí, retornamos el principio
        }
        lista = lista->next;
    }
    lista->next = newNode; // Añadir al final si character es el más grande
    newNode->next = NULL;
    return *list;
}

void deleteArrayOfWords(char** words, int wordsCount) {
    for (int i=0; i<wordsCount; i++){
        free(words[i]);
    }
    free(words);
}
