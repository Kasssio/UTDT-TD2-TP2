#include "utils.h"
#include <string.h>

// Funciones auxiliares
// Esta función cuenta la longitud de un string, avanzando carácter por carácter hasta llegar al carácter nulo '\0'
int strLen(char* src) {
    int len = 0; // Longitud
    while (src[len] != '\0' && src[len] != '\n'){ // Mientras el carácter actual no sea el nulo, incrementar a len en 1
        len++;
    }
    return len;
}

// strDup dedica la cantidad de espacios de memoria necesarios para almacenar una copia de src con el caractér nulo incluído
char* strDup(char* src) {
    int size = strLen(src); // Calculo la longitud de src
    char* str2 = (char*) malloc(sizeof(char) * (size+1)); // Dedico los size espacios de memoria necesarios para copiar src
    for(int i=0; i<size; i++){
        str2[i] = src[i]; // Copio el i-ésimo caracter de mi string
    }
    str2[size] = '\0'; // Añado el caracter nulo
    return str2;
}

// countWords es una función recursiva que busca todas las palabras en una lista de nodos, bajando con down y con next
void countWords(struct node* node, int* count){
    if(node == NULL){
        return;
    }
    if(node->end == 1){
        (*count)++;
    }
    countWords(node->next, count);
    countWords(node->down, count);
}

// Función recursiva que usa un algoritmo similar a storeWordsInArray, recorriendo todo el árbol de nodos y liberando cada nodo y palabra.
void deleteAllWords(struct node* n, struct keysPredict* kt){
    if (n == NULL){
        return;
    }
    deleteAllWords(n->next,kt);
    deleteAllWords(n->down,kt);
    if (n->word != NULL){
        free(n->word);
        kt->totalWords--;
    }

    free(n);
    kt->totalKeys--;
}
// storeWordsInArray almacena recursivamente en un arreglo de punteros a strings todas las palabras que existan desde el primer nodo pasado por parámetro
void storeWordsInArray(struct node* node, char** stringsArray, int* i){ // Creamos una función auxiliar recursiva que nos va a ayudar a almacenar los strings que estén debajo y delante del prefijo
    if(node == NULL){ // Caso base
        return;
    }
    if(node->end == 1){
        stringsArray[*i] = strDup(node->word);
        (*i)++;
    }
    storeWordsInArray(node->down, stringsArray, i); // Llamamos recursivamente a la función, sólo que desplazándonos para abajo
    storeWordsInArray(node->next, stringsArray, i); // Llamamos recursivamente a la función, sólo que desplazándonos a la derecha
}

// Keys Predict

struct keysPredict* keysPredictNew() {
    struct keysPredict* kt = (struct keysPredict*)malloc(sizeof(struct keysPredict));
    kt->first = 0;
    kt->totalKeys = 0;
    kt->totalWords = 0;
    return kt;
}

// keysPredictAddWord busca, por iteración, la letra actual en la lista de nodos en la que estemos parados.
// Si existe, nos paramos en la letra y seguimos avanzando.
// Sino, añadimos la letra como nodo, nos movemos a ese nodo y seguimos buscando.
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

// keysPredictRemoveWord va buscando nodo por nodo la palabra pasada por parámetro. Una vez que la encuentra libera la memoria del nodo que la contiene.
void keysPredictRemoveWord(struct keysPredict* kt, char* word) {
    struct node** currentNodePtr = &kt->first; // apuntamos al primer nodo

    for (int i = 0; i < strLen(word); i++) { // Por cada carácter...
        char letter = word[i]; // Letra actual
        struct node* foundNode = findNodeInLevel(currentNodePtr, letter); // Busco si la letra existe como nodo

        if (foundNode->end == 1 && i == strLen(word) - 1) { //
            foundNode->word = 0;
            foundNode->end = 0;
            kt->totalWords--;
        }
        currentNodePtr = &foundNode->down; // Bajamos al siguiente nivel
    }
}

// keysPredictFind va buscando caracter por caracter la palabra pasada por parámetro. Si encuentra todos los caracteres,
struct node* keysPredictFind(struct keysPredict* kt, char* word) {
    if (kt == NULL) {
        return NULL;
    }
    struct node* current = kt->first;
    int len = strLen(word);

