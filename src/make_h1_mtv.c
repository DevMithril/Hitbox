#include "types.h"

Vector2 get_middle(Hitbox *h);

/**
 * Inverse le sens du mtv si celui-ci résout la collision pour h2 au lieu de h1
 */
void make_h1_mtv(Hitbox *h1, Hitbox *h2, Mtv *mtv) {
    Vector2 mid1 = get_middle(h1);
    Vector2 mid2 = get_middle(h2);
    if ((mid2.x - mid1.x) * mtv->x + (mid2.y - mid1.y) * mtv->y > 0) {
        mtv->x *= -1;
        mtv->y *= -1;
    }
    // FIXME : cela ne donne pas toujours le bon sens pour le mtv
    if (mtv->x * mtv->xs + mtv->y * mtv->ys < 0) {
        mtv->xs *= -1;
        mtv->ys *= -1;
    }
}
