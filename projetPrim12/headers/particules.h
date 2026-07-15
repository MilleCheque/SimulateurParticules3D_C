#ifndef PARTICULES_H
#define PARTICULES_H


typedef struct particule* particule;


/*La fonction create_particule sert à créer et initialiser une particule.
 Elle prend en entrée les coordonnées de position (x, y) et les composantes de vitesse (vx, vy).
  La fonction alloue l’espace mémoire nécessaire pour la particule, place celle-ci à la position indiquée
   et définit sa vitesse selon le vecteur fourni. Si ce vecteur de vitesse n’est pas de norme 1, 
   il est automatiquement normalisé afin que la particule ait une vitesse unitaire.*/
particule create_particule(float x, float y, float vx, float vy);



/*La fonction free_particule sert à libérer la mémoire occupée par une particule précédemment créée.
 Elle prend en entrée un pointeur vers la particule à libérer et ne renvoie aucune valeur.
  Son rôle est de s’assurer que les ressources mémoire utilisées par la particule sont correctement libérées pour éviter les fuites de mémoire.*/
void free_particule (particule p);


/*La fonction get_x permet d’obtenir l’abscisse d’une particule. 
Elle prend en entrée une particule et renvoie un nombre à virgule flottante correspondant à sa position sur l’axe des x.*/
float get_x(particule p);


/*La fonction get_y permet d’obtenir l’ordonnée d’une particule. 
Elle prend en entrée une particule et renvoie un nombre à virgule flottante correspondant à sa position sur l’axe des y.*/
float get_y(particule p);



/*La fonction get_vx permet d’obtenir la composante horizontale de la vitesse d’une particule.
 Elle prend en entrée une particule et renvoie un nombre à virgule flottante correspondant à sa vitesse selon l’axe des x.*/
float get_vx(particule p);




/*La fonction get_vy permet d’obtenir la composante verticale de la vitesse d’une particule.
 Elle prend en entrée une particule et renvoie un nombre à virgule flottante correspondant à sa vitesse selon l’axe des y.*/
float get_vy(particule p);



/*La fonction set_position permet de modifier la position d’une particule.
 Elle prend en entrée une particule ainsi que deux nombres à virgule flottante x et y, et met 
 à jour la particule pour qu’elle se trouve à la position (x, y).*/
void set_position(particule p, float x, float y);



/*La fonction set_speed permet de modifier la vitesse d’une particule.
 Elle prend en entrée une particule ainsi que deux nombres à virgule flottante vx et vy, et met 
 à jour la particule pour qu’elle se déplace à la vitesse (vx, vy).*/
void set_speed(particule p, float vx, float vy);

/*La fonction move permet de déplacer une particule en fonction de sa vitesse. 
Elle prend en entrée une particule et un nombre à virgule flottante dt, représentant un intervalle de temps en secondes, 
et met à jour la position de la particule comme si elle se déplaçait en ligne droite pendant dt secondes.*/
void move(particule p, float dt);



/*La fonction distance calcule la distance entre deux particules. 
Elle prend en entrée deux particules et renvoie un nombre à virgule flottante correspondant à la distance euclidienne séparant leurs positions.*/
float distance(particule p1, particule p2);


#endif