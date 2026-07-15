#include "physic.h"

void normalize(Vector2 *v) {
    double magnitude = sqrt(v->x * v->x + v->y * v->y);
    if (magnitude != 0) {
        v->x /= magnitude;
        v->y /= magnitude;
    }
}
