#include "types.h"

void get_mtv(double overlap, Vector2 normal, Vector2 *mtv) {
    Vector2 new_mtv;

    new_mtv.x = normal.x * overlap;
    new_mtv.y = normal.y * overlap;

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
