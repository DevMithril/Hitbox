#include "physic.h"

bool compute_mtv(double overlap, Vector2 normal, Vector2 *mtv, Vector2 mtv_aa) {
    if (!overlap) {
        return false;
    }

    if (mtv) {
        mtv->x = normal.x * overlap;
        mtv->y = normal.y * overlap;

        if (abs_value(mtv->x) > abs_value(mtv->y)) {
            mtv->x += (mtv->y * mtv->y) / mtv->x;
            mtv->y = 0;
        } else {
            mtv->y += (mtv->x * mtv->x) / mtv->y;
            mtv->x = 0;
        }

        if (abs_value(mtv->x + mtv->y) > abs_value(mtv_aa.x + mtv_aa.y)) {
            *mtv = mtv_aa;
        }
    }

    return true;
}
