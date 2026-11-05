#include "types.h"

/**
 * Calcule les extrema d'une Hitbox sur un axe donné
 * \param h Hitbox dont on souhaite les extrema
 * \param extrema sortie des extrema sur l'axe (x = min, y = max)
 * \param normal vecteur normal définissant l'axe voulu
 */
void get_extrema(Hitbox *h, Vector2 *extrema, Vector2 normal) {
    double p = 0;
    Vector2 points[4];
    int len_points;

    switch (h->type & 0x7) {
    case HITBOX_AABB :
        points[0] = (Vector2){h->x, h->y};
        points[1] = (Vector2){h->x, h->y + h->h};
        points[2] = (Vector2){h->x + h->w, h->y + h->h};
        points[3] = (Vector2){h->x + h->w, h->y};
        len_points = 4;
        break;
    case HITBOX_TRIANGLE :
        points[0] = (Vector2){h->x, h->y};
        points[1] = (Vector2){h->x + h->w, h->y};
        points[2] = (Vector2){h->x, h->y + h->h};
        len_points = 3;
        break;
    case HITBOX_CIRCLE :
        points[0] = (Vector2){h->x, h->y};
        len_points = 1;
        break;
    }

    extrema->x = normal.x * points[0].x + normal.y * points[0].y;
    extrema->y = extrema->x;
    for (int i = 1; i < len_points; i++) {
        p = normal.x * points[i].x + normal.y * points[i].y;
        if (p < extrema->x) {
            extrema->x = p;
        } else if (p > extrema->y) {
            extrema->y = p;
        }
    }

    if (h->type & HITBOX_CIRCLE) {
        extrema->x -= h->r;
        extrema->y += h->r;
    }
}
