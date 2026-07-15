#include "physic.h"

bool rtriangle_rtriangle(Hitbox *h1, Hitbox *h2, Vector2 *mtv) {
    if (mtv) {
        *mtv = (Vector2){0, 0};
    }
    Vector2 mtv_aa;
    if (!aabb_aabb(h1, h2, &mtv_aa)) {
        return false;
    }

    double min1, max1, min2, max2;

    Vector2 normal = {-h1->h, -h1->w};
    if (mtv) {
        normalize(&normal);
    }

    get_extrema_sat(h1, &min1, &max1, &normal);
    get_extrema_sat(h2, &min2, &max2, &normal);

    double overlap = get_overlap(min1, max1, min2, max2);

    if (!overlap) {
        return false;
    }

    Vector2 normal2 = {h2->h, h2->w};
    if (mtv) {
        normalize(&normal2);
    }

    get_extrema_sat(h1, &min1, &max1, &normal2);
    get_extrema_sat(h2, &min2, &max2, &normal2);

    double overlap2 = get_overlap(min1, max1, min2, max2);

    if (overlap > overlap2) {
        overlap = overlap2;
        normal = normal2;
    }

    assert_mtv_for_h1(get_middle(h1), get_middle(h2), &normal);

    return compute_mtv(overlap, normal, mtv, mtv_aa);
}