    for (int i = 0; i < len; i++) {
        current = findNodeInLevel(&current, word[i]); // Busco si el carácter actual existe como nodo en este nivel
        if (current == NULL) { // Si no existe...
            return NULL; // ...no retornamos nada
        }
        if (i == len - 1 && current->end == 1) { // Si estamos en la última letra y estamos el fin de una palabra...
            return current; // ...devolvemos el nodo
        }
        current = current->down; // Bajamos un nivel
    }
    return NULL; // Si nunca encontramos la palabra retornamos NULL
}


// keysPredictRun utiliza las funciones recursivas wordsCount y storeWordsInArray para contar y listar todas las palabras que existan a partir del prefijo pasado por parámetro.
// Iteramos hasta encontrar todo el prefijo en el keysPredict, y de ahí en adelante usamos storeWordsInArray para almacenar todas las palabras encontradas en el "árbol" de nodos.
//
//
char** keysPredictRun(struct keysPredict* kt, char* partialWord, int* wordsCount) {
    *wordsCount = 0;
    int len = strLen(partialWord);
    if (kt == NULL){
        return 0;
    }
    struct node* current = kt->first;
    int prefixExists = 0;
    for(int i=0;partialWord[i] != '\0';i++){
        current = findNodeInLevel(&current, partialWord[i]);
        if (current == NULL){
            return NULL;
        }
        if (i == len-1 && current->end == 1){
            prefixExists = 1;
        }
        current = current->down;
    }
    countWords(current, wordsCount);
    int count = 0;
    if(prefixExists){
        (*wordsCount)++;
        count++;
    }
    char** strings = (char**) malloc(sizeof(char*) * *wordsCount);
    if(prefixExists){
        strings[0] = strDup(partialWord);
    }
    storeWordsInArray(current, strings, &count);
    return strings;
}

// keysPredictListAll hace y usa lo mismo que keysPredictRun, sólo que sin prefijo.
// es decir, recorre el keysPredict completo y almacena en un arreglo de punteros a strings todas las palabras encontradas, sin restricciones
char** keysPredictListAll(struct keysPredict* kt, int* wordsCount) {
    if (kt == NULL){
      return NULL;
    }
    *wordsCount = 0;
    countWords(kt->first, wordsCount);
    char** wordList = (char**) malloc(sizeof(char*) * *wordsCount);
    int count = 0;
    storeWordsInArray(kt->first, wordList, &count);
    return wordList;
}

void keysPredictDelete(struct keysPredict* kt) {
    deleteAllWords(kt->first, kt);
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

// en findPosInAlphabet buscamos la posición de nuestro caracter actual en el alfabeto
int findPosInAlphabet(char character){ // Esta función nos permite encontrar la posición del caracter en el abecedario
    int pos = 0;
    char* alphabet = " abcdefghijklmn-opqrstuvwxyz";
    for(int i = 0; i<strLen(alphabet); i++){
        if(alphabet[i] == character){
            return i;
        }
    }
    return strLen(alphabet);
}

// findNodeInLevel recorre cada nodo y se fija si su caracter coincide con el pasado por parámetro. Si se cumple devuelve ese nodo.
// Sino, no devuelve nada.
struct node* findNodeInLevel(struct node** list, char character) {
    if(list == NULL){
        return NULL;
    }
    struct node* lista = *list; // Hago una reasignación de la lista (desreferenciamos el doble puntero ya que está de más)
    while(lista != NULL){ // Recorre cada nodo en la lista hasta llegar a 0
        if(lista->character == character){ // Si el caracter del nodo actual coincide con el buscado...
            return lista; // ...retornamos el nodo en el cual se encuentra la coincidencia
        }
        lista = lista->next; // Avanzamos
    }
    return NULL; // Retornamos 0 si no encontramos ninguna coincidencia
}

// addSortedNewNodeInLevel se ocupa de añadir un nuevo nodo en una lista de nodos respetando el orden alfabético por caracter.
// Hay tres posibles casos: que el nuevo nodo tenga el caracter más "chico" en la lista, que esté entre dos nodos y que sea el último.
// Para ver si es el más chico comparamos con el primer nodo, y si es menor lo añadimos al principio y hacemos que apunte al siguiente.
// Para añadir entre dos nodos vemos si el nodo actual es menor al newNode y si el siguiente al nodo actual es mayor que newNode.
// Si es el caracter más grande en la lista, significa que el ciclo fue ignorado, así que hacemos que el último nodo de la lista apunte a newNode.
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

// deleteArrayOfWords limpia la memoria en cada índice del arreglo de palabras.
void deleteArrayOfWords(char** words, int wordsCount) {
    for (int i=0; i<wordsCount; i++){
        free(words[i]);
    }
    free(words);
}
