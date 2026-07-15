#include "physic.h"

bool aabb_rtriangle(Hitbox *h1, Hitbox *h2, Vector2 *mtv) {
    if (mtv) {
        *mtv = (Vector2){0, 0};
    }
    Vector2 mtv_aa;
    if (!aabb_aabb(h1, h2, &mtv_aa)) {
        return false;
    }

    double min1, max1, min2, max2, overlap;

    Vector2 normal = {h2->h, h2->w};
    if (mtv) {
        normalize(&normal);
    }

    get_extrema_sat(h1, &min1, &max1, &normal);
    get_extrema_sat(h2, &min2, &max2, &normal);

    overlap = get_overlap(min1, max1, min2, max2);

    assert_mtv_for_h1(get_middle(h1), get_middle(h2), &normal);

    return compute_mtv(overlap, normal, mtv, mtv_aa);
}
