#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <time.h>
#define TAILLE 512
#define MAX_LINE_LENGTH 100
#define MAX_LOCATIONS 1000
#define N 1000

typedef struct AVL{
	struct AVL* fd;
	struct AVL* fg;
	int equilibre;
	char cligne[TAILLE];
	char** ligne;
	int taille_ligne;
	int nbr_moyenne[2];
} avl;


typedef struct ABR{
	struct ABR* fd;
	struct ABR* fg;
	char cligne[TAILLE];
	char** ligne;
	int taille_ligne;
	int nbr_moyenne[2];
} Arbre;





void verifpchar(char* c);
void verifpint(int* n);
void verifn(int n);

void verifavl(avl a);
void verifpavl(avl* a);


void verifpfile(FILE * file);

void verifmode(char* c);



int min3(int a, int b, int c);
int max2(int a, int b);
int max3(int a, int b, int c);
int min2(int a, int b);


/*
char* convertdateavl(avl* a, char* verif, int idx);
char* convertheureavl(avl* a, char* verif1, char* verif2, int idx);


int convertstrtoint(int n, char* a);
int comparedate(char* a, char* b);
int compareheure(char* a, char* b);
*/

int compare_dates(const char *date1, const char *date2);

int infstrictavl(avl* a, avl* b, int idx, char* type);
int egalavl(avl* a, avl* b, char* type);


char** strtotab(char* l, int* nl, char* type);
char** creationligne(char* l, int* nbr_i, char* type);

avl* creationavl(char* l, char* type);
avl* rotadroite(avl* a);
avl* rotagauche(avl* a);
avl* doublerotagauche(avl* a);
avl* doublerotadroite(avl* a);
avl* equilibreravl(avl* a);
avl* insertavl(avl* a, avl* nv, int* h, int idx, char* type);
avl* insertavl_appel(avl* a, char* ligne, int idx, char* type);


avl* construireavl(char* nomf, int idx, char* type);

//abr* creationabr(char* l);
//abr* insertabr(abr* a, abr* nv);

void parcourscroissantavl(avl* a, FILE* fichier);
void parcourscroissantavl_appel(avl* a, char* nomf);
void parcoursdecroissantavl(avl* a, FILE* fichier);
void parcoursdecroissantavl_appel(avl* a, char* nomf);
void traiteravl(avl* a, FILE* out_fichier);

avl* finiravl(avl* a, char* type);

char* actualiseravl_cligne(avl* a);


int tri_p1_avl(char* input_fich, char* output_fich, int decroissant);
int infstrictavl_p1(avl* a, avl* b, int idx);
avl* egalavl_p1(avl* a, avl* b, int i);
avl* finiravl_p1(avl* a, int i);

int tri_p2_avl(char* input_fich, char* output_fich, int decroissant);
int infstrictavl_p2(avl* a, avl* b, int idx);
avl* egalavl_p2(avl* a, avl* b, int i);
avl* finiravl_p2(avl* a, int i);

int tri_p3_avl(char* input_fich, char* output_fich, int decroissant);
int infstrictavl_p3(avl* a, avl* b, int idx);
avl* egalavl_p3(avl* a, avl* b, int i);
avl* finiravl_p3(avl* a, int i);

int tri_t1_avl(char* input_fich, char* output_fich, int decroissant);
int infstrictavl_t1(avl* a, avl* b, int idx);
avl* egalavl_t1(avl* a, avl* b, int i);
avl* finiravl_t1(avl* a, int i);

int tri_t2_avl(char* input_fich, char* output_fich, int decroissant);
int infstrictavl_t2(avl* a, avl* b, int idx);
avl* egalavl_t2(avl* a, avl* b, int i);
avl* finiravl_t2(avl* a, int i);

int tri_t3_avl(char* input_fich, char* output_fich, int decroissant);
int infstrictavl_t3(avl* a, avl* b, int idx);
avl* egalavl_t3(avl* a, avl* b, int i);
avl* finiravl_t3(avl* a, int i);

int tri_w_avl(char* input_fich, char* output_fich, int decroissant);
int infstrictavl_w(avl* a, avl* b, int idx);
avl* egalavl_w(avl* a, avl* b, int i);
avl* finiravl_w(avl* a, int i);

int tri_h_avl(char* input_fich, char* output_fich);
int infstrictavl_h(avl* a, avl* b, int idx);
avl* egalavl_h(avl* a, avl* b, int i);
avl* finiravl_h(avl* a, int i);

