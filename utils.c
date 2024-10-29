#include "utils.h"
#include <string.h>

int strLen(char* src) {
    int len = 0; // Longitud
    while (src[len] != '\0'){ // Mientras el carácter actual no sea el nulo, incrementar a len en 1
        len++;
    }
    return len;
}

char* strDup(char* src) {
    int size = strLen(src); // Calculo la longitud de src
    char* str2 = (char*) malloc(sizeof(char) * (size+1)); // Dedico los size espacios de memoria necesarios para copiar src
    for(int i=0; i<size; i++){
        str2[i] = src[i]; // Copio el i-ésimo caracter de mi string
    }
    str2[size] = '\0';
    return str2;
}

void countWords(struct node* node, int* count){
    if(node == NULL){
        return;
    }
    if(node->end == 1){
        (*count)++;
        printf("count vale %i\n", *count);
    }
    countWords(node->next, count);
    countWords(node->down, count);
}

void storeWordsInArray(struct node* node, char** stringsArray, int* i){ // Creamos una función auxiliar recursiva que nos va a ayudar a almacenar los strings que estén debajo y delante del prefijo
    if(node == NULL){ // Caso base
        return;
    }
    if(node->end == 1){
        printf("Se supone que mi palabra actual es %s\n", node->word);
        stringsArray[*i] = strDup(node->word);
        printf("La palabra almacenada en stringsArray es: %s\n",stringsArray[*i]);
        (*i)++;
    }
    storeWordsInArray(node->next, stringsArray, i); // Llamamos recursivamente a la función, sólo que desplazándonos a la derecha
    storeWordsInArray(node->down, stringsArray, i); // Llamamos recursivamente a la función, sólo que desplazándonos para abajo
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
    struct node** currentNodePtr = &kt->first; // apuntamos al primer nodo

    for (int i = 0; i < strLen(word); i++) { // Por cada carácter...
        char letter = word[i]; // Letra actual

        struct node* foundNode = findNodeInLevel(currentNodePtr, letter); // Busco si la letra existe como nodo
        if (foundNode == NULL) { // Si no existe...
            *currentNodePtr = addSortedNewNodeInLevel(currentNodePtr, letter); // ...agrego el nodo
            foundNode = findNodeInLevel(currentNodePtr,letter); // Me posiciono en el nuevo nodo
            kt->totalKeys++;
        }

        if (i == strLen(word) - 1 && foundNode->end != 1) { // Si estamos en el final de la palabra...
            foundNode->end = 1; // ...marco el final de la palabra
            foundNode->word = strDup(word); //Guardamos una copia de word
            kt->totalWords++;
        }
        currentNodePtr = &foundNode->down; // Bajamos al siguiente nivel
    }
}


void keysPredictRemoveWord(struct keysPredict* kt, char* word) {
    struct node** currentNodePtr = &kt->first; // apuntamos al primer nodo

    for (int i = 0; i < strLen(word); i++) { // Por cada carácter...
        char letter = word[i]; // Letra actual
        struct node* foundNode = findNodeInLevel(currentNodePtr, letter); // Busco si la letra existe como nodo

        if (foundNode->end == 1 && i == strLen(word) - 1) { //
            foundNode->word = 0;
            foundNode->end = 0;
            kt->totalWords--;
            kt->totalKeys -= strLen(word);
        }
        currentNodePtr = &foundNode->down; // Bajamos al siguiente nivel
    }
}

struct node* keysPredictFind(struct keysPredict* kt, char* word) {
    if (kt == NULL) {
        return NULL;
    }
    struct node* current = kt->first;
    int len = strLen(word);

    for (int i = 0; i < len; i++) {
        current = findNodeInLevel(&current, word[i]); // Busco si el carácter actual existe como nodo en este nivel
        if (current == NULL) { // Si no existe...
            return NULL; // No retornamos nada
        }
        if (i == len - 1 && current->end == 1) { // Si estamos en la ultima letra y su palabra coincide con word...
            return current; // ...devolvemos el nodo
        }
        current = current->down; // Bajamos un nivel
    }
    return NULL; // Si nunca encontramos la palabra
}



char** keysPredictRun(struct keysPredict* kt, char* partialWord, int* wordsCount) {
    // tomando el caso de test que esta escrito en main.c, la idea es que le pasemos como prefijo "gat", y que retorne en un arreglo lo siguiente:
    // {"gata","gate","gati","gato","gatubela"}.
    // encuentro "gata", hago una copia de ese char y lo almaceno en el arreglo.
    int len = strLen(partialWord);
    if (kt == NULL){
        return 0;
    }
    struct node* current = kt->first;
    for(int i=0;partialWord[i] != '\0';i++){
        current = findNodeInLevel(&current, partialWord[i]);
        if (current == NULL){
            return NULL;
        }
        current = current->down;
    }

    *wordsCount = 0;
    countWords(current, wordsCount);
    printf("wordsCount vale %i\n",*wordsCount);
    char** strings = (char**) malloc(sizeof(char*) * *wordsCount);
    int count = 0;
    storeWordsInArray(current, strings, &count);
    return strings;
}

char** keysPredictListAll(struct keysPredict* kt, int* wordsCount) {
    if (kt == NULL){
      return NULL;
    }
    wordsCount = 0;
    countWords(kt->first, wordsCount);
    char** wordList = (char**) malloc(sizeof(char*) * *wordsCount);
    int count = 0;
    storeWordsInArray(kt->first, wordList, &count);
    return wordList;
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

    if(lista == NULL){ // posible caso en el cual la lista esté vacía
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
