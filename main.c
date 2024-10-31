#include <stdio.h>
#include <stdlib.h>
#include "utils.h"

void predictAndPrintAll(struct keysPredict* kt, char* partialWord ) {
    char** words;
    int wordsCount;
    words = keysPredictRun(kt, partialWord, &wordsCount);
    printf("Predicts: %s = ", partialWord);
    for(int i=0; i<wordsCount; i++) {
        printf("%s,", words[i]);
    }
    printf("\n");
    deleteArrayOfWords(words, wordsCount);
}

void findAndPrintAll(struct keysPredict* kt, char* word ) {
    struct node* result = keysPredictFind(kt, word);
    printf("Find: %s = %i\n", word, result==0);
}

int main() {

    // Tests de strLen()
    int len = strLen("");
    printf("La longitud de \" \" es: %i\n", len);
    len = strLen("a");
    printf("La longitud de \"a\" es: %i\n", len);
    len = strLen("abcdefghijklmnopqrstuwxyz0123456789");
    printf("La longitud de \"abcdefghijklmnopqrstuwxyz0123456789\" es: %i\n", len);

    // Tests de strDup()
    char* copy = strDup("");
    printf("La copia de \" \" es: %s\n", copy);
    copy = strDup("a");
    printf("La copia de \"G\" es: %s\n", copy);
    copy = strDup("abcdefghijklmnopqrstuwxyz0123456789");
    printf("La copia de \"abcdefghijklmnopqrstuwxyz0123456789\" es: %s\n", copy);

    // Tests de keysPredict
    struct keysPredict* dict = keysPredictNew();
    int wordsCount = 0;
    keysPredictAddWord(dict,"alfajor");
    keysPredictAddWord(dict,"canoa");
    keysPredictAddWord(dict,"rinoceronte");
    keysPredictAddWord(dict,"casa");
    keysPredictAddWord(dict,"noqui");
    keysPredictPrint(dict);

    keysPredictRemoveWord(dict,"canoa");
    keysPredictAddWord(dict,"pato");
    keysPredictPrint(dict);
    // Tests de keysPredict - keysPredictListAll
    char** lista = keysPredictListAll(dict, &wordsCount);
    for (int i = 0; i < dict->totalWords; i++) {
        printf(" HOALHOLAOHOLA%s\n", lista[i]);
    }
    // Tests de keysPredict - keysPredictRun
    char** kPR = keysPredictRun(dict, "c", &wordsCount);
    printf("Palabras encontradas en dict con el prefijo \"c\":\n");
    for (int i = 0; i < wordsCount; i++) {
        printf("%s\n", kPR[i]);
    }
    kPR = keysPredictRun(dict, "ca", &wordsCount);
    printf("Palabras encontradas en dict con el prefijo \"ca\":\n");
    for (int i = 0; i < wordsCount; i++) {
        printf("%s\n", kPR[i]);
    }
    kPR = keysPredictRun(dict, "ca", &wordsCount);
    printf("Palabras encontradas en dict con el prefijo \"casa\":\n");
    for (int i = 0; i < wordsCount; i++) {
        printf("%s\n", kPR[i]);
    }
    kPR = keysPredictRun(dict, "casas", &wordsCount);
    printf("Palabras encontradas en dict con el prefijo \"casas\":\n");
    for (int i = 0; i < wordsCount; i++) {
        printf("%s\n", kPR[i]);
    }

    // Tests de keysPredict - keysPredictDelete


    // keysPredict casos grandes - añadir 100 palabras
    struct keysPredict* diccionario = keysPredictNew();
    FILE *file = fopen("./dicc.txt", "r");
    if (file == NULL) {
        printf("Error al abrir el archivo.\n");
        return 1;
    }
    char word[20];

    while (fgets(word, sizeof(word),file) != NULL) {
        keysPredictAddWord(diccionario, word);
    }
    keysPredictPrint(diccionario);

    // keysPredict casos grandes - quitar 50 palabras
    fclose(file);
    file = fopen("./dicc copy.txt", "r");
    while (fgets(word, sizeof(word),file) != NULL) {
        keysPredictRemoveWord(diccionario, word);
    }
    keysPredictPrint(diccionario);
    fclose(file);

    // keysPredict casos grandes - predecir prefijos de dos letras
    char* alphabet = " abcdefghijklmn-opqrstuvwxyz";
    char prefix[3];

    for (int i=0; i<strLen(alphabet); i++){
        for(int j=0; j<strLen(alphabet);j++){
            prefix[0]= alphabet[i];
            prefix[1]= alphabet[j];
            char** dictRun = keysPredictRun(dict, prefix, &wordsCount);
            printf("Palabras encontradas en dict con el prefijo \"%s\":\n",prefix);
            for (int k = 0; k < wordsCount; k++) {
                printf("%s\n", dictRun[k]);
            }
        }
    }
    return 0;
}
