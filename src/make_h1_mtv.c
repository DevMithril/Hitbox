#include "types.h"

Vector2 get_middle(Hitbox *h);

/**
 * Inverse le sens du mtv si celui-ci résoud la collision pour h2 au lieu de h1
 */
void make_h1_mtv(Hitbox *h1, Hitbox *h2, Vector2 *mtv) {
    Vector2 mid1 = get_middle(h1);
    Vector2 mid2 = get_middle(h2);
    if ((mid2.x - mid1.x) * mtv->x + (mid2.y - mid1.y) * mtv->y > 0) {
        mtv->x *= -1;
        mtv->y *= -1;
    }
}
