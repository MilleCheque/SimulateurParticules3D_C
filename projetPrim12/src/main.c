#include <stdio.h>
#include <stdlib.h>
#include "../headers/environnement.h"
#include "../headers/interface.h"
#include <time.h>

int main() {
    srand(time(NULL)); // sans cette partie la graine resterait la meme et la sequence aleatoire aussi donc pas forcement pratique
    /* Paramètres de la simulation */

    print_message("Bienvenue dans la simulation de particules !\n");
    print_message("Merci de suivre les instructions à l'écran pour configurer la simulation.\n");
    
    print_message("Veuillez entrer le nombre de particules à simuler : ");
    int num_particles = get_int();

    print_message("Veuillez entrer le rayon de collision des particules (en unités) : ");
    float r = get_float_int();

    print_message("Veuillez entrer la largeur de l'environnement (en unités) : ");
    float width = get_float_int();
    
    print_message("Veuillez entrer la hauteur de l'environnement (en unités) : ");
    float height = get_float_int();

    print_message("Veuillez choisir le pas temps de la simulation (en secondes) : ");
    float time_step = get_float_int();

    print_message("Veuillez entrer le nombre d'itérations à simuler : ");
    int iterations = get_int();

    // Chemin pour sauvegarder les images de la simulation
    char* path = "output/";


    print_message("Configuration de la simulation terminée. Initialisation en cours...\n");

    /* Initialisation de la simulation */
    env environnement = create_environnement(num_particles, width, height, r, time_step);

    /* Lancement de la simulation et génération d'images */
    animate(environnement, path, (int)width, (int)height, iterations);
    
    // Libération de la mémoire allouée
    free_environnement(environnement);
    return 0;
}