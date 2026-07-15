#ifndef ENVIRONNEMENT_H
#define ENVIRONNEMENT_H
#include "particules.h"

/*  @requires 
    @assigns 
    @ensures
*/

typedef struct env_s* env;

/*Type représentant un environnement de particules*/


/*  @requires  n >= 0, w > 0, h > 0, r > 0, dt > 0
    @assigns 
    @ensures alloue la mémoire pour un environnement de taille wxh avec n particules, dont la durée des itérations de déplacement est dt, et dont le rayon d'intéraction entre particules est r, et qui renvoie cet environnement
    Les particules sont toutes placées au centre de l'environnement avec une vitesse qui les envoie vers la droite.
*/
env create_environnement(int n, float w, float h, float r, float dt);


/*  @requires e un environnement de particules valide
    @assigns 
    @ensures libère la mémoire allouée pour l'environnement e
*/
void free_environnement(env e);


/*  @requires e un environnement de particules valide
    @assigns 
    @ensures renvoie un entier égal au nombre de particules dans l'environnement
*/
int get_n(env e); 


/*  @requires e un environnement de particules valide, i un entier tel que 0 <= i < n
    @assigns 
    @ensures renvoie la i-ieme particule de l'environnement
*/
particule get_particule(env e, int i);


/*  @requires e un environnement de particules valide
    @assigns 
    @ensures renvoie un float égal à la largeur de l'environnement
*/
float get_w(env e);


/*  @requires e un environnement de particules valide
    @assigns 
    @ensures renvoie un float égal à la durée des itérations de déplacement des
particules
*/
float get_dt(env e);


/*  @requires e un environnement de particules valide
    @assigns 
    @ensures renvoie un float égal à la hauteur de l'environnement
*/
float get_h(env e);


/*  @requires e un environnement de particules valide
    @assigns 
    @ensures renvoie un float égal au rayon d'intéraction des particules
*/
float get_r(env e);


/*  @requires e un environnement de particules valide
    @assigns 
    @ensures effectue une itération de déplacement
*/
void move_particules(env e);


#endif