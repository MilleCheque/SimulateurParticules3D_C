/* Trois mesures à faire : 

-1 / le temps de calcul 
-2 / la distance minimale entre les particules
-3 / la variance de l'écart minimal entre les particules
*/

/* Pourquoi choisir ce dernier indicateur ? On veut regarder s'il la distance du plus proche voisin pour chacune des particules est stable ou non, en effet si ette distance varie beaucoup, cela indique que l'on peut déplacer les particules pour faire augmenter la plus petite de ses distances en diminuant la plus grande. Or cette modification n'est significative uniquement lorsque l'étendu de l'ensemble des distances est important. On veut donc observer la variance de la distance du plus proche voisin pour chacune des particules : Si elle est grande c'est pas bon signe car cela veut dire que la distance minimale peut encore être améliorer.*/

/* Valeurs à faire varier : 
- T 
- (W, H)
- n 
*/

/* Protocole : 
- On fait des simulations pour différentes valeurs de T, W, H et n et on stocke puis observe les valeurs des 3 mesures que l'on a eu.
- On choisit arbitrairement de faire pour les valeurs suivantes de sorte d'avoir une certaines variétés de cas d'études. 
T \in {10, 20, 50, 100, 200}
W \in {10, 70, 100, 300}
H \in {10, 30, 150, 300}
n \in {5, 10, 20}
*/
#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>

#include "../../headers/environnement.h"
#include "../../headers/particules.h"
#include "optimization.h"

// Mesure 2 : Distance minimale globale
float calcul_distance_min(env e) {
    float d_min = 1000000.0; // Infini
    // Double parcours basique pour récupérer la distance minimale globale
    for (int i = 0; i < get_n(e); i++) {
        for (int j = i + 1; j < get_n(e); j++) {
            float dist = distance(get_particule(e, i), get_particule(e, j));
            if (dist < d_min) {
                d_min = dist;
            }
        }
    }
    return d_min;
}

float calcul_variance(env e) {
    // Initialisation des variables utiles
    int n = get_n(e);
    float distances_voisins[n];
    float somme = 0;

    // Pour chaque particule, on trouve son voisin le plus proche
    for (int i = 0; i < n; i++) {
        float d_proche = 1000000.0; // Infini
        for (int j=0; j < n; j++) {
            // Si c'est la particule d'étude on skip
            if (i == j) {
                continue;
            }
            float dist = distance(get_particule(e, i), get_particule(e, j));
            // Sinon on regarde si la distance avec la nouvelle particule est plus petite
            if (dist < d_proche) {
                d_proche = dist;
            }
        }
        // On met à jour nos variables de stockage
        distances_voisins[i] = d_proche;
        somme += d_proche;
    }
    // On calcul la moyenne
    float moyenne = somme / n;
    float somme_carres = 0;
    for (int i = 0; i < n; i++) {
        somme_carres += powf(distances_voisins[i] - moyenne, 2);
    }
    // On retourne la variance
    return somme_carres / n;
}

int main() {
    // Initialisation des variables
    // Valeurs de cas d'étude
    float T_list[5] = {10, 20, 50, 100, 200};
    float W_list[4] = {10, 70, 100, 300};
    float H_list[4] = {10, 30, 150, 300};
    int n_list[3] = {5, 10, 20};


    // Stockage des mesures pour les différentes valeurs de T, W, H et n
    float stockage_temps[5][4][4][3];
    float stockage_dmin[5][4][4][3];
    float stockage_var[5][4][4][3];


    for (int i = 0; i < 5; i++) { // Boucle pour T
        for (int j = 0; j < 4; j++) { // Boucle pour W
            for (int k = 0; k < 4; k++) { // Boucle pour H
                for (int l = 0; l < 3; l++) { // Boucle pour n

                    // 1. Initialisation de l'environnement 
                    float dt = 0.1; 
                    float r = 1.0;  // rayon des particules
                    env e = create_environment(W_list[j], H_list[k], n_list[l], dt, r);

                    // 2. Mesure du temps d'exécution de l'optimisation
                    clock_t start = clock();
                    optimisation(e, T_list[i]);
                    clock_t end = clock();
                    double temps_calcul = ((double) (end - start)) / CLOCKS_PER_SEC;
                    

                    // 3. Simulation de l'environnement jusqu'à T 
                    float t_ecoule = 0;
                    while (t_ecoule < T_list[i]) {
                        move_particules(e);
                        t_ecoule += dt;
                    }

                    // 4. Calcules des autre mesures 
                    float d_min = calcul_distance_min(e);
                    float var = calcul_variance(e);
                    
                    // On les stocke pour pouvoir les étudier plus tard
                    stockage_temps[i][j][k][l] = (float)temps_calcul;
                    stockage_dmin[i][j][k][l] = d_min;
                    stockage_var[i][j][k][l] = var;

                    // On détruit l'environnement pour pas avoir de fuite mémoire
                    free_environnement(e);
                }
            }
        }
    }
    
    return 0;
}