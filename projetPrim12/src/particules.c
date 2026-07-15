#include <stdlib.h>
#include <math.h>
#include "../headers/particules.h"


/* Type représentant une particule*/
struct particule {
    float x;
    float y;
    float vx;
    float vy;
};


/* Normalise un vecteur (vx, vy).
   Si le vecteur est nul, on laisse tel quel. */
static void normalize(float *vx, float *vy) {
    float norm = sqrt((*vx) * (*vx) + (*vy) * (*vy));
    if (norm > 0.0f) {
        *vx = *vx / norm;
        *vy = *vy / norm;
    }
}

particule create_particule(float x, float y, float vx, float vy) {
    particule p = malloc(sizeof(struct particule));
    if (p == NULL) {
        exit(EXIT_FAILURE);
    }
    p->x = x;
    p->y = y;
    normalize(&vx, &vy);
    p->vx = vx;
    p->vy = vy;
    return p;
}

void free_particule(particule p) {
    if (p != NULL) {
        free(p);
    }
}

float get_x(particule p) {
    return p->x;
}

float get_y(particule p) {
    return p->y;
}

float get_vx(particule p) {
    return p->vx;
}

float get_vy(particule p) {
    return p->vy;
}

void set_position(particule p, float x, float y) {
    p->x = x;
    p->y = y;
}

void set_speed(particule p, float vx, float vy) {
    normalize(&vx, &vy);
    p->vx = vx;
    p->vy = vy;
}

void move(particule p, float dt) {
    p->x += dt * p->vx;
    p->y += dt * p->vy;
}

float distance(particule p1, particule p2) {
    float dx = p1->x - p2->x;
    float dy = p1->y - p2->y;
    return sqrt(dx * dx + dy * dy);
}