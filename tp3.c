#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tp3.h"
#include <string.h>


/* ========== CREER SEMAINE ========== */
t_semaine_elt* creerSemaine(int num_semaine, int nb_vaccins){
    t_semaine_elt* nouvelleSemaine = malloc(sizeof(t_semaine_elt));
    if (nouvelleSemaine == NULL) {exit(EXIT_FAILURE);}

    nouvelleSemaine->nombre_vaccins = nb_vaccins;
    nouvelleSemaine->numero_semaine = num_semaine;
    nouvelleSemaine->suivant = NULL;

    return nouvelleSemaine;
}


/* ========== CREER VILLE ========== */
t_ville_elt* creerVille(char* ville, int num_semaine, int nb_vaccins){
    t_ville_elt* nouvelleVille = malloc(sizeof(t_ville_elt));
    if (nouvelleVille == NULL) {exit(EXIT_FAILURE);}

    nouvelleVille->nom_ville = strdup(ville);
    nouvelleVille->nombre_vaccins_total = nb_vaccins;
    nouvelleVille->semaines_planifiees = creerSemaine(num_semaine,nb_vaccins);
    nouvelleVille->suivant = NULL;

    return nouvelleVille;
}


/* ========== CREER VACCIN ========== */
t_vaccin_elt* creerVaccin(char* marque){
    t_vaccin_elt* nouveauVaccin = malloc(sizeof(t_vaccin_elt));
    if (nouveauVaccin == NULL) {exit(EXIT_FAILURE);}

    nouveauVaccin->marque = strdup(marque);
    nouveauVaccin->villes_dispo = NULL;
    return nouveauVaccin;
}


/* ========== AJOUT NB VACCIN DANS LISTE SEMAINES ========== */
t_semaine_elt* ajouterVaccinS(t_semaine_elt* liste, int semaine, int nb_vaccins){
    if(liste == NULL){
        liste = creerSemaine(semaine, nb_vaccins);
        return liste;
    }

    else{
        t_semaine_elt* ptr = liste;
        t_semaine_elt* prec_ptr = NULL;

        //Parcours liste
        while(ptr->suivant != NULL && ptr->numero_semaine < semaine){
            prec_ptr = ptr;
            ptr = ptr->suivant;
        }

        //Si la semaine existe dj
        if(semaine == ptr->numero_semaine){
            ptr->nombre_vaccins += nb_vaccins;
            return liste;
            }

        //Si la semaine n'existe pas
        else{
            t_semaine_elt* nouvelleSemaine = creerSemaine(semaine, nb_vaccins);

            //Cas 1 : Ajout en ddl
            if(prec_ptr==NULL && semaine < ptr->numero_semaine){
                    nouvelleSemaine->suivant = ptr;
                    liste = nouvelleSemaine;
                    return liste;
            }

            //Cas 2: Ajout en fdl
            else if(ptr->suivant==NULL && semaine>ptr->numero_semaine){
               ptr->suivant = nouvelleSemaine;
               return liste;
            }

            //Cas 3 : Ajout en mdl
            else if(prec_ptr!=NULL){
                nouvelleSemaine->suivant = ptr;
                prec_ptr->suivant = nouvelleSemaine;
                return liste;
            }
        }
    }
    return liste;
}


/* ========== RETRAIT NB VACCIN DE LISTE SEMAINES ========== */
t_semaine_elt* deduireVaccinS(t_semaine_elt *liste, int semaine, int nb_vaccins){
    if(liste == NULL){
        printf("Il n'y a pas de semaine programmee.\n");
        return liste;
    }
    else{
        t_semaine_elt* ptr = liste;
        t_semaine_elt* prec_ptr = NULL;

        //Parcours liste
        while(ptr->suivant != NULL && ptr->numero_semaine < semaine){
            prec_ptr = ptr;
            ptr = ptr->suivant;
        }

        //Si la semaine existe
        if(semaine == ptr->numero_semaine){
            if(ptr->nombre_vaccins > nb_vaccins){ //soustraction positive
                ptr->nombre_vaccins = ptr->nombre_vaccins - nb_vaccins;
                return liste;
            }

            else{
                //Cas 1 : Deduction en ddl
                if(prec_ptr==NULL){
                    liste=liste->suivant;
                    ptr->suivant=NULL;
                    return liste;
                }
                //Cas 2 : Deduction en mdl
                else if(prec_ptr!=NULL && ptr->suivant!=NULL){
                    prec_ptr->suivant=ptr->suivant;
                    ptr->suivant=NULL;
                    return liste;
                }

                //Cas 3: Deduction en fdl
                else if(ptr->suivant == NULL){
                    prec_ptr->suivant=NULL;
                    return liste;
                }
            }
        }
        else
            printf("\n La semaine en question n'existe pas");
        }
    return liste;
}


