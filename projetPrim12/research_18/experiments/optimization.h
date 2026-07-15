#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include "../headers/environnement.h"
#include "../headers/distribution.h"
#include "../headers/particules.h"
#include "../headers/interface.h"


//initialise les positions et vitesse des n (n de l'odre de 5) particules  d'un environnements de manieres a
//maximiser la distance minimum entre deux particules lors de la première itération qui dépasse t secondes (en restant tres proche de t). 
//On fait en sorte d'avoir une dispertion ciculaire des particules uniformément répartie sur un cercle de rayon min(h,w)/2 avec
//w : la largeur de l'environnement et h : la hauteur de l'environnement

void optimisation(env e, float t);