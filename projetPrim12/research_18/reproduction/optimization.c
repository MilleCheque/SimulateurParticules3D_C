#include <math.h>
#include <stdbool.h>
#include <stdlib.h>
#include <float.h>
#include <string.h>
#include "optimization.h"

#define NUM_TRIALS 100

/**
 * \brief Calcule la distance maximale entre deux particules d'un environnement.
 * \detail Fonction interne utilisée pour évaluer la qualité d'une configuration
 * de particules. Elle parcourt toutes les paires de particules et conserve
 * la plus grande distance euclidienne trouvée.
 * \param e L'environnement en question
 * \return La distance maximale entre deux particules de l'environnement
 */
static float compute_max_dist(env e) {
    float max_d = 0.0f;
    int n = get_n(e);

    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            float d = distance(get_particule(e, i), get_particule(e, j));
            // Si une plus grande distance est trouvée
            if (d > max_d) {
                max_d = d;
            }
        }
    }

    return max_d;
}

/**
 * \brief Simule l'environnement jusqu'à la première itération dépassant t.
 * \detail Fonction interne utilisée pour appliquer plusieurs itérations de
 * déplacement aux particules. La simulation s'arrête dès que le temps écoulé
 * dépasse la valeur t. La fonction retourne ensuite la distance maximale entre
 * deux particules dans l'état obtenu.
 * \param e L'environnement en question
 * \param t Le temps cible à dépasser
 * \return La distance maximale entre deux particules après simulation
 */
static float simulate_to_t(env e, float t) {
    float elapsed = 0.0f;
    float dt = get_dt(e);

    do {
        move_particules(e);
        elapsed += dt;
    } while (elapsed <= t);

    return compute_max_dist(e);
}

/**
 * \brief Sauvegarde l'état courant des particules d'un environnement.
 * \detail Fonction interne utilisée pour conserver la position et la vitesse
 * de chaque particule dans quatre tableaux distincts afin de pouvoir restaurer
 * ultérieurement cette configuration.
 * \param e L'environnement en question
 * \param xs Tableau des abscisses
 * \param ys Tableau des ordonnées
 * \param vxs Tableau des vitesses horizontales
 * \param vys Tableau des vitesses verticales
 */
static void save_state(env e, float *xs, float *ys, float *vxs, float *vys) {
    int n = get_n(e);

    for (int i = 0; i < n; i++) {
        particule p = get_particule(e, i);
        xs[i]  = get_x(p);
        ys[i]  = get_y(p);
        vxs[i] = get_vx(p);
        vys[i] = get_vy(p);
    }
}

/**
 * \brief Restaure un état précédemment sauvegardé de l'environnement.
 * \detail Fonction interne utilisée pour replacer toutes les particules dans
 * une configuration enregistrée, en restaurant leurs positions et leurs
 * vitesses à partir de tableaux.
 * \param e L'environnement en question
 * \param xs Tableau des abscisses
 * \param ys Tableau des ordonnées
 * \param vxs Tableau des vitesses horizontales
 * \param vys Tableau des vitesses verticales
 */
static void restore_state(env e, float *xs, float *ys, float *vxs, float *vys) {
    int n = get_n(e);

    for (int i = 0; i < n; i++) {
        particule p = get_particule(e, i);
        set_position(p, xs[i], ys[i]);
        set_speed(p, vxs[i], vys[i]);
    }
}

/**
 * \brief Place les particules sur une grille avec des vitesses dirigées vers le centre.
 * \detail Fonction interne utilisée comme configuration initiale déterministe.
 * Les particules sont réparties régulièrement dans l'environnement puis leur
 * direction est orientée vers le centre afin de favoriser leur rapprochement.
 * \param e L'environnement en question
 */
