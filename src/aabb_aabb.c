#include "physic.h"

bool aabb_aabb(Hitbox *h1, Hitbox *h2, Vector2 *mtv) {
    Vector2 min1, max1, min2, max2;

    get_extrema(h1, &min1, &max1);
    get_extrema(h2, &min2, &max2);

    if (!mtv) {
        return !(min1.x > max2.x || min2.x > max1.x 
              || min1.y > max2.y || min2.y > max1.y);
    }

    mtv->x = (min1.x > max2.x || min2.x > max1.x) ? 0 :
            (abs_value(max2.x - min1.x) < abs_value(min2.x - max1.x)) ? 
            max2.x - min1.x : min2.x - max1.x;
    mtv->y = (min1.y > max2.y || min2.y > max1.y) ? 0 :
            (abs_value(max2.y - min1.y) < abs_value(min2.y - max1.y)) ? 
            max2.y - min1.y : min2.y - max1.y;

    (abs_value(mtv->x) < abs_value(mtv->y)) ?
        (mtv->y = 0) :
        (mtv->x = 0);

    return !(mtv->x == 0 && mtv->y == 0);
}
