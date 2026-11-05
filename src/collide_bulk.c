#include "types.h"

#define square(x) (double)((x) * (x))
#define len(x, y) (double)(square(x) + square(y))

bool collide(Hitbox *h1, Hitbox *h2, Vector2 *mtv);

bool collide_bulk(Hitbox *h, Hitbox *h_arr, int len, int stride, Vector2 *mtv) {
    bool collision = false;
    Vector2 mtv_max = {0, 0};
    size_t cur = (size_t)h_arr;
    size_t end = cur + len * stride;

    while ((mtv || !collision) && cur < end) {
        collision += collide(h, (Hitbox*)cur, mtv);
        if (mtv) {
            if (h->type & 0x8) {
                if (len(mtv->x, mtv->y) > len(mtv_max.x, mtv_max.y)) {
                    mtv_max = *mtv;
                }
            } else {
                if (abs_value(mtv->x) > abs_value(mtv_max.x)) {
                    mtv_max.x = mtv->x;
                }
                if (abs_value(mtv->y) > abs_value(mtv_max.y)) {
                    mtv_max.y = mtv->y;
                }
            }
        }
        cur += stride;
    }

    if (mtv) *mtv = mtv_max;
    return collision;
}

#undef square
#undef len