static void place_grid_inward(env e) {
    int n = get_n(e);
    float w = get_w(e);
    float h = get_h(e);
    float cx = w / 2.0f;
    float cy = h / 2.0f;

    // Calcule le nombre de colonnes et lignes de la grille
    int cols = (int)ceilf(sqrtf((float)n));
    int rows = (int)ceilf((float)n / cols);

    float margin = 1.0f;
    float x_step;
    float y_step;

    // Si on a plusieurs colonnes et lignes, on espace les particules sur la largeur et la hauteur

    if (cols > 1) {
        x_step = (w - 2.0f * margin) / (cols - 1);
    }
    else {
        x_step = 0.0f;
    }

    if (rows > 1) {
        y_step = (h - 2.0f * margin) / (rows - 1);
    }
    else {
        y_step = 0.0f;
    }

    for (int i = 0; i < n; i++) {
        int row = i / cols;
        int col = i % cols;

        float x;
        float y;

        if (cols > 1) {
            x = margin + col * x_step;
        } else {
            x = cx;
        }

        if (cols > 1) {
           y = margin + row * y_step;
        }
        else {
            y = cy;
        }

        particule p = get_particule(e, i);
        set_position(p, x, y);

        // Direction de la vitesse vers le centre
        float dvx = cx - x;
        float dvy = cy - y;
        float norm = sqrtf(dvx * dvx + dvy * dvy);

        // Si la particule est déjà au centre
        if (norm < 1e-6f) {
            set_speed(p, 1.0f, 0.0f);
        } else {
            set_speed(p, dvx / norm, dvy / norm);
        }
    }
}

/**
 * \brief Place les particules aléatoirement avec des vitesses dirigées vers le centre.
 * \detail Fonction interne utilisée pour tester des configurations initiales
 * variées. Chaque particule est placée aléatoirement dans l'environnement,
 * de préférence sans trop se rapprocher des précédentes, puis sa vitesse est
 * orientée vers le centre de l'environnement.
 * \param e L'environnement en question
 */
static void place_random_inward(env e) {
    int n = get_n(e);
    float r = get_r(e);
    float w = get_w(e);
    float h = get_h(e);
    float cx = w / 2.0f;
    float cy = h / 2.0f;

    for (int i = 0; i < n; i++) {
        float x, y;
        bool ok = false;
        int attempts = 0;

        while (!ok && attempts < 1000) {
            x = r + ((float)rand() / RAND_MAX) * (w - 2.0f * r);
            y = r + ((float)rand() / RAND_MAX) * (h - 2.0f * r);
            ok = true;

            for (int j = 0; j < i; j++) {
                particule pj = get_particule(e, j);
                float dx = x - get_x(pj);
                float dy = y - get_y(pj);

                if (sqrtf(dx * dx + dy * dy) < 2.0f * r) {
                    ok = false;
                    break;
                }
            }
            attempts++;
        }

        // Si aucune bonne position n'a été trouvée
        if (!ok) {
            x = ((float)rand() / RAND_MAX) * w;
            y = ((float)rand() / RAND_MAX) * h;
        }

        particule p = get_particule(e, i);
        set_position(p, x, y);

        // Direction de la vitesse vers le centre
        float dvx = cx - x;
        float dvy = cy - y;
        float norm = sqrtf(dvx * dvx + dvy * dvy);

        // Si la particule est déjà au centre
        if (norm < 1e-6f) {
            set_speed(p, 1.0f, 0.0f);
        }
        else {
            set_speed(p, dvx / norm, dvy / norm);
        }
    }
}

void optimization(env e, float t) {
    int n = get_n(e);
    float *xs      = malloc(n * sizeof(float));
    float *ys      = malloc(n * sizeof(float));
    float *vxs     = malloc(n * sizeof(float));
    float *vys     = malloc(n * sizeof(float));
    float *best_xs  = malloc(n * sizeof(float));
    float *best_ys  = malloc(n * sizeof(float));
    float *best_vxs = malloc(n * sizeof(float));
    float *best_vys = malloc(n * sizeof(float));

    float best_score = FLT_MAX;

    for (int i = 0; i < NUM_TRIALS; i++) {
        // Premier essai en grille, les autres aléatoirement
        if (i == 0) {
            place_grid_inward(e);
        }
        else {
            place_random_inward(e);
        }

        save_state(e, xs, ys, vxs, vys);

        float score = simulate_to_t(e, t);

        // Si cette configuration est meilleure
        if (score < best_score) {
            best_score = score;
            // Sauvegarde des positions et vitesses de la meilleure configuration
            memcpy(best_xs,  xs,  n * sizeof(float));
            memcpy(best_ys,  ys,  n * sizeof(float));
            memcpy(best_vxs, vxs, n * sizeof(float));
            memcpy(best_vys, vys, n * sizeof(float));
        }
    }

    restore_state(e, best_xs, best_ys, best_vxs, best_vys);
    simulate_to_t(e, t);

    free(xs);
    free(ys);
    free(vxs);
    free(vys);
    free(best_xs);
    free(best_ys);
    free(best_vxs);
    free(best_vys);
}
