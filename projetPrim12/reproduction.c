#include <stdlib.h>
#include <stdio.h>
#include <math.h>
#include <time.h>
#include <float.h>

#define MAX_ATTRACTORS 100


typedef struct {
    float x, y, z;
    float vx, vy, vz;
} particule;

typedef struct {
    float x, y, z;
} attractor;

typedef struct env_s {
    int n;
    float w, h, d;
    float r;
    float dt;

    particule *particules;
    attractor attractors[MAX_ATTRACTORS];
    int nb_attractors;

} env;

env *create_environment(int n, float w, float h, float d, float r, float dt) {

    env *e = malloc(sizeof(env));
    if (!e) exit(EXIT_FAILURE);

    e->n = n;
    e->w = w;
    e->h = h;
    e->d = d;
    e->r = r;
    e->dt = dt;

    e->particules = malloc(n * sizeof(particule));
    if (!e->particules) {
        free(e);
        exit(EXIT_FAILURE);
    }

    for (int i = 0; i < n; i++) {
        e->particules[i].x = w / 2.0f;
        e->particules[i].y = h / 2.0f;
        e->particules[i].z = d / 2.0f;

        e->particules[i].vx = 0.0f;
        e->particules[i].vy = 0.0f;
        e->particules[i].vz = 0.0f;
    }

    e->nb_attractors = 0;

    return e;
}


void measureExecutionTime(env *e, int T, double *temps) {

    clock_t start = clock();

    for (int t = 0; t < T; t++) {

        for (int i = 0; i < e->n; i++) {

            particule *p = &e->particules[i];

            p->x += p->vx * e->dt;
            p->y += p->vy * e->dt;
            p->z += p->vz * e->dt;

            if (p->x < 0 || p->x > e->w) p->vx *= -1;
            if (p->y < 0 || p->y > e->h) p->vy *= -1;
            if (p->z < 0 || p->z > e->d) p->vz *= -1;
        }
    }

    clock_t end = clock();

    *temps = (double)(end - start) / CLOCKS_PER_SEC;
}


void findMaxDist(env *e, float *distmax) {

    if (e->n < 2) {
        *distmax = 0.0f;
        return;
    }

    float maxd2 = 0.0f;

    for (int i = 0; i < e->n; i++) {
        for (int j = i + 1; j < e->n; j++) {

            float dx = e->particules[i].x - e->particules[j].x;
            float dy = e->particules[i].y - e->particules[j].y;
            float dz = e->particules[i].z - e->particules[j].z;

            float d2 = dx*dx + dy*dy + dz*dz;

            if (d2 > maxd2) {
                maxd2 = d2;
            }
        }
    }

    *distmax = sqrtf(maxd2);
}



void averageDistance(env *e, float *distAverage) {

    if (e->n < 2) {
        *distAverage = 0.0f;
        return;
    }

    float sum = 0.0f;
    int count = 0;

    for (int i = 0; i < e->n; i++) {
        for (int j = i + 1; j < e->n; j++) {

            float dx = e->particules[i].x - e->particules[j].x;
            float dy = e->particules[i].y - e->particules[j].y;
            float dz = e->particules[i].z - e->particules[j].z;

            float d = sqrtf(dx*dx + dy*dy + dz*dz);

            sum += d;
            count++;
        }
    }

    *distAverage = sum / count;
}