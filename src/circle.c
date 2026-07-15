#include "physic.h"

// FIXME : circle vs circle ok, mais pas les autres
bool circle(Hitbox *h1, Hitbox *h2, Vector2 *mtv) {
    double min1, max1, min2, max2, overlap;
    Vector2 mid1 = get_middle(h1);
    Vector2 mid2 = get_middle(h2);

    Vector2 normal = {mid2.x - mid1.x, mid2.y - mid1.y};
    if (mtv) {
        normalize(&normal);
    }

    get_extrema_sat(h1, &min1, &max1, &normal);
    get_extrema_sat(h2, &min2, &max2, &normal);

    overlap = get_overlap(min1, max1, min2, max2);
    if (mtv) {
        mtv->x = normal.x * overlap;
        mtv->y = normal.y * overlap;        
        assert_mtv_for_h1(mid1, mid2, mtv);
    }

    return overlap;
}
