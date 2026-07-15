#include "physic.h"

Vector2 get_middle(Hitbox *h) {
    Vector2 mid = {0, 0};
    switch (h->type) {
    case AABB_RECTANGLE :
        mid.x = h->x + h->w / 2;
        mid.y = h->y + h->h / 2;
        break;
    case RIGHT_TRIANGLE :
        mid.x = h->x + h->w / 3;
        mid.y = h->y + h->h / 3;
        break;
    case CIRCLE :
        mid.x = h->x;
        mid.y = h->y;
        break;
    }
    return mid;
}
