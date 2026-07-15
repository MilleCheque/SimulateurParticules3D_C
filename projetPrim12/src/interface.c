#include "../headers/environnement.h"
#include "../headers/particules.h"
#include "../headers/interface.h"

#include <stdio.h>
#include <stdlib.h>

void print_particule(particule p){
    fprintf(stdout, "position : (%f,%f), vitesse : (%f, %f)\n",
                get_x(p), get_y(p), get_vx(p), get_vy(p));
}

void print_environnement(env e){
    fprintf(stdout, "Information de l'environnement :\nNombre de particule : %d, largeur : %f, hauteur : %f\nrayon de colision : %f, pas de temps : %f\n",get_n(e), get_w(e), get_h(e), get_r(e), get_dt(e));
    fprintf(stdout, "Informations des %d particules :\n", get_n(e));
    for(int i = 0; i < get_n(e); i++){
        print_particule(get_particule(e, i));
    }
}

void print_message(const char *msg){
    fprintf(stdout,"%s",msg);
}

int get_int(void){
    int res;
    fscanf(stdin, "%d", &res);
    return res;
}

float get_float_int(void){
    float res;
    fscanf(stdin, "%f", &res);
    return res;
}

void snapshot(env e, const char *path, int wp, int hp){
    FILE *f = fopen(path, "w");
    if (!f) {
        printf("Impossible d'ecrire dans le fichier\n");
        return;
    }

    fprintf(f,"P1\n# snapshot\n");
    fprintf(f,"%d %d\n", wp, hp);

    // tableau initialisé à 0
    int tableau[wp][hp];
    for(int i = 0; i < wp; i++)
        for(int j = 0; j < hp; j++)
            tableau[i][j] = 0;

    // remplissage des particules
    for(int i = 0; i < get_n(e); i++){
        particule p = get_particule(e, i);
        int xi = (int)get_x(p);
        int yi = (int)get_y(p);
        if(xi >= 0 && xi < wp && yi >= 0 && yi < hp)
            tableau[xi][yi] = 1;
    }

    // écriture dans le fichier PBM
    for(int i = 0; i < hp; i++){
        for(int j = 0; j < wp; j++){
            fprintf(f, "%d ", tableau[j][i]);
        }
        fprintf(f, "\n");
    }

    fclose(f);
}


void animate(env e, const char *path, int wp, int hp, int t){//on respecte le .h, ce qui implique de ne pas modifier env
    char pathDuFichieri[100]; //on prie pour ne pas avoir de chemin de plus de 50 caracteres
    for(int i = 0; i < t+1; i++){//on met aussi dans le dossier l'itération 0
        sprintf(pathDuFichieri, "%s/env-%d.pbm", path, i);
        snapshot(e, pathDuFichieri, wp, hp);
        move_particules(e);
    }
}

