#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "automate.h"

char* sort(char* array, int size){                                             //fonction qui permet de ranger une liste dans l'odre croissant 
   for(int i = 0; i < size - 1; i++)
   {
      for(int j = 0; j < size - i - 1; j++)
      {
         if(*(array+j) > *(array+j+1))
         {
            int temp = *(array+j);
            *(array+j) = *(array+j+1);
            *(array+j+1) = temp;
         }
      }
   }
   return array;
}

int nbValeursDifferentes(char* array, int size){                              //fonction qui permet de compter le nombre de valeurs uniques dans une liste 
    array=sort(array, size);
    int cpt=0;
    for(int i=0; i<size; i++){
        if(i==0) cpt++;
        else{
            if(*(array+i)!=*(array+i-1)) cpt++;
        }
    }
    return cpt;
}

char* liste_valeurs_uniques(char* array, int size){                             //Fonction qui permet de renvoyer une liste ou l'on a supprimé les doublons
    array=sort(array, size);
    char* new_array = NULL;
    new_array=malloc(nbValeursDifferentes(array, size)*sizeof(char));
    int cpt=0;
    for(int i=0; i<size; i++){
        if(i==0){
            *(new_array+i)=*(array+i);
            cpt++;
        }
        else{
            if(*(array+i)!=*(array+i-1)){
                *(new_array+cpt)=*(array+i);
                cpt++;
            } 
        }
    }
    return new_array;
}


int estComplet(Automate automate){
    //Phase préparatoire 

    int nb_etats_differents=0;
    char* liste_from_to = NULL;
    liste_from_to=malloc(2*automate.liste_Relations.taille*sizeof(char));
    //Ces boucles for servent à récupérer les diffénrents états dans notre AEF, on utilise ensuite no
    for(int i=0; i<automate.liste_Relations.taille; i++){
        *(liste_from_to+i)=automate.liste_Relations.liste[i].from; 
    }
    int a = 0;
    for(int j=automate.liste_Relations.taille; j<2*automate.liste_Relations.taille; j++){
        *(liste_from_to+j)=automate.liste_Relations.liste[a].to;
        a++;
    }
    nb_etats_differents=nbValeursDifferentes(liste_from_to, 2*automate.liste_Relations.taille);                        //Nous donne la taille de la liste from to donc le nombre d'états dans l'AEF
    char* liste_etats = NULL;
    liste_etats = malloc(nb_etats_differents*sizeof(char));
    liste_etats=liste_valeurs_uniques(liste_from_to, 2*automate.liste_Relations.taille);                               //J'ai enfin récupéré la liste de tous les états dans mon AEF
    
    //CODE
    int cpt=0;
    for(int k=0; k<automate.alphabet.tailleAlphabet; k++){
        for(int l=0; l<nb_etats_differents; l++){
            for(int m=0; m<automate.liste_Relations.taille; m++) if( automate.liste_Relations.liste[m].from==*(liste_etats+l) && automate.liste_Relations.liste[m].alphabet== automate.alphabet.listeAlphabet[k] ){
                cpt++;
                break;
            }
        }
    }
    if(cpt==(nb_etats_differents*automate.alphabet.tailleAlphabet)) return 1;
    else return 0;
}


int main(){
    Automate automate;
    automate=getAutomate();
    printf("estComplet? %d ",estComplet(automate));
}