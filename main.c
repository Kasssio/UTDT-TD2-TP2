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
    struct keysPredict* kt1 = keysPredictNew();
    keysPredictPrint(kt1);
    // Tests de strLen()
    int len = strLen("");
    printf("La longitud de \" \" es: %i\n\n", len);
    len = strLen("a");
    printf("La longitud de \"a\" es: %i\n\n", len);
    len = strLen("abcdefghijklmnopqrstuwxyz0123456789");
    printf("La longitud de \"abcdefghijklmnopqrstuwxyz0123456789\" es: %i\n", len);

    // Tests de strDup()
    char* copy = strDup("");
    printf("La copia de \" \" es: %s\n\n", copy);
    copy = strDup("a");
    printf("La copia de \"a\" es: %s\n\n", copy);
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
    printf("Las palabras que existen en dict son: ");
    char** lista = keysPredictListAll(dict, &wordsCount);
    for (int i = 0; i < dict->totalWords; i++) {
        if(i<dict->totalWords-1){
            printf("%s, ", lista[i]);
        }
        else{
            printf("%s\n\n",lista[i]);
        }
    }
    // Tests de keysPredict - keysPredictRun
    char** kPR = keysPredictRun(dict, "c", &wordsCount);
    printf("Palabras encontradas en dict con el prefijo \"c\": ");
    for (int i = 0; i < wordsCount; i++) {
        if(i<wordsCount-1){
            printf("%s, ", kPR[i]);
        }
        else{
            printf("%s\n\n",kPR[i]);
        }
    }
    kPR = keysPredictRun(dict, "ca", &wordsCount);
    printf("Palabras encontradas en dict con el prefijo \"ca\": ");
    for (int i = 0; i < wordsCount; i++) {
        if(i<wordsCount-1){
            printf("%s, ", kPR[i]);
        }
        else{
            printf("%s\n\n",kPR[i]);
        }
    }
    kPR = keysPredictRun(dict, "casa", &wordsCount);
    printf("Palabras encontradas en dict con el prefijo \"casa\": ");
    for (int i = 0; i < wordsCount; i++) {
        if(i<wordsCount-1){
            printf("%s, ", kPR[i]);
        }
        else{
            printf("%s\n\n",kPR[i]);
        }
    }
    kPR = keysPredictRun(dict, "casas", &wordsCount);
    printf("Palabras encontradas en dict con el prefijo \"casas\": ");
    for (int i = 0; i < wordsCount; i++) {
        if(i<wordsCount-1){
            printf("%s, ", kPR[i]);
        }
        else{
            printf("%s\n\n",kPR[i]);
        }
    }

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
    printf("Después de añadir 100 palabras, las palabras en diccionario son: ");
    lista = keysPredictListAll(diccionario, &wordsCount);
    for (int i = 0; i < diccionario->totalWords; i++) {
        if(i<diccionario->totalWords-1){
            printf("%s, ", lista[i]);
        }
        else{
            printf("%s\n\n",lista[i]);
        }
    }
    // keysPredict casos grandes - quitar 50 palabras
    fclose(file);
    file = fopen("./dicc copy.txt", "r");
    while (fgets(word, sizeof(word),file) != NULL) {
        keysPredictRemoveWord(diccionario, word);
    }
    keysPredictPrint(diccionario);
    fclose(file);

    printf("Después de quitar 50 palabras, las palabras en diccionario son: ");
    lista = keysPredictListAll(diccionario, &wordsCount);
    for (int i = 0; i < diccionario->totalWords; i++) {
        if(i<diccionario->totalWords-1){
            printf("%s, ", lista[i]);
        }
        else{
            printf("%s\n\n",lista[i]);
        }
    }
    // keysPredict casos grandes - predecir prefijos de dos letras
    char* alphabet = " abcdefghijklmn-opqrstuvwxyz";
    char prefix[3];

    for (int i=0; i<strLen(alphabet); i++){
        for(int j=0; j<strLen(alphabet);j++){
            prefix[0]= alphabet[i];
            prefix[1]= alphabet[j];
            char** dictRun = keysPredictRun(diccionario, prefix, &wordsCount);
            printf("Palabras encontradas en dict con el prefijo \"%s\": ",prefix);
            for (int k = 0; k < wordsCount; k++) {
                if(k<wordsCount-1){
                    printf("%s, ", dictRun[k]);
                }
                else{
                    printf("%s",dictRun[k]);
                }
            }
            printf("\n");
        }
    }
    // Tests de keysPredict - keysPredictDelete
    keysPredictDelete(dict);
    printf("Dict ahora debería estar vacío. Supuestamente está bien que tire segmentation fault al printearlo.\n");
    return 0;
}
