#include "types.h"

/**
 * Calcule le milieu d'une Hitbox
 */
Vector2 get_middle(Hitbox *h) {
    Vector2 mid = {0, 0};
    switch (h->type & 0x7) {
    case HITBOX_AABB :
        mid.x = h->x + h->w / 2;
        mid.y = h->y + h->h / 2;
        break;
    case HITBOX_TRIANGLE :
        mid.x = h->x + h->w / 3;
        mid.y = h->y + h->h / 3;
        break;
    case HITBOX_CIRCLE :
        mid.x = h->x;
        mid.y = h->y;
        break;
    }
    return mid;
}
