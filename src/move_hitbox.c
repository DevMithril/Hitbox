#include "types.h"

void move_hitbox(Hitbox *h, double x, double y) {
    h->x += x;
    h->y += y;
}
