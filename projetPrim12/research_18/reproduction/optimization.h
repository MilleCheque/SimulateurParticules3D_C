#ifndef OPTIMIZATION_H
#define OPTIMIZATION_H

#include "../../headers/environnement.h"

/**
 * \brief \b Optimise la configuration initiale des particules d'un environnement.
 * \detail Cette fonction modifie les positions et vitesses initiales des
 * particules d'un environnement afin de rechercher une configuration
 * minimisant la distance maximale entre deux particules après la première
 * itération dépassant \a t secondes.
 * \param e L'environnement en question
 * \param t Le temps cible de l'optimisation
 */
void optimization(env e, float t);

#endif
