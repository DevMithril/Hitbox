#include "physic.h"

void get_extrema(Hitbox *h, Vector2 *min, Vector2 *max) {
    *min = (Vector2){h->x, h->y};
    *max = *min;

    (h->w > 0) ?
        (max->x += h->w) :
        (min->x += h->w);

    (h->h > 0) ?
        (max->y += h->h) :
        (min->y += h->h);
}
