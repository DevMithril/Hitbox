#include "physic.h"

bool collide(Hitbox *h1, Hitbox *h2, Vector2 *mtv) {
    int types = h1->type | h2->type;

    switch (types) {
    case AABB_RECTANGLE | AABB_RECTANGLE :
        return aabb_aabb(h1, h2, mtv);
    case AABB_RECTANGLE | RIGHT_TRIANGLE :
        if (h2->type == AABB_RECTANGLE) {
            bool collision = aabb_rtriangle(h2, h1, mtv);
            if (mtv) {
                mtv->x *= -1;
                mtv->y *= -1;
            }
            return collision;
        }
        return aabb_rtriangle(h1, h2, mtv);
    case RIGHT_TRIANGLE | RIGHT_TRIANGLE :
        return rtriangle_rtriangle(h1, h2, mtv);
    default :
        if (types & CIRCLE) {
            return circle(h1, h2, mtv);
        }
        if (mtv) *mtv = (Vector2){0, 0};
        return false;
    }
}
