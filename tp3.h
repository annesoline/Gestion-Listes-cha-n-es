#ifndef TP3_H_INCLUDED
#define TP3_H_INCLUDED


/* ========== STRUCTURES ========== */
typedef struct  semaine_elt{
    unsigned int numero_semaine;
    unsigned int nombre_vaccins;
    struct semaine_elt* suivant;
}t_semaine_elt;

typedef struct ville_elt{
    char* nom_ville;
    unsigned int nombre_vaccins_total;
    t_semaine_elt* semaines_planifiees;
    struct ville_elt* suivant;
}t_ville_elt;

typedef struct vaccin_elt{
    char* marque;
    struct t_ville_elt* villes_dispo;
}t_vaccin_elt;



/* ========== FONCTIONS s========== */
t_semaine_elt* creerSemaine(int num_semaine, int nb_vaccins);
t_ville_elt* creerVille(char* ville, int num_semaine, int nb_vaccins);
t_vaccin_elt* creerVaccin(char* marque);
t_semaine_elt* ajouterVaccinS(t_semaine_elt* liste, int semaine, int nb_vaccins);
t_semaine_elt* deduireVaccinS(t_semaine_elt* liste, int semaine, int nb_vaccins);
t_ville_elt* ajouterVaccinV(t_ville_elt* liste, char* ville, int semaine, int nb_vaccins);
t_ville_elt* deduireVaccinV(t_ville_elt* liste, char* ville, int semaine, int nb_vaccins);
void afficherStock(t_vaccin_elt* vaccin);
void afficherPlanification(t_vaccin_elt* vaccin, int semaine);
t_vaccin_elt* fusionnerStocks(t_vaccin_elt *vaccinA, t_vaccin_elt *vaccinB);


/* ------- UTILITAIRES ------------ */
void viderBuffer ();
bool verifVaccSem(int semaine, int nb_vaccins);
bool trouver_ville(t_ville_elt* liste, char* ville);
t_ville_elt* tri_liste_villes_A(t_ville_elt* liste, t_ville_elt* ville, int total);
t_ville_elt* ajout_ville(t_ville_elt* liste, t_ville_elt* ville);
t_ville_elt* tri_liste_villes_D(t_ville_elt* liste, t_ville_elt* ville, int total);
t_ville_elt* deduire_Ville(t_ville_elt* liste, char* ville);
bool trouver_semaine(t_semaine_elt* liste,int semaine);
t_semaine_elt* renvoyer_semaine(t_semaine_elt* liste,int semaine);
t_ville_elt *ajoutVaccin(t_vaccin_elt* vaccinA, t_vaccin_elt* vaccinB);
void vider_tableau_vacc(t_vaccin_elt* tabl_vacc[10]);
void vider_vaccin(t_vaccin_elt* vacc);
void trier_vaccins(t_vaccin_elt* GESTION_VACCINS[10], int i);



#endif // TP3_H_INCLUDED
