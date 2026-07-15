#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../headers/environnement.h"
#include "../headers/distribution.h"
#include "../headers/particules.h"
#include "../headers/interface.h"

// But : placer les particules sur un cercle de rayon min(h, w)/2
// On se focalise sur une des 2 particules se déplaçant positivement selon l'axe x pour initilaiser sa vitesse et sa position,
//(on garde en tete que a chaque itération elle se déplace de  dt)
//qu'on généralise ensuite pour les autres particules
void optimisation(env e, float t){
    int n = get_n(e);

    // Initialisation des vitesses : mouvement circulaire
    for(int k = 0; k < n; k++){
        set_speed(get_particule(e, k),
                  cosf(2 * M_PI * k / n),
                  sinf(2 * M_PI * k / n));
    }

    // Cas où la taille de l'environnement coincide exactement à t
    if ((get_w(e) == t && get_h(e) > t) ||
        (get_w(e) > t && get_h(e) == t) ||
        (get_w(e) == t && get_h(e) == t)) {

        for(int k = 0; k < n; k++){
            set_position(get_particule(e, k), 0.0f, 0.0f);
        }
        return;
    }

    // Calcul du minimum entre largeur et hauteur
    float min_w_h;
    if(get_w(e) < get_h(e)) {
        min_w_h = get_w(e);
    } else {
        min_w_h = get_h(e);
    }

    float rayon = min_w_h / 2.0f;
    float ecart = fabsf(t - rayon);

    // Cas : t plus petit que le rayon
    if(t < rayon){
        for(int k = 0; k < n; k++){
            set_position(get_particule(e, k),
                         ecart * cosf(2 * M_PI * k / n),
                         ecart * sinf(2 * M_PI * k / n));
        }
        return;
    }

    // Cas : t plus grand que le rayon
    if(t > rayon){
        float periode = rayon;
        float ecart_mod = fmodf(t, periode);
        int d = (int)(t / periode); //on compte le nombre de fois que la particule se deplacant selon +x peut parcourir la distance rayon

        float depart;

        // Selon la parité de d
        if(d % 2 == 1){
            depart = -ecart_mod;
        } else {
            //dans ce cas, si la particule qui se déplace selon +x part du bord, 
            //on remarque que au final elle se retrouve éloigné du bord d'une distance
            depart = rayon - ecart_mod;
        }

        for(int k = 0; k < n; k++){
            set_position(get_particule(e, k),
                         depart * cosf(2 * M_PI * k / n),
                         depart * sinf(2 * M_PI * k / n));
        }
        return;
    }
}


/*Schéma explicatif en supposant que on a le centre a gauche et le bord a droite
on représente le parcourt de la particule se déplacant selon +/-x

cas ou d est impair :
->--------------------->|
<----|

cas ou d est pair :
    ce qui ce passe si on part de ecart_mod :
<---------------------<-|
->--------------------->|
<----|
    ce qui ce passe si on part de (rayon - ecart_mod)
->--------------------->|
-<--------------------<-|
     |->--------------->|

*/