int tri_m1_avl(char* input_fich, char* output_fich);
int tri_m2_avl(char* input_fich, char* output_fich);
int infstrictavl_m1(avl* a, avl* b, int idx);
int infstrictavl_m2(avl* a, avl* b, int idx);
avl* egalavl_m(avl* a, avl* b, int i);
avl* finiravl_m(avl* a, int i);

//char* prendreligne(int* verif, size_t len, FILE* fichier);

void parcoursPrefixeVent(Arbre *arbre, char *fichier_entree, char *fichier_sortie);

int compare_rows(const void * a, const void * b);
void TriDecroissantHumidite(char  * fichier_entree, char * fichier_sortie);


/* on a eu des problemes en mettant tout le travail en commun donc beaucoup de modes ne marchent pas

ArbreABR *creationNoeud(int *tab);
int countChar(char *str, char c);
int Compte_Nbr_colonnes(char *fichier_sortie);
char *strtok2(char *str, const char *delim);
ArbreABR *insertion(ArbreABR *arbre, char *fichier_entree, int *tab, int colonne_a_filtrer, int nb_filtrage);
ArbreABR *remplir_ABR(char *fichier_entree, int colonne_a_filtrer, int nb_filtrage);
void AfficheNoeud(ArbreABR *arbre, char *fichier_entree);
void EcritNoeudFichier(ArbreABR *arbre, char *fichier_entree, char *fichier_sortie);
void SupprimeDernierCaractere(char *fichier_entree);
void parcoursPrefixe(ArbreABR *arbre, char *fichier_entree, char *fichier_sortie, int nb_filtrage);
Arbre *creationNoeudTemp(Station station);
Station create_station(int id_station, float temperature);
int nb_stations(char *fichier_entree);
Station *lecture_fichier(char *fichier_entree);
void gestion_meme_noeud(Arbre *arbre, Station station);
void affiche_station(Station *station);
Arbre *insertion_station(Arbre *arbre, Station station);
Arbre *remplir_arbre(Station *tab_station, int nb_station);
void EcritNoeudFichierTemp1(Arbre *arbre, char *fichier_entree, char *fichier_sortie);
void parcoursPrefixeTemp1(Arbre *arbre, char *fichier_entree, char *fichier_sortie);
void parcoursPrefixeTemp1Decroissant(Arbre *arbre, char *fichier_entree, char *fichier_sortie);
Station create_station_press1(int id_station, float pression);
void EcritNoeudFichierPress1(Arbre *arbre, char *fichier_entree, char *fichier_sortie);
void parcoursPrefixePress1(Arbre *arbre, char *fichier_entree, char *fichier_sortie);
void parcoursPrefixePress1Decroissant(Arbre *arbre, char *fichier_entree, char *fichier_sortie);
Arbre *insertion_station_press1(Arbre *arbre, Station station);
Arbre *remplir_arbre_press1(Station *tab_station, int nb_station);
Station *lecture_fichier_press1(char *fichier_entree);
Station create_station_Humidite(int id_station, float humidite, float lattitude, float longitude);
void EcritNoeudFichierHumidite(Arbre *arbre, char *fichier_entree, char *fichier_sortie);
void parcoursPrefixeHumidite(Arbre *arbre, char *fichier_entree, char *fichier_sortie);
Arbre *insertion_station_Humidite(Arbre *arbre, Station station);
Arbre *remplir_arbre_Humidite(Station *tab_station, int nb_station);
Station *lecture_fichier_Humidite(char *fichier_entree);
int compare_rows(const void *a, const void *b);
void TriDecroissantHumidite(char *fichier_entree, char *fichier_sortie);
Station create_station_altitude(int id_station, int altitude, float lattitude, float longitude);
void EcritNoeudFichierAltitude(Arbre *arbre, char *fichier_entree, char *fichier_sortie);
void parcoursPrefixeAltitude(Arbre *arbre, char *fichier_entree, char *fichier_sortie);
Arbre *insertion_station_Altitude(Arbre *arbre, Station station);
Arbre *remplir_arbre_altitude(Station *tab_station, int nb_station);
Station *lecture_fichier_altitude(char *fichier_entree);
void TriDecroissantAltitude(char *fichier_entree, char *fichier_sortie);
Station create_station_Vent(int id_station, float direction, float vitesse, float lattitude, float longitude);
void EcritNoeudFichierVent(Arbre *arbre, char *fichier_entree, char *fichier_sortie);
void parcoursPrefixeVent(Arbre *arbre, char *fichier_entree, char *fichier_sortie);
Arbre *insertion_station_Vent(Arbre *arbre, Station station);
Arbre *remplir_arbre_Vent(Station *tab_station, int nb_station);
Station *lecture_fichier_Vent(char *fichier_entree);
void parcoursPrefixeVentDecroissant(Arbre *arbre, char *fichier_entree, char *fichier_sortie);
int compare_dates(const char *date1, const char *date2);
Station create_station_Temp2(float temperature, char *date);
void EcritNoeudFichierTemp2(Arbre *arbre, char *fichier_entree, char *fichier_sortie);
void parcoursPrefixeTemp2(Arbre *arbre, char *fichier_entree, char *fichier_sortie);
Arbre *insertion_station_Temp2(Arbre *arbre, Station station);
Arbre *remplir_arbre_Temp2(Station *tab_station, int nb_station);
Station *lecture_fichier_Temp2(char *fichier_entree);
void parcoursPrefixeTemp2Decroissant(Arbre *arbre, char *fichier_entree, char *fichier_sortie);
Station create_station_Press2(char *date, float pression);
void EcritNoeudFichierPress2(Arbre *arbre, char *fichier_entree, char *fichier_sortie);
void parcoursPrefixePress2(Arbre *arbre, char *fichier_entree, char *fichier_sortie);
Arbre *insertion_station_Press2(Arbre *arbre, Station station);
Arbre *remplir_arbre_Press2(Station *tab_station, int nb_station);
Station *lecture_fichier_Press2(char *fichier_entree);
void parcoursPrefixePress2Decroissant(Arbre *arbre, char *fichier_entree, char *fichier_sortie);
void parcoursPrefixePress3Decroissant(Arbre *arbre, char *fichier_entree, char *fichier_sortie);
Station create_station_Temp3(int station_id, char *date, float temperature);
void EcritNoeudFichierTemp3(Arbre *arbre, char *fichier_entree, char *fichier_sortie);
void parcoursPrefixeTemp3(Arbre *arbre, char *fichier_entree, char *fichier_sortie);
void parcoursPrefixeTemp3Decroissant(Arbre *arbre, char *fichier_entree, char *fichier_sortie);
Arbre *insertion_station_Temp3(Arbre *arbre, Station station);
Arbre *remplir_arbre_Temp3(Station *tab_station, int nb_station);
Station *lecture_fichier_Temp3(char *fichier_entree);
Station create_station_Press3(int station_id, char *date, float pression);
void EcritNoeudFichierPress3(Arbre *arbre, char *fichier_entree, char *fichier_sortie);
void parcoursPrefixePress3(Arbre *arbre, char *fichier_entree, char *fichier_sortie);
Arbre *insertion_station_Press3(Arbre *arbre, Station station);
Arbre *remplir_arbre_Press3(Station *tab_station, int nb_station);
Station *lecture_fichier_Press3(char *fichier_entree);
void Tri_Temp1ABR(int mode_decroissant, char *fichier_entree, char *fichier_sortie);
void Tri_Temp2ABR(int mode_decroissant, char *fichier_entree, char *fichier_sortie);
void Tri_Temp3ABR(int mode_decroissant, char *fichier_entree, char *fichier_sortie);
void Tri_Press1ABR(int mode_decroissant, char *fichier_entree, char *fichier_sortie);
void Tri_Press2ABR(int mode_decroissant, char *fichier_entree, char *fichier_sortie);
void Tri_Press3ABR(int mode_decroissant, char *fichier_entree, char *fichier_sortie);
void Tri_HumiditeABR(int mode_decroissant, char *fichier_entree, char *fichier_sortie);
void Tri_AltitudeABR(int mode_decroissant, char * fichier_entree, char * fichier_sortie);
void Tri_VentABR(int mode_decroissant, char *fichier_entree, char *fichier_sortie);
void Analyse_des_arguments(char *mode, int decroissant, char *fichier_entree, char *fichier_sortie, int nbr_argument, char *mode_sort);

int compare_rows(const void * a, const void * b);
void TriDecroissantHumidite(char  * fichier_entree, char * fichier_sortie);
void addLine(char line);
int findLine(char line);
void readLines();
void writeLines();
int lines();
void addLine(char line);
void readLines();
void writeLines();
int compare(const void a, const voidb);
void tri_tab_altitude(char* entree, char* sortie);

*/