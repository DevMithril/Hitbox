/*
================================================================================
    zlib License
================================================================================

Copyright (c) 2026 Théophane Bruyelles

This software is provided 'as-is', without any express or implied warranty.
In no event will the authors be held liable for any damages arising from
the use of this software.

Permission is granted to anyone to use this software for any purpose,
including commercial applications, and to alter it and redistribute it freely,
subject to the following restrictions:

1. The origin of this software must not be misrepresented;
   you must not claim that you wrote the original software.
   If you use this software in a product, an acknowledgment in the product
   documentation would be appreciated but is not required.
2. Altered source versions must be plainly marked as such,
   and must not be misrepresented as being the original software.
3. This notice may not be removed or altered from any source distribution.

*/

#ifndef HITBOX_LIB_H
#define HITBOX_LIB_H
#include <SDL3/SDL.h>
#include <math.h>

/*
================================================================================
    Hitbox
================================================================================
*/

typedef enum HitboxType {
    // MTV interprété pour les pentes
    HITBOX_AABB = 0x1,
    HITBOX_TRIANGLE = 0x2,
    HITBOX_CIRCLE = 0x4,
    // MTV brut (No Slopes)
    HITBOX_AABB_NS = 0x8 | HITBOX_AABB,
    HITBOX_TRIANGLE_NS = 0x8 | HITBOX_TRIANGLE,
    HITBOX_CIRCLE_NS = 0x8 | HITBOX_CIRCLE
} HitboxType;

typedef struct Vector2 {
    double x;
    double y;
} Vector2;

typedef struct Hitbox {
    double x;
    double y;
    union {
        double w;
        double r;
    };
    double h;
    HitboxType type;
} Hitbox;

/**
 * Indique la collision entre deux Hitbox
 * \param h1 première Hitbox
 * \param h2 deuxième Hitbox
 * \param mtv paramètre de sortie du MTV (Minimal Translation Vector)
 * \return true si h1 et h2 sont en collision, false sinon
 * \note le MTV fourni permet de résoudre la collision en l'applicant sur 'h1'
 * \note si on ne souhaite pas calculer le MTV, 'mtv' peut être NULL
 */
bool collide(Hitbox *h1, Hitbox *h2, Vector2 *mtv);

/**
 * Indique la collision entre une Hitbox et plusieurs Hitbox
 * \param h Hitbox à tester
 * \param h_arr tableau des Hitbox à tester
 * \param len taille du tableau
 * \param stride taille d'un élément du tableau
 * \param mtv paramètre de sortie du MTV (Minimal Translation Vector)
 * \return true si 'h' est en collision avec au moins une Hitbox de 'h_arr'
 * \note 'stride' permet d'utiliser un tableau ne contenant pas que des Hitbox
 * \note le MTV fourni permet de résoudre la collision en l'applicant sur 'h'
 * \note si on ne souhaite pas calculer le MTV, 'mtv' peut être NULL
 */
bool collide_bulk(Hitbox *h, Hitbox *h_arr, int len, int stride, Vector2 *mtv);

/**
 * Déplace une Hitbox
 * \param h Hitbox à déplacer
 * \param x déplacement horizontal à effectuer
 * \param y déplacement vertical à effectuer
 */
void move_hitbox(Hitbox *h, double x, double y);

/**
 * Affiche une Hitbox
 * \param h Hitbox à afficher
 * \param ofx décalage horizontal de l'affichage (offset x)
 * \param ofy décalage vertical de l'affichage (offset y)
 * \param renderer destination d'affichage
 */
void display_hitbox(Hitbox *h, double ofx, double ofy, SDL_Renderer *renderer);

#endif
