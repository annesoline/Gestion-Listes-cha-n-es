#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "tp3.h"
#include <string.h>
#define NMAX 80

int main()
{
    t_vaccin_elt* GESTION_VACCINS[10] = {NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL,NULL};

    char marque[NMAX];
    char nom_ville[NMAX];
    int numero_sem=0;
    int nb_vaccins=0;
    int i=0;
    int j=1;
    int l=1;
    int stop=0;
    t_vaccin_elt* vaccinA = NULL;
    t_vaccin_elt* vaccinB = NULL;
    t_vaccin_elt* vaccinC = NULL;
    int a;
    int b;
    int c;


    char choix = '0';
    while (choix != '7') {
        printf("\n======================================");
        printf("\n1. Initialiser la liste des marques de vaccin disponibles");
        printf("\n2. Ajouter et planifier un stock");
        printf("\n3. Retirer un nombre de vaccins du stock");
        printf("\n4. Afficher le stock d'un vaccin");
        printf("\n5. Afficher la planification pour une semaine");
        printf("\n6. Fusionner deux stocks");
        printf("\n7. Quitter");
        printf("\n======================================");
        printf("\n   Votre choix ? ");
        choix = getchar();
        viderBuffer();

        switch (choix) {
            case '1' :
                printf("\n===INITIALISER VACCINS===\n");
                for(int i=0; i<10; i++){
                    if(GESTION_VACCINS[9]!=NULL){
                        printf("\nLe tableau est plein. Pour en ajouter, veuillez retirer l'un des vaccins suivants : \n");
                        for(int i=0; i<10; i++){
                            printf("- %s\n", GESTION_VACCINS[i]->marque);
                        }
                        break;
                    }
                    printf("\nEntrez la marque du vaccin ou 0 pour sortir : ");
                    gets(marque);
                    if(strlen(marque)>20){
                        printf("Le nom de la marque est trop long\n");
                        break;
                    }
                    if(strcmp(marque, "0")==0){
                        break;
                    }
                    int m=0;
                    while(m<10 && GESTION_VACCINS[m]!=NULL){
                        if(strcmp(GESTION_VACCINS[m]->marque,marque)==0){
                            printf("!!! Le vaccin existe deja !!!\n");
                            stop=1;
                            break;
                        }else{ m++; }
                    }
                    if(stop){
                        stop=0;
                        break;
                    }
                    GESTION_VACCINS[m]=creerVaccin(marque);
                    if(GESTION_VACCINS[9]!=NULL){
                        printf("\nLe tableau des vaccins est maintenant plein.\n");
                        break;
                    }
                }
                break;

            case '2' :
                printf("\n===AJOUTER VACCINS===\n");
                while(j==1 || j==2 || j==3){
                    if(j==1){
                        i=0;
                        int m=0;
                        int none_exist=0;
                        printf("\nEntrez le nom du vaccin : ");
                        gets(marque);
                        if(strlen(marque)>20){
                            printf("Le nom de la marque est trop long.\n");
                            break;
                        }
                        printf("Entrez le nom de la ville : ");
                        gets(nom_ville);
                        if(strlen(nom_ville)>20){
                            printf("Le nom de la ville est trop long.\n");
                            break;
                        }
                        printf("Entrez le numero de la semaine : ");
                        scanf("%d", &numero_sem);
                        printf("Entrez le nombre de vaccins : ");
                        scanf("%d", &nb_vaccins);
                        if(verifVaccSem(numero_sem, nb_vaccins)){
                            if(GESTION_VACCINS[0]== NULL){ //cas où notre liste est nulle
                                GESTION_VACCINS[m]=creerVaccin(marque);
                                GESTION_VACCINS[m]->villes_dispo=ajouterVaccinV(GESTION_VACCINS[m]->villes_dispo,nom_ville,numero_sem,nb_vaccins);
                                break;
                            }else{
                                while(i<10 && GESTION_VACCINS[i]!=NULL && strcmp(GESTION_VACCINS[i]->marque,marque)!=0){
                                    i++;
                                }
                                if(i<10 && GESTION_VACCINS[i]==NULL){
                                    printf("Le vaccin n'existe pas, on l'ajoute au tableau.\n");
                                    none_exist=1;
                                    m=0;
                                    while(m<10){
                                        if(GESTION_VACCINS[m]==NULL){
                                            GESTION_VACCINS[m]=creerVaccin(marque);
                                            GESTION_VACCINS[m]->villes_dispo=ajouterVaccinV(GESTION_VACCINS[m]->villes_dispo,nom_ville,numero_sem,nb_vaccins);
                                            break;
                                        }else{ m++; }
                                    }
                                }
                                if(i>9 && GESTION_VACCINS[9]!=NULL){
                                    printf("\nLe tableau est plein. Pour en ajouter, veuillez retirer l'un des vaccins suivants : \n");
                                    for(int i=0; i<10; i++){
                                        printf("- %s\n", GESTION_VACCINS[i]->marque);
                                    }
                                    viderBuffer();
                                    j=1;
                                    break;
                                }
                                GESTION_VACCINS[i]->villes_dispo = ajouterVaccinV(GESTION_VACCINS[i]->villes_dispo, nom_ville, numero_sem, nb_vaccins);
                                printf("\nTapez 1 si vous souhaitez ajouter d'autres vaccins d'une autre marque\n");
                                printf("Tapez 2 si vous souhaitez ajouter d'autres vaccins de la meme marque mais dans une ville differente\n");
                                printf("Tapez 3 si vous souhaitez ajouter d'autres vaccins de la meme marque et dans la meme ville\n");
                                printf("Tapez 0 si vous ne souhaitez plus ajouter de vaccins\n");
                                scanf("%d", &j);
                                viderBuffer();
                            }
                        }
                    }
                    else if(j==2){//même marque, ville différente
                        printf("\nEntrez le nom de la ville : ");
                        scanf("%s", nom_ville);
                        if(strlen(marque)>20){
                            printf("Le nom de la marque est trop long.\n");
                            break;
                        }
                        printf("Entrez le numero de la semaine : ");
                        scanf("%d", &numero_sem);
                        printf("Entrez le nombre de vaccins : ");
                        scanf("%d", &nb_vaccins);
                        if(verifVaccSem(numero_sem, nb_vaccins)){
                            GESTION_VACCINS[i]->villes_dispo = ajouterVaccinV(GESTION_VACCINS[i]->villes_dispo, nom_ville, numero_sem, nb_vaccins);
                            printf("\nTapez 1 si vous souhaitez ajouter d'autres vaccins d'une autre marque\n");
                            printf("Tapez 2 si vous souhaitez ajouter d'autres vaccins de la meme marque mais dans une ville differente\n");
                            printf("Tapez 3 si vous souhaitez ajouter d'autres vaccins de la meme marque et dans la meme ville\n");
                            printf("Tapez 0 si vous ne souhaitez plus ajouter de vaccins\n");
                            scanf("%d", &j);
                            viderBuffer();
                        }
                    }
                    else if(j==3){//même marque, même ville
                        printf("\nEntrez le numero de la semaine : ");
                        scanf("%d", &numero_sem);
                        printf("Entrez le nombre de vaccins : ");
                        scanf("%d", &nb_vaccins);
                        if(verifVaccSem(numero_sem, nb_vaccins)){
                            GESTION_VACCINS[i]->villes_dispo = ajouterVaccinV(GESTION_VACCINS[i]->villes_dispo, nom_ville, numero_sem, nb_vaccins);
                            printf("\nTapez 1 si vous souhaitez ajouter d'autres vaccins d'une autre marque\n");
                            printf("Tapez 2 si vous souhaitez ajouter d'autres vaccins de la meme marque mais dans une ville differente\n");
                            printf("Tapez 3 si vous souhaitez ajouter d'autres vaccins de la meme marque et dans la meme ville\n");
                            printf("Tapez 0 si vous ne souhaitez plus ajouter de vaccins\n");
                            scanf("%d", &j);
                            viderBuffer();
                        }
                    }
                }
                j=1;
                break;

            case '3' :
                printf("\n===RETIRER VACCINS===\n");
                while(j==1 || j==2 || j==3){
                    if(j==1){
                        i=0;
                        printf("\nEntrez le nom du vaccin : ");
                        gets(marque);
                        if(strlen(marque)>20){
                            printf("Le nom de la marque est trop long et donc n'existe pas.\n");
                            break;
                        }
                        printf("Entrez le nom de la ville : ");
                        gets(nom_ville);
                        if(strlen(nom_ville)>20){
                            printf("Le nom de la ville est trop long.\n");
                            break;
                        }
                        printf("Entrez le numero de la semaine : ");
                        scanf("%d", &numero_sem);
                        printf("Entrez le nombre de vaccins : ");
                        scanf("%d", &nb_vaccins);
                        if(verifVaccSem(numero_sem, nb_vaccins)){
                            while(strcmp(GESTION_VACCINS[i]->marque,marque)!=0){
                            i++;
                            if(i>9 || GESTION_VACCINS[i]==NULL){
                                printf("!!! Le vaccin n'existe pas !!!\n");
                                break;
                            }
                            }
                            if(i>9 || GESTION_VACCINS[i]==NULL){
                                viderBuffer();
                                j=1;
                                break;
                            }
                            GESTION_VACCINS[i]->villes_dispo = deduireVaccinV(GESTION_VACCINS[i]->villes_dispo, nom_ville, numero_sem, nb_vaccins);
                            trier_vaccins(GESTION_VACCINS, i);
                            printf("\nTapez 1 si vous souhaitez deduire d'autres vaccins d'une autre marque\n");
                            printf("Tapez 2 si vous souhaitez deduire d'autres vaccins de la meme marque mais dans une ville differente\n");
                            printf("Tapez 3 si vous souhaitez deduire d'autres vaccins de la meme marque et dans la meme ville\n");
                            printf("Tapez 0 si vous ne souhaitez plus deduire de vaccins\n");
                            scanf("%d", &j);
                            viderBuffer();
                        }
                    }
                    else if(j==2){//même marque, ville différente
                        printf("\nEntrez le nom de la ville : ");
                        gets(nom_ville);
                        if(strlen(nom_ville)>20){
                            printf("Le nom de la ville est trop long.\n");
                            break;
                        }
                        printf("Entrez le numero de la semaine : ");
                        scanf("%d", &numero_sem);
                        printf("Entrez le nombre de vaccins : ");
                        scanf("%d", &nb_vaccins);
                        if(verifVaccSem(numero_sem, nb_vaccins)){
                            GESTION_VACCINS[i]->villes_dispo = deduireVaccinV(GESTION_VACCINS[i]->villes_dispo, nom_ville, numero_sem, nb_vaccins);
                            trier_vaccins(GESTION_VACCINS, i);
                            printf("\nTapez 1 si vous souhaitez deduire d'autres vaccins d'une autre marque\n");
                            printf("Tapez 2 si vous souhaitez deduire d'autres vaccins de la meme marque mais dans une ville differente\n");
                            printf("Tapez 3 si vous souhaitez deduire d'autres vaccins de la meme marque et dans la meme ville\n");
                            printf("Tapez 0 si vous ne souhaitez plus deduire de vaccins\n");
                            scanf("%d", &j);
                            viderBuffer();
                        }
                    }
                    else if(j==3){//même marque, même ville
                        printf("\nEntrez le numero de la semaine : ");
                        scanf("%d", &numero_sem);
                        printf("Entrez le nombre de vaccins : ");
                        scanf("%d", &nb_vaccins);
                        if(verifVaccSem(numero_sem, nb_vaccins)){
                            GESTION_VACCINS[i]->villes_dispo = deduireVaccinV(GESTION_VACCINS[i]->villes_dispo, nom_ville, numero_sem, nb_vaccins);
                            trier_vaccins(GESTION_VACCINS, i);
                            printf("\nTapez 1 si vous souhaitez deduire d'autres vaccins d'une autre marque\n");
                            printf("Tapez 2 si vous souhaitez deduire d'autres vaccins de la meme marque mais dans une ville differente\n");
                            printf("Tapez 3 si vous souhaitez deduire d'autres vaccins de la meme marque et dans la meme ville\n");
                            printf("Tapez 0 si vous ne souhaitez plus deduire de vaccins\n");
                            scanf("%d", &j);
                            viderBuffer();
                        }
                    }
                }
                j=1;
                break;

            case '4' :
                printf("\n===STOCK VACCINS===\n");
                while(1){
                    i=0;
                    printf("\nEntrez le nom du vaccin dont vous souhaitez consulter le stock ou 0 pour sortir : ");
                    gets(marque);
                    if(strlen(marque)>20){
                        printf("Le nom de la marque est trop long et donc n'existe pas.\n");
                        break;
                    }
                    if(strcmp(marque, "0")==0){
                        break;
                    }
                    while(strcmp(GESTION_VACCINS[i]->marque,marque)!=0){
                        i++;
                        if(i>9 || GESTION_VACCINS[i]==NULL){
                                printf("!!! Le vaccin n'existe pas !!!\n");
                                break;
                            }
                    }
                    if(i>9 || GESTION_VACCINS[i]==NULL){
                        break;
                    }
                    afficherStock(GESTION_VACCINS[i]);
                }
                break;

            case '5' :
                printf("\n===PLANIFICATION VACCINS===\n");
                while(l==1 || l==2){
                    if(l==1){
                        i=0;
                        printf("\nEntrez le nom du vaccin dont vous souhaitez consulter le stock : ");
                        gets(marque);
                        if(strlen(marque)>20){
                            printf("Le nom de la marque est trop long et donc n'existe pas.\n");
                            break;
                        }
                        while(strcmp(GESTION_VACCINS[i]->marque,marque)!=0){
                            i++;
                            if(i>9 || GESTION_VACCINS[i]==NULL){
                                printf("!!! Le vaccin n'existe pas !!!\n");
                                break;
                            }
                        }
                        if(i>9 || GESTION_VACCINS[i]==NULL){
                            viderBuffer();
                            break;
                        }
                        printf("Entrez le numero de la semaine dont vous souhaitez consulter la planification : ");
                        scanf("%d", &numero_sem);
                        afficherPlanification(GESTION_VACCINS[i], numero_sem);
                        printf("\nTapez 1 si vous souhaitez consulter d'autres planifications d'un autre vaccin.\n");
                        printf("Tapez 2 si vous souhaitez consulter d'autres planifications du meme vaccin.\n");
                        printf("Tapez 0 si vous ne souhaitez plus consulter de planifications.\n");
                        scanf("%d", &l);
                        viderBuffer();
                    }
                    else if(l==2){
                        printf("\nEntrez le numero de la semaine dont vous souhaitez consulter la planification : ");
                        scanf("%d", &numero_sem);
                        afficherPlanification(GESTION_VACCINS[i], numero_sem);
                        printf("\nTapez 1 si vous souhaitez consulter d'autres planifications d'un autre vaccin.\n");
                        printf("Tapez 2 si vous souhaitez consulter d'autres semaines planifiees du meme vaccin.\n");
                        printf("Tapez 0 si vous ne souhaitez plus consulter de planifications.\n");
                        scanf("%d", &l);
                        viderBuffer();
                    }
                }
                l=1;
                break;

            case '6' :
                printf("\n===FUSION VACCINS===\n");
                printf("Entrez le nom du 1er vaccin a fusionner : ");
                gets(marque);
                if(strlen(marque)>20){
                    printf("Le nom de la marque est trop long et donc n'existe pas.\n");
                    viderBuffer();
                    break;
                }
                a=0;
                while(strcmp(GESTION_VACCINS[a]->marque,marque)!=0){
                    a++;
                    if(a>9 || GESTION_VACCINS[a]==NULL){
                        printf("!!! Le vaccin n'existe pas !!!\n");
                        break;
                    }
                }
                if(a>9 || GESTION_VACCINS[a]==NULL){
                        break;
                }
                vaccinA=GESTION_VACCINS[a];


                printf("Entrez le nom du 2eme vaccin a fusionner : ");
                gets(marque);
                if(strlen(marque)>20){
                    printf("Le nom de la marque est trop long et donc n'existe pas.\n");
                    viderBuffer();
                    break;
                }
                b=0;
                while(strcmp(GESTION_VACCINS[b]->marque,marque)!=0){
                    b++;
                    if(b>9 || GESTION_VACCINS[b]==NULL){
                        printf("!!! Le vaccin n'existe pas !!!\n");
                        break;
                    }
                }
                if(b>9 || GESTION_VACCINS[b]==NULL){
                        break;
                }
                vaccinB=GESTION_VACCINS[b];

                vaccinC=fusionnerStocks(vaccinA, vaccinB);

                c=0;
                while(GESTION_VACCINS[c]!=NULL){
                    c++;
                    if(c==9 && GESTION_VACCINS[c]!=NULL){
                        printf("Le tableau des vaccins est plein. Impossible de fusionner 2 vaccins.\n");
                        break;
                    }
                }
                if(c==9 || GESTION_VACCINS[c]!=NULL){
                        break;
                }
                GESTION_VACCINS[c]=vaccinC;

                break;

            case '7' :
                printf("\n======== PROGRAMME TERMINE ========\n");
                break;

            default :
                printf("\n\nERREUR : votre choix n'est valide !");
        }
        printf("\n\n\n");
    }
    vider_tableau_vacc(GESTION_VACCINS);
    return 0;
}
