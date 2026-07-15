#ifndef DISTRIBUTION_H
#define DISTRIBUTION_H

/* fonction qui reproduit une loi uniform, prends deux float en entree
et renvoie un float aleatoire suivant la loi*/
float uniform(float a, float b);

/* fonction qui reproduit une loi normal, prends deux float en entree
et renvoie un float aleatoire suivant la loi*/
float normal(float mu, float sigma);

/* fonction qui reproduit une loi exponentielle, prends deux float en entree
et renvoie un float aleatoire suivant la loi*/
float exponential(float k);

/* Fonction qui prends en paramètre un entier n, un tableau de float t 
et un tableau de float p contenant n float donc leur somme vaut 1.
Renvoie t[i] suivant la proba p[i]*/
float discrete(int n, float t[], float p[]);

#endif
