#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "automate.h"

int contain(char* liste, char mot){
    int cpt =0;
    for(int i=0; i<sizeof(liste); i++){
        if( *(liste+i) == mot ) cpt++;
    }
    if( cpt> 0 ) return 1;
    else return 0;
} //On aura besoin de cette fonction plus tard, elle vérifie si une valeur est dans une liste ou non

int estReconnu(char* mot, Automate automate){                                       //Cette fonction renvoie 0(faux) ou 1(vrai)
    //Déclaration des variables
    char etat_Initial = automate.Initial_States.liste[0];
    int nb_Relations = automate.liste_Relations.taille;
    char* liste_To = NULL;

    // Code :
    for(int a=0; a<strlen(mot); a++){                                  //On parcourt les lettres de notre mot mais on s'arrete avant la dernière lettre
        char lettre = mot[a];                                              //On crée une variable lettre qui stocke la lettre du mot
        int cpt=0;
        if(a==0){                                                           //On gère le cas de la première lettre
            for(int b=0; b<nb_Relations; b++) if(automate.liste_Relations.liste[b].from == etat_Initial && automate.liste_Relations.liste[b].alphabet == lettre) cpt++;                                                         //Vérifie qu'en partant de l'état initial on peut obtenir la première lettre du mot
            liste_To = malloc(cpt* sizeof(char));
            int cpt2=0;
            for(int c=0; c<nb_Relations; c++){ 
                if(automate.liste_Relations.liste[c].from == etat_Initial && automate.liste_Relations.liste[c].alphabet == lettre){
                    *(liste_To+cpt2)=automate.liste_Relations.liste[c].to;
                    cpt2++;
                }
            }
            if(cpt2==0) return 0;
        }
        else{
            for(int b=0; b<nb_Relations; b++) if(contain(liste_To, automate.liste_Relations.liste[b].from) && automate.liste_Relations.liste[b].alphabet == lettre) cpt++;      //Récupère la taille de la liste qui va contenir les to 
            char* liste_To_2 = NULL;
            liste_To_2 = liste_To;
            liste_To = NULL;
            liste_To = malloc(cpt * sizeof(char));
            int cpt2=0;
            for(int c=0; c<nb_Relations; c++){ 
                if(contain(liste_To_2, automate.liste_Relations.liste[c].from) && automate.liste_Relations.liste[c].alphabet == lettre){
                    *(liste_To+cpt2)=automate.liste_Relations.liste[c].to;
                    cpt2++;
                }
            }
            if(cpt2==0) return 0;
        } 
    }
    for(int i=0; i<automate.Final_States.taille; i++){
        if( contain(liste_To, automate.Final_States.liste[i]) == 1 ) return 1;
    }
    return 0;
}

int main(){
    Automate automate;
    automate = getAutomate();
    char mot[3] = "aaa";
    printf("%d\n", estReconnu(mot, automate));
    return 0;
}

