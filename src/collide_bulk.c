#include "types.h"

#define square(x) (double)((x) * (x))
#define len(x, y) (double)(square(x) + square(y))
#define abs_value(x) (double)(((x) > 0) ? (x) : -(x))

bool collide(Hitbox *h1, Hitbox *h2, Mtv *mtv);

bool collide_bulk(Hitbox *h, Hitbox *h_arr, int len, int stride, Mtv *mtv) {
    bool collision = false;
    Mtv mtv_max = {0, 0, 0, 0};
    size_t cur = (size_t)h_arr;
    size_t end = cur + len * stride;

    while ((mtv || !collision) && cur < end) {
        collision += collide(h, (Hitbox*)cur, mtv);
        if (mtv) {
            if (len(mtv->x, mtv->y) > len(mtv_max.x, mtv_max.y)) {
                mtv_max.x = mtv->x;
                mtv_max.y = mtv->y;
            }
            if (abs_value(mtv->xs) > abs_value(mtv_max.xs)) {
                mtv_max.xs = mtv->xs;
            }
            if (abs_value(mtv->ys) > abs_value(mtv_max.ys)) {
                mtv_max.ys = mtv->ys;
            }
        }
        cur += stride;
    }

    if (mtv) *mtv = mtv_max;
    return collision;
}

#undef square
#undef len
#undef abs_value
