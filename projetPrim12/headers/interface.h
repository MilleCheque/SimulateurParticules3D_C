#ifndef INTERFACE_H
#define INTERFACE_H

#include "environnement.h"
#include "particules.h"

/*
 * @requires p est une particule valide et initialisée.
 * @assigns  stdout
 * @ensures  Les informations de p sont affichées sur la sortie standard.
 */
void print_particule(particule p);

/*
 * @requires e est un environnement valide et initialisé.
 * @assigns  stdout
 * @ensures  Les informations de e et de toutes ses particules sont affichées sur la sortie standard.
 */
void print_environnement(env e);

/*
 * @requires msg != NULL et msg est une chaîne de caractères valide (terminée par '\0').
 * @assigns  stdout
 * @ensures  Le contenu de msg est affiché sur la sortie standard.
 *           Seule fonction autorisée à écrire sur stdout.
 */
void print_message(const char *msg);

/*
 * @requires L'entrée standard contient un entier valide.
 * @assigns  stdin
 * @ensures  \result est l'entier lu depuis l'entrée standard.
 */
int get_int(void);

/*
 * @requires L'entrée standard contient un flottant valide.
 * @assigns  stdin
 * @ensures  \result est le flottant lu depuis l'entrée standard.
 */
float get_float_int(void);

/*
 * @requires e est un environnement valide et initialisé.
 * @requires path != NULL et désigne un chemin accessible en écriture.
 * @requires wp > 0 et hp > 0.
 * @assigns  le fichier désigné par path.
 * @ensures  Un fichier PBM de dimensions wp x hp est créé à l'emplacement path,
 *           représentant l'état actuel de e : les particules en noir (1), le fond en blanc (0).
 */
void snapshot(env e, const char *path, int wp, int hp);

/*
 * @brief Génère t fichiers PBM pour t itérations de déplacement.
 *        Les fichiers sont nommés env-0.pbm, env-1.pbm, ..., env-(t-1).pbm
 *        et placés dans le dossier path.
 * @param e    l'environnement
 * @param path chemin vers le dossier de sortie
 * @param wp   largeur des images en pixels
 * @param hp   hauteur des images en pixels
 * @param t    nombre d'itérations à générer
 */
void animate(env e, const char *path, int wp, int hp, int t);

#endif /* INTERFACE_H */