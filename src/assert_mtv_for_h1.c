#include "physic.h"

void assert_mtv_for_h1(Vector2 mid1, Vector2 mid2, Vector2 *mtv) {
    if ((mid2.x - mid1.x) * mtv->x + (mid2.y - mid1.y) * mtv->y > 0)
    {
        mtv->x *= -1;
        mtv->y *= -1;
    }
}
