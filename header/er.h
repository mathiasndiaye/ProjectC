#ifndef ER_H
#define ER_H
#include <stdio.h>


//normes du fichier 
void standardERfile(char *fileName, char *lectureMode, FILE *file);

//prototype fonctions utilisateurs
void seizeER(char *ER);
void isCorrectUserER(char *ER);

//prototype fonctions fichiers
void importERfromFile(char *buffer, char *fileName, FILE *file);
void modifyERinFile(char *fileName, FILE *file);
void isCorrectFileER(char *ER, char *fileName, FILE *file);
void manipulateERfromFile(char *importedER, char *fileName, char *lectureMode, FILE *erFile);


void isWordRecognizedByER(char *ER);

#endif