/* ========== AJOUT NB VACCIN DANS LISTE VILLES ========== */
t_ville_elt* ajouterVaccinV(t_ville_elt *liste, char* ville, int semaine, int nb_vaccins){
    t_ville_elt* ptr=liste;

    //AUCUNE VILLE
    if (ptr==NULL){
        liste=creerVille(ville, semaine, nb_vaccins);
        return liste;
    }

    //PARCOURS LISTE VILLES
    while (ptr->suivant != NULL && strcmp(ptr->nom_ville,ville)!=0){
        ptr=ptr->suivant;
    }//VILLE TROUVEE, OU PAS !


    if (strcmp(ptr->nom_ville,ville)!=0){//LA VILLE N'EXISTE PAS
        t_ville_elt* nv_ville = creerVille(ville, semaine, nb_vaccins);
        return ajout_ville(liste,nv_ville);
    }

    else{
        ptr->semaines_planifiees = ajouterVaccinS(ptr->semaines_planifiees,semaine,nb_vaccins);
        int futur_total = ptr->nombre_vaccins_total+nb_vaccins;

        if (ptr->suivant!=NULL && futur_total > ptr->suivant->nombre_vaccins_total)//s'il y a plus d'un elt ds liste ou si on n'est pas sur la derniere ville de la liste
            return tri_liste_villes_A(liste, ptr, futur_total);

        ptr->nombre_vaccins_total = futur_total;
    }
    return liste;
}


/* ========== RETRAIT NB VACCIN DE LISTE VILLES ========== */
t_ville_elt* deduireVaccinV(t_ville_elt *liste, char* ville, int semaine, int nb_vaccins){
    t_ville_elt* ptr=liste;
    t_ville_elt* prec_ptr=NULL;

    //AUCUNE VILLE
    if(ptr==NULL){
        printf("\nIl n'y a aucune ville pour ce vaccin.\n");
        return liste;
    }

    //PARCOURS LISTE VILLES
    while(ptr->suivant != NULL && strcmp(ptr->nom_ville,ville)!=0){
        prec_ptr=ptr;
        ptr=ptr->suivant;
    }//VILLE TROUVEE, OU PAS !

    if(strcmp(ptr->nom_ville,ville)!=0){
        printf("La ville n'existe pas\n");
        return liste;
    }
    else{

    if(trouver_semaine(ptr->semaines_planifiees,semaine) == 1){
        ptr->semaines_planifiees=renvoyer_semaine(ptr->semaines_planifiees,semaine);

        if (ptr->semaines_planifiees->nombre_vaccins <= nb_vaccins){
            ptr->semaines_planifiees = deduireVaccinS(ptr->semaines_planifiees,semaine,nb_vaccins);
            ptr->nombre_vaccins_total -= nb_vaccins;
            int total_vaccins = (int) ptr->nombre_vaccins_total;

            if (total_vaccins <= 0){ //suppression ville
                liste = deduire_Ville(liste,ville);
                return liste;
            }
            return liste;
        }

        ptr->semaines_planifiees = deduireVaccinS(ptr->semaines_planifiees,semaine,nb_vaccins);

        int futur_total = ptr->nombre_vaccins_total-nb_vaccins;

        if (prec_ptr!=NULL && futur_total <= prec_ptr->nombre_vaccins_total){//s'il y a plus d'un elt ds liste ou si on n'est pas sur la première ville de la liste
            return tri_liste_villes_D(liste, ptr, futur_total);
        }

        ptr->nombre_vaccins_total = futur_total;
    }
    printf("Il n'y a aucun vaccin dans cette semaine.\n");
    return liste;
 }
}


/* ========== AFFICHER STOCK PLANIFIE D'UN VACCIN ========== */
void afficherStock(t_vaccin_elt* vaccin){
    if(vaccin->villes_dispo==NULL){
        printf("Le stock de %s est vide.\n", vaccin->marque);
        return 0;
    }
    printf("%s : \n",vaccin->marque);
    t_ville_elt* ptr_ville=vaccin->villes_dispo;

    while(ptr_ville != NULL){
        t_semaine_elt* ptr_semaine=ptr_ville->semaines_planifiees;
        printf(" --- %s [Total = %d]\n",ptr_ville->nom_ville,ptr_ville->nombre_vaccins_total);

        while(ptr_semaine != NULL){
            printf("     semaine %d : %d \n",ptr_semaine->numero_semaine,ptr_semaine->nombre_vaccins);
            ptr_semaine=ptr_semaine->suivant;
        }
        ptr_ville=ptr_ville->suivant;
    }
}


/* ========== AFFICHER STOCK D'UN VACCIN POUR UNE SEMAINE ========== */
void afficherPlanification(t_vaccin_elt* vaccin,int semaine){
    int affiche_num_sem=0;
    int sem_existe=0;
    t_ville_elt* ptr_ville=vaccin->villes_dispo;

    while(ptr_ville != NULL){
        t_semaine_elt* ptr_semaine = ptr_ville->semaines_planifiees;
        if(trouver_semaine(ptr_semaine, semaine)==0){
                ptr_ville=ptr_ville->suivant;
                continue;
        }
        if(affiche_num_sem==0){
            printf("%s : \n",vaccin->marque);
            printf(" --- semaine %d \n",semaine);
            affiche_num_sem=1;
        }
        while(ptr_semaine != NULL){
            if (ptr_semaine->numero_semaine == semaine){
                sem_existe=1;
                printf("     --- %s : %d \n",ptr_ville->nom_ville, ptr_semaine->nombre_vaccins);
            }
            ptr_semaine=ptr_semaine->suivant;
        }
        ptr_ville=ptr_ville->suivant;
    }
    if(sem_existe==0){
        printf("La semaine n'existe pas.\n");
    }
}


/* ========== FUSION DEUX VACCINS ========== */

t_vaccin_elt* fusionnerStocks(t_vaccin_elt* vaccinA, t_vaccin_elt* vaccinB){
    char* marque = strdup(vaccinA->marque);
    strcat(marque,"_");
    strcat(marque,vaccinB->marque);

    t_vaccin_elt* newVacc = creerVaccin(marque);

    newVacc->villes_dispo=ajoutVaccin(newVacc,vaccinA);
    newVacc->villes_dispo=ajoutVaccin(newVacc,vaccinB);

    return newVacc;
}


/* ----------------------------------
 *   UTILITAIRES
 ---------------------------------- */


void viderBuffer(){
    char c;
    do {
        c = getchar();
    } while (c != '\n' && c != EOF);
}


bool verifVaccSem(int semaine, int nb_vaccins){
    if((semaine<1 || semaine>53) || nb_vaccins<1){
        printf("Le numero de semaine ou le nombre de vaccins est invalide.\n");
        return 0;
    }
    return 1;
}


bool trouver_ville(t_ville_elt *liste, char* ville){ //la ville existe dans liste ?
    if (liste==NULL)
        return 0; //FAUX
    else{
        while(liste->suivant!=NULL && strcmp(liste->nom_ville,ville)!=0){
            liste=liste->suivant;
        }
        if (strcmp(liste->nom_ville,ville)==0)
            return 1;//VRAI
        else
            return 0;
    }
}


