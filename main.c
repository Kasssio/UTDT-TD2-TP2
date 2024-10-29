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
    // strLen
    int len = strLen("hola");
    printf("strLen(\"hola\") -> \"%i\"\n", len); //MODIFICADO
    printf("\n");

    len = strLen("");
    printf("strLen(\"\") -> \"%i\"\n", len); //String vacio.
    printf("\n");

    len = strLen("Ñ");
    printf("strLen(\"Ñ\") -> \"%i\"\n", len); //String de un caracter.
    printf("\n");

    len = strLen("0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ");
    printf("strLen(\"0123456789abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ\") -> \"%i\"\n", len); //String que incluya todos los caracteres alfanumericos.
    printf("\n");

    len = strLen("");
    printf("strLen(\"hola\") -> \"%i\"\n", len); //String que incluya todos los simbolos. (espacio) ! " # $ % & ' ( ) * + , - . / : ; < = > ? @ [ \ ] ^ _` { | } ~ (33 caracteres) No muy buena idea.
    printf("\n");

    // strDup
    char* dup = strDup("");
    printf("strDup(\"\") -> \"%s\"\n", dup); //String vacio.
    free(dup);
    printf("\n");

    dup = strDup("í");
    printf("strDup(\"í\") -> \"%s\"\n", dup); //String de un caracter.
    free(dup);
    printf("\n");

    dup = strDup("0123456789abcdefghijklmnñopqrstuvwxyzABCDEFGHIJKLMNÑOPQRSTUVWXYZ"); //(Solo min) "0123456789abcdefghijklmnñopqrstuvwxyz" // (sin ñ) "0123456789abcdefghijklmnopqrstuvwxyz"
    printf("strDup(\"0123456789abcdefghijklmnñopqrstuvwxyzABCDEFGHIJKLMNÑOPQRSTUVWXYZ\") -> \"%s\"\n", dup); //String que incluya todos los caracteres alfanumericos.
    free(dup);
    printf("\n");

    dup = strDup("");
    printf("strDup(\"\") -> \"%s\"\n", dup); //String que incluya todos los simbolos. (espacio) ! " # $ % & ' ( ) * + , - . / : ; < = > ? @ [ \ ] ^ _` { | } ~ (33 caracteres) No muy buena idea. Conte 31 sin el espacio.
    free(dup);
    printf("\n");

    // keysPredict
    struct keysPredict* kt = keysPredictNew();

    // keysPredict - agregar palabras al diccionario (Casos chicos)
    keysPredictAddWord(kt, "alfajor");
    keysPredictAddWord(kt, "canoa");
    keysPredictAddWord(kt, "rinoceronte");
    keysPredictAddWord(kt, "casa");
    keysPredictAddWord(kt, "rino");

    // keysPredict - borrar palabras del diccionario (Casos chicos)
    keysPredictRemoveWord(kt,"canoa");
    keysPredictAddWord(kt, "pato");

    // Y si eliminamos algo que no existe? Y si agregamos algo que ya existe? Y si agregamos un string vacio?
    keysPredictRemoveWord(kt,"rin");
    keysPredictRemoveWord(kt,"alfajor ");
    keysPredictAddWord(kt, "pato");
    keysPredictAddWord(kt, "PaTo");
    keysPredictAddWord(kt, "");
    keysPredictAddWord(kt, " c");
    keysPredictAddWord(kt, "Canal ");

    // keysPredict - predecir palabras (Casos chicos)
    int* wordsCount;
    keysPredictRun(kt, "c", wordsCount); // Que pongo en wordsCount una direccion de memoria? Va con * o con &.
    keysPredictRun(kt, "ca", wordsCount);
    keysPredictRun(kt, "casa", wordsCount);
    keysPredictRun(kt, "casas", wordsCount);

    //Y si lo hacemos con un string vacio o con un string tal que ninguna palabra empiece asi
    keysPredictRun(kt, "", wordsCount);
    keysPredictRun(kt, "noq", wordsCount);
    keysPredictRun(kt, "RIN", wordsCount);
    keysPredictRun(kt, " ca", wordsCount);

    ////////////////////////////////////////////////////////////////64
    char* palabra = 0;
    for (int i=0; i<100; i++){
        palabra = ..., ¿Splir?, "\n",
        keysPredictAddWord(kt, palabra);
    }
    for (int i=0; i<50; i++){
        palabra = ..., ¿Splir?, "\n",
        keysPredictRemoveWord(kt, palabra);
    }


    // keysPredict - crear un diccionario
    keysPredictAddWord(kt, "papanatas");
    keysPredictAddWord(kt, "zanahoria");
    keysPredictAddWord(kt, "oreja");
    keysPredictAddWord(kt, "ricardo");
    keysPredictAddWord(kt, "zaz");
    keysPredictAddWord(kt, "a");
    keysPredictAddWord(kt, "");
    keysPredictAddWord(kt, "b");
    keysPredictAddWord(kt, "ab");
    keysPredictAddWord(kt, "abfff");
    keysPredictAddWord(kt, "abfgato");
    keysPredictAddWord(kt, "bebe");
    keysPredictAddWord(kt, "pata");
    keysPredictPrint(kt);

    // keysPredict - listar todas las palabras
    char** words;
    words = keysPredictListAll(kt, wordsCount);
    for(int i=0; i<wordsCount; i++) {
        printf("%s\n", words[i]);
    }
    deleteArrayOfWords(words, wordsCount);

    // keysPredict - encontrar palabras
    findAndPrintAll(kt, "papa");
    findAndPrintAll(kt, "pata");
    findAndPrintAll(kt, "a");
    findAndPrintAll(kt, "zazz");

    // keysPredict - predecir palabras
    predictAndPrintAll(kt,"or");
    predictAndPrintAll(kt,"ab");
    predictAndPrintAll(kt,"pa");
    predictAndPrintAll(kt,"pap");
    predictAndPrintAll(kt,"q");
    predictAndPrintAll(kt,"zap");

    // keysPredict - predecir palabras
    keysPredictRemoveWord(kt,"");
    keysPredictRemoveWord(kt,"zaz");
    keysPredictRemoveWord(kt,"aaa");
    keysPredictRemoveWord(kt,"papa");
    keysPredictRemoveWord(kt,"pata");
    keysPredictPrint(kt);

    // keysPredict - borrar diccionario
    keysPredictDelete(kt);

    return 0;
}
