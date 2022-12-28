#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "automate.h"

typedef struct EtatLettre EtatLettre;
struct EtatLettre
{
    char etat;
    char lettre;  
};

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

int estDansListe(char a, char* liste, int tailleListe){
    int cpt=0;
    for(int i=0; i<tailleListe; i++) if(a==*(liste+i)) cpt++;
    if(cpt>0) return 1;
    else return 0;
}

Automate rendreComplet(Automate automate){
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
    //Récupérons maintenant les états qui n'ont pas au moins une relation sortante avec toutes les lettres de l'alphabet - D'abord je récupère la taille de la liste (cpt2)
    int taille_liste=0;
    int cpt1, cpt2 = 0;
    for(int k=0; k<nb_etats_differents; k++){
        for(int l=0; l<automate.alphabet.tailleAlphabet; l++){
            cpt1=0;
            for(int m=0; m<automate.liste_Relations.taille; m++){
                if(*(liste_etats+k)==automate.liste_Relations.liste[m].from && automate.alphabet.listeAlphabet[l]==automate.liste_Relations.liste[m].alphabet){cpt1++; break;} 
            }
            if(cpt1==0) cpt2++;
        }
    }
    //Je récupère mnt dans une liste (liste_etat_lettre) les etats associés à leur lettre manquante
    EtatLettre* liste_etat_lettre = NULL;
    liste_etat_lettre=malloc(cpt2*2*sizeof(char));
    int index=0;
    for(int k=0; k<nb_etats_differents; k++){
        for(int l=0; l<automate.alphabet.tailleAlphabet; l++){
            cpt1=0;
            for(int m=0; m<automate.liste_Relations.taille; m++){
                if(*(liste_etats+k)==automate.liste_Relations.liste[m].from && automate.alphabet.listeAlphabet[l]==automate.liste_Relations.liste[m].alphabet){cpt1++; break;}
            }
            if(cpt1==0){
                liste_etat_lettre[index].etat=*(liste_etats+k); 
                liste_etat_lettre[index].lettre=automate.alphabet.listeAlphabet[l];
                index++;
            } 
        }
    }
    int taille_liste_etat_lettre=index;
    //Création d'un état puit qui va venir recevoir toutes les relations manquantes
    char etat_puit=*(liste_etats+(nb_etats_differents-1))+1;                            //J'ai crée un état puit
    FILE* fichier = NULL; 
    fichier=fopen("automate.txt", "r+");
    fseek(fichier, 0, SEEK_END);                                                        //On se place à la fin du fichier
    //Ecris les relations vers l'état puit
    for(int i=0; i<taille_liste_etat_lettre; i++){
        fprintf(fichier,"\n%c,%c,%c;",liste_etat_lettre[i].etat, etat_puit, liste_etat_lettre[i].lettre);
    }
    //Ecris les relations de l'état puis vers lui-même
    for(int i=0; i<automate.alphabet.tailleAlphabet; i++){
        fprintf(fichier, "\n%c,%c,%c;", etat_puit, etat_puit, automate.alphabet.listeAlphabet[i]);
    }
    fclose(fichier);
    automate=getAutomate();
    return automate;
}    

int main(){
    Automate automate;
    automate=getAutomate();
    automate=rendreComplet(automate);
    printAutomaton(automate);
    return 0;
}