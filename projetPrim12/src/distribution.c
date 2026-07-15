#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../headers/distribution.h"
#include <time.h>

float uniform(float a, float b){
    float x = (float)rand()/RAND_MAX; //on normalise pour que x soit entre 0 et 1 (RAND_MAX est d'après la doc le nombre max generer par rand)
    //cast pour éviter l'arrondi de la division d'entier donne 0
    return a + (b - a) * x; //on utilise a pour que le nombre soit >= à a et b-a pour que le nombre additionner soit inférieur à b et multiplier par x sert à introduire l'aléatoire
}

float normal(float mu, float sigma){
    float l_nor = 0;//inialisation de notre future loi normale
    for(int i = 0; i < 12; i++){
        l_nor += uniform(0,1);//somme de V.A iid et V(l_uniforme) = 12*V(uniform(0,1)) = 12* (1/12) = 1 réduction de la VA
    }
    l_nor = l_nor - 6; // Centrer la VA E(l_nor) = 12*1/2 = 6 
    return l_nor * sigma + mu;//On décale de centre et on modifie la variance 

}

float exponential(float k){
    float expo = 0 ;
    float uni;
    do{uni = uniform(0,1);}while(uni == 1.0);//il l'a faut différente de 1 pour appliquer le log après et avoir autre chose que 0 qui n'est pas défini
    expo = -logf(1-uni)/k;//issu de la page de la loi uniforme  et logf issu de math.h pour float
    return expo;
}

float discrete(int n, float t[], float p[]){
    float u = uniform(0, 1); //pour l'aléatoire
    float somme_prob = 0;
    for(int i = 0; i <n; i++){
        somme_prob += p[i];//accumulation des proba du tableau 
        if(somme_prob >= u){return t[i];}//si u appartient à cette tranche des proba on retourne la valeur à la case associé dans t
    }
    return t[n - 1];
}