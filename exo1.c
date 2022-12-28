#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>


#include "header/exo1.h"
#include "header/tools.h"

#define FALSE 1
#define TRUE 0


//fonctions exo1
//a
int appartenir(char string[], char alphabet[]){
  int n = strlen(string);
  int m = strlen(alphabet);
  int cpt=0;
  for(int i = 0; i<n; i++){
    for(int j = 0; j<m; j++){
      if(string[i]==alphabet[j])
        cpt = cpt+1;
    }
    if(cpt > 0){
      i=i+1;
      cpt = 0;
    }
    else
      return FALSE;
  }
  return TRUE;
}

//d
char *concat(char *s1, char *s2){
  char *result = NULL;
  // +1 for the null-terminator \0 à la fin du string dans l'espace mémoire
  result = malloc(sizeof(char) * (strlen(s1) + strlen(s2) + 1)); 
  checkMallocIsWorking(result);
  strcpy(result, s1);
  strcat(result, s2);
  return result;
}

//b
char *puis(char *string, int puissance){
  if(puissance == 0){
    string = ""; 
    return string;
  }
  char *init_string = string;
  for(int i=0; i<puissance-1; i++)
    string = concat(string, init_string);
  return string;
}

//c
int vide(char *string){
  if(strlen(string) == 0)
    return TRUE;
  return FALSE;
}



//e
char *mirror(char string[]){
  // *string=string[]
  int i, j = 0;
  int k = strlen(string); 
  char *mirrorString = NULL;
  mirrorString = malloc(sizeof(char) * (k + 1)); //+1  car \0 à la fin du string (zone mémoire)
  checkMallocIsWorking(mirrorString);
  for(i=k-1; i>=0; i--) //k-1 car \0 à la fin du string (zone mémoire)
    mirrorString[j++] = string[i];
  return mirrorString;
}

//f
int isFinite(char *string){
  for(int i=0; i<strlen(string); i++){
    if(string[i] == '*')
      return FALSE;
  }
  return TRUE;
}

// int main(){
//   char *a="yo";
//   printf("%d\n",vide(a));

//   return 0;
// }