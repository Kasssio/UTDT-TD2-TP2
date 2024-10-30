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
    int* wordsCount;
    keysPredictAddWord(dict,"casat");
    keysPredictAddWord(dict,"casan");
    keysPredictAddWord(dict,"casal");
    keysPredictAddWord(dict,"casa");
    keysPredictAddWord(dict,"rino");
    keysPredictPrint(dict);

    //keysPredictRemoveWord(dict,"canoa");
    keysPredictAddWord(dict,"pato");
    keysPredictPrint(dict);

    char** kPR = keysPredictRun(dict, "c", wordsCount);
    printf("Palabras encontradas en dict con el prefijo \"c\":\n");
    for (int i = 0; i < *wordsCount; i++) {
        printf("%s\n", kPR[i]);
    }

    kPR = keysPredictRun(dict, "ca", wordsCount);
    printf("Palabras encontradas en dict con el prefijo \"ca\":\n");
    for (int i = 0; i < *wordsCount; i++) {
        printf("%s\n", kPR[i]);
    }

    kPR = keysPredictRun(dict, "casa", wordsCount);
    printf("Palabras encontradas en dict con el prefijo \"casa\":\n");
    for (int i = 0; i < *wordsCount; i++) {
        printf("%s\n", kPR[i]);
    }

    kPR = keysPredictRun(dict, "casas", wordsCount);
    printf("Palabras encontradas en dict con el prefijo \"casas\":\n");
    for (int i = 0; i < *wordsCount; i++) {
        printf("%s\n", kPR[i]);
    }
    return 0;
}
