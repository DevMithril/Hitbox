#include "types.h"

#define square(x) (double)((x) * (x))
#define len(x, y) (double)(square(x) + square(y))
#define abs_value(x) (double)(((x) > 0) ? (x) : -(x))

void get_mtv(double overlap, Vector2 normal, Mtv *mtv) {
    Vector2 new_mtv;

    new_mtv.x = normal.x * overlap;
    new_mtv.y = normal.y * overlap;

    if (len(mtv->x, mtv->y) > len(new_mtv.x, new_mtv.y)) {
        mtv->x = new_mtv.x;
        mtv->y = new_mtv.y;
    }

    if (abs_value(new_mtv.x) > abs_value(new_mtv.y)) {
        new_mtv.x += (new_mtv.y * new_mtv.y) / new_mtv.x;
        new_mtv.y = 0;
    } else {
        new_mtv.y += (new_mtv.x * new_mtv.x) / new_mtv.y;
        new_mtv.x = 0;
    }

    if (abs_value(mtv->xs + mtv->ys) > abs_value(new_mtv.x + new_mtv.y)) {
        mtv->xs = new_mtv.x;
        mtv->ys = new_mtv.y;
    }
}

#undef square
#undef len
#undef abs_value
