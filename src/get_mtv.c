#include "types.h"

#define square(x) (double)((x) * (x))
#define len(x, y) (double)(square(x) + square(y))
#define abs_value(x) (double)(((x) > 0) ? (x) : -(x))

void get_mtv(double overlap, Vector2 normal, Vector2 *mtv, bool slopes) {
    Vector2 new_mtv;
    (void)slopes;

    new_mtv.x = normal.x * overlap;
    new_mtv.y = normal.y * overlap;

    if (!slopes) {
        if (len(mtv->x, mtv->y) > len(new_mtv.x, new_mtv.y)) {
            *mtv = new_mtv;
        }
        return;
    }

    if (abs_value(new_mtv.x) > abs_value(new_mtv.y)) {
        new_mtv.x += (new_mtv.y * new_mtv.y) / new_mtv.x;
        new_mtv.y = 0;
    } else {
        new_mtv.y += (new_mtv.x * new_mtv.x) / new_mtv.y;
        new_mtv.x = 0;
    }

    if (abs_value(mtv->x + mtv->y) > abs_value(new_mtv.x + new_mtv.y)) {
        *mtv = new_mtv;
    }
}

#undef square
#undef len
#undef abs_value
