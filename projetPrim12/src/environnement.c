#include <stdlib.h>
#include <math.h>
#include "../headers/environnement.h"
#include "../headers/particules.h"



struct env_s{
    int n; // nombre de particules
    float w; // largeur de l'environnement
    float h; // hauteur de l'environnement
    float r; // rayon de collision des particules
    float dt; // pas de temps pour le mouvement des particules
    particule* particules; // tableau de particules
};


/* -------------------------------------------------------
 * create_environnement
 * ------------------------------------------------------- */
env create_environnement(int n, float w, float h, float r, float dt) {
    /* Allocation dynamique de la structure env elle-même */
    env e = malloc(sizeof(struct env_s));
    if (e == NULL) {
        exit(EXIT_FAILURE);
    }

    e->n  = n;
    e->w  = w;
    e->h  = h;
    e->r  = r;
    e->dt = dt;

    /* Allocation du tableau de particule* */
    e->particules = malloc(n * sizeof(particule));
    if (e->particules == NULL) {
        free(e);
        exit(EXIT_FAILURE);
    }

    /* Allocation dynamique de chaque particule via create_particule */
    for (int i = 0; i < n; i++) {
        e->particules[i] = create_particule(w / 2.0f, h / 2.0f, 1.0f, 0.0f);
    }

    return e;
}


/* -------------------------------------------------------
 * free_environnement : libère toutes les particules puis l'environnement
 * ------------------------------------------------------- */
void free_environnement(env e) {
    for (int i = 0; i < e->n; i++) {
        free_particule(e->particules[i]); /* libère chaque particule */
    }
    free(e->particules); /* libère le tableau */
    free(e);             /* libère la structure env elle-même */
}

/* -------------------------------------------------------
 * Accesseurs en lecture
 * ------------------------------------------------------- */
int       get_n(env e)               { return e->n;  }
particule get_particule(env e, int i){ return e->particules[i]; }
float     get_w(env e)               { return e->w;  }
float     get_h(env e)               { return e->h;  }
float     get_dt(env e)              { return e->dt; }
float     get_r(env e)               { return e->r;  }

/* -------------------------------------------------------
 * Fonction interne : gère le rebond d'une particule sur les bords.
 * Si la particule sort par un bord, on la "réfléchit" à l'intérieur
 * et on inverse la composante de vitesse correspondante.
 * ------------------------------------------------------- */
static void rebond(particule p, float w, float h) {
    float x  = get_x(p);
    float y  = get_y(p);
    float vx = get_vx(p);
    float vy = get_vy(p);

    /* Rebond sur le bord gauche (x < 0) */
    if (x < 0.0f) {
        x  = -x;
        vx = -vx;
    }
    /* Rebond sur le bord droit (x > w) */
    if (x > w) {
        x  = 2.0f * w - x;
        vx = -vx;
    }
    /* Rebond sur le bord bas (y < 0) */
    if (y < 0.0f) {
        y  = -y;
        vy = -vy;
    }
    /* Rebond sur le bord haut (y > h) */
    if (y > h) {
        y  = 2.0f * h - y;
        vy = -vy;
    }

    set_position(p, x, y);
    set_speed(p, vx, vy);
}

/* -------------------------------------------------------
 * Fonction interne : renvoie un angle aléatoire dans [0, 2*pi].
 * Utilisée quand le barycentre coïncide avec la particule.
 * ------------------------------------------------------- */
static float uniform_angle(void) {
    float pi = 3.14f;
    return ((float)rand() / (float)RAND_MAX) * 2.0f * pi;
}


/* -------------------------------------------------------
 * Fonction interne : calcule la répulsion pour la particule d'indice idx.
 * On cherche toutes les voisines à distance < r, on calcule leur barycentre,
 * et on oriente la vitesse de la particule pour s'en éloigner.
 * ------------------------------------------------------- */
static void repulsion(env e, int idx) {
    int   i;
    int   nb_voisins = 0;
    float bx = 0.0f;
    float by = 0.0f;
    float dx, dy;
    particule p = e->particules[idx];

    /* Parcours de toutes les autres particules */
    for (i = 0; i < e->n; i++) {
        if (i == idx) {
            continue;
        }
        if (distance(p, e->particules[i]) < e->r) {
            bx += get_x(e->particules[i]);
            by += get_y(e->particules[i]);
            nb_voisins++;
        }
    }

    /* Pas de voisin proche : rien à faire */
    if (nb_voisins == 0) {
        return;
    }

    /* Barycentre des voisins */
    bx = bx / (float)nb_voisins;
    by = by / (float)nb_voisins;

    /* Vecteur de la particule vers le barycentre */
    dx = get_x(p) - bx;
    dy = get_y(p) - by;

    /* Si le barycentre est exactement sur la particule, vitesse aléatoire */
    if (dx * dx + dy * dy < 1e-12f) {
        float angle = uniform_angle(); /* voir ci-dessous */
        set_speed(p, cosf(angle), sinf(angle));
    } else {
        /* On s'éloigne du barycentre (set_speed normalise automatiquement) */
        set_speed(p, dx, dy);
    }
}


/* -------------------------------------------------------
 * move_particules : une itération complète de simulation
 *   1. Déplacer toutes les particules
 *   2. Gérer les rebonds sur les bords
 *   3. Appliquer les répulsions
 * ------------------------------------------------------- */
void move_particules(env e) {

    /* Étape 1 & 2 : déplacement + rebonds */
    for (int i = 0; i < e->n; i++) {
        move(e->particules[i], e->dt);
        rebond(e->particules[i], e->w, e->h);
    }

    /* Étape 3 : répulsions entre particules proches */
    for (int i = 0; i < e->n; i++) {
        repulsion(e, i);
    }
}