t_ville_elt* tri_liste_villes_A(t_ville_elt* liste, t_ville_elt* ville, int futur_total){//ajout ville ds liste, et tri liste
    t_ville_elt* ptr = liste;
    t_ville_elt* prec_ptr = NULL;
    t_ville_elt* prec_ville = liste;

    //Parcours de la liste
    while(ptr->suivant != NULL && ptr->nombre_vaccins_total < futur_total){
        prec_ptr = ptr;
        ptr = ptr->suivant;
    }

    //Cas 1: premiere ville
    if(liste->nom_ville==ville->nom_ville){
        if(ptr->suivant==NULL && futur_total >= ptr->nombre_vaccins_total){
            liste=liste->suivant;
            ptr->suivant=ville;
            ville->suivant=NULL;
            ville->nombre_vaccins_total=futur_total;
            return liste;
        }
        if(prec_ptr!=NULL){
            liste=liste->suivant;
            prec_ptr->suivant=ville;
            ville->suivant=ptr;
            ville->nombre_vaccins_total=futur_total;
            return liste;
        }
    }

    //Cas 2 : ville du milieu en fdl
    else if(ptr->suivant==NULL && futur_total > ptr->nombre_vaccins_total){
       while(strcmp(prec_ville->suivant->nom_ville, ville->nom_ville)!=0)
            prec_ville = prec_ville->suivant;

        prec_ville->suivant = ville->suivant;
        ptr->suivant = ville;
        ville->suivant = NULL;
        ville->nombre_vaccins_total=futur_total;
        return liste;
    }

    //Cas 3 : ville du milieu au milieu
    else if(prec_ptr!=NULL){
        while(strcmp(prec_ville->suivant->nom_ville, ville->nom_ville)!=0)
            prec_ville = prec_ville->suivant;
        prec_ville->suivant = ville->suivant;
        ville->suivant = ptr;
        prec_ptr->suivant = ville;
        ville->nombre_vaccins_total=futur_total;
        return liste;
    }
    return liste;
}


t_ville_elt* ajout_ville(t_ville_elt* liste, t_ville_elt* ville){//ajout ville ds liste, et tri liste
    t_ville_elt* ptr = liste;
    t_ville_elt* prec_ptr = NULL;

    //Parcours de la liste
    while(ptr->suivant != NULL && ptr->nombre_vaccins_total < ville->nombre_vaccins_total){
        prec_ptr = ptr;
        ptr = ptr->suivant;
    }

    //Cas 2 : Ajout en dbut de liste
    if(prec_ptr==NULL && ville->nombre_vaccins_total <= ptr->nombre_vaccins_total){
        ville->suivant = ptr;
        liste = ville;
        return liste;
    }

    //Cas 3 : Ajout en fin de liste
    else if(ptr->suivant==NULL && ville->nombre_vaccins_total > ptr->nombre_vaccins_total){
        ptr->suivant = ville;
        ville->suivant = NULL;
        return liste;
    }

    //Cas 4 : Ajout en "milieu" de liste
    else if(prec_ptr!=NULL /*&& ptr->suivant!=NULL*/){
        ville->suivant = ptr;
        prec_ptr->suivant = ville;
        return liste;
    }
    return liste;
}


t_ville_elt* tri_liste_villes_D(t_ville_elt* liste, t_ville_elt* ville, int futur_total){//ajout ville ds liste, et tri liste
    t_ville_elt* ptr = liste;
    t_ville_elt* prec_ptr = NULL;
    t_ville_elt* prec_ville = liste;

    //Parcours de la liste
    while(ptr != NULL && ptr->nombre_vaccins_total < futur_total){
        prec_ptr = ptr;
        ptr = ptr->suivant;
    }
    while(prec_ville !=NULL && strcmp(prec_ville->suivant->nom_ville,ville->nom_ville)!=0){
          prec_ville=prec_ville->suivant;
    }

    //Cas 1: on bouge la derniere ville
    if(ville->suivant==NULL){
        if(prec_ptr==NULL){//soit on place notre ville en debut de liste
            prec_ville->suivant=NULL;
            ville->suivant=liste;
            liste = ville;
            ville->nombre_vaccins_total=futur_total;
            return ville;
        }
        if(prec_ptr!=NULL){
            prec_ville->suivant=NULL;
            prec_ptr->suivant=ville;
            ville->suivant=ptr;
            ville->nombre_vaccins_total=futur_total;
            return liste;
        }
    }

    //Cas 2 : on bouge une ville du milieu en ddl
    else if(prec_ptr==NULL && futur_total < ptr->nombre_vaccins_total){
        prec_ville->suivant = ville->suivant;
        ville->suivant=ptr;
        liste = ville;
        ville->nombre_vaccins_total=futur_total;
        return ville;
    }

    //Cas 3 : on bouge une ville du milieu au milieu
    else if(prec_ptr!=NULL){
        prec_ville->suivant = ville->suivant;
        ville->suivant = ptr;
        prec_ptr->suivant = ville;
        ville->nombre_vaccins_total=futur_total;
        return liste;
    }
    return liste;
}


t_ville_elt* deduire_Ville(t_ville_elt* liste, char* ville){
    t_ville_elt* ptr = liste;
    t_ville_elt* prec_ptr = NULL;

    //Parcours de la liste
    while(ptr->suivant!=NULL && strcmp(ptr->nom_ville,ville)!=0){
        prec_ptr = ptr;
        ptr = ptr->suivant;
    }
    if (strcmp(ptr->nom_ville,ville)==0)
    {
        //Cas 1 : Deduction en dbut de liste
        if(prec_ptr==NULL){
            liste=liste->suivant;
            ptr->suivant=NULL;
        }
        //Cas 2 : Deduction en "milieu" de liste
        else if(prec_ptr!=NULL && ptr->suivant!=NULL){
            prec_ptr->suivant=ptr->suivant;
            ptr->suivant=NULL;
        }

        //Cas 3: Deduction en fin de liste
        else if(ptr->suivant == NULL){
            prec_ptr->suivant=NULL;
        }
    }
    else
        printf("\nLa ville en question n'existe pas");
    return liste;
}


bool trouver_semaine(t_semaine_elt* liste,int semaine){
    t_semaine_elt* ptr=liste;
    while(ptr!=NULL){
        if(ptr->numero_semaine == semaine)
            return 1;
        ptr=ptr->suivant;
    }
    return 0;
}


t_semaine_elt* renvoyer_semaine(t_semaine_elt* liste,int semaine){
    t_semaine_elt* ptr=liste;
    while(ptr!=NULL){
        if(liste->numero_semaine == semaine)
            return ptr;
        ptr=ptr->suivant;
    }
    printf("Il n'y a aucun vaccin dans cette semaine\n");
    return liste;
}


t_ville_elt* ajoutVaccin(t_vaccin_elt* vaccinA, t_vaccin_elt* vaccinB){
    t_ville_elt* ptr_vaccinBV = vaccinB->villes_dispo;
    t_semaine_elt* ptr_vaccinBS = NULL;

    while (ptr_vaccinBV != NULL){
        ptr_vaccinBS = ptr_vaccinBV->semaines_planifiees;
        vaccinA->villes_dispo = ajouterVaccinV(vaccinA->villes_dispo,ptr_vaccinBV->nom_ville,ptr_vaccinBS->numero_semaine,ptr_vaccinBS->nombre_vaccins);
        while(ptr_vaccinBS->suivant != NULL){
            ptr_vaccinBS = ptr_vaccinBS->suivant;
            vaccinA->villes_dispo = ajouterVaccinV(vaccinA->villes_dispo,ptr_vaccinBV->nom_ville,ptr_vaccinBS->numero_semaine,ptr_vaccinBS->nombre_vaccins);
        }
        ptr_vaccinBV = ptr_vaccinBV->suivant;
    }
    return vaccinA->villes_dispo;
}


void vider_tableau_vacc(t_vaccin_elt* tabl_vacc[10]){
    t_vaccin_elt* ptr_vacc;
    for (int i=0;i<10;i++){
        ptr_vacc=tabl_vacc[i];
        if (tabl_vacc[i] !=NULL){
            vider_vaccin(tabl_vacc[i]);
            free(tabl_vacc[i]->marque);
            free(tabl_vacc[i]);
        }
        tabl_vacc[i]=NULL;
    }
}


void vider_vaccin(t_vaccin_elt* vacc){
    t_ville_elt* ptr_ville=vacc->villes_dispo;

    while(ptr_ville!=NULL){
            t_ville_elt*   ptr_ville_prec=ptr_ville;
            t_semaine_elt* ptr_semaine=ptr_ville->semaines_planifiees;
            while(ptr_semaine!= NULL){
                t_semaine_elt* ptr_semaine_prec=ptr_semaine;

                ptr_semaine=ptr_semaine->suivant;
                free(ptr_semaine_prec);
            }
            ptr_ville=ptr_ville->suivant;
            free(ptr_ville_prec->nom_ville);
            free(ptr_ville_prec);
        }
    free(ptr_ville->nom_ville);
    free(ptr_ville);
}


void trier_vaccins(t_vaccin_elt* GESTION_VACCINS[10], int i){
    if(GESTION_VACCINS[i]->villes_dispo==NULL){
        printf("On retire le vaccin du tableau.\n");
        int j=i+1;
        while(GESTION_VACCINS[j]!=NULL){
            j++;
        }
        GESTION_VACCINS[i]=GESTION_VACCINS[j-1];
        GESTION_VACCINS[j-1]=NULL;
    }
}













