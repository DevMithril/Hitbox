#include "types.h"

double get_overlap(Vector2 extrema1, Vector2 extrema2) {
    double o;
    if (extrema1.y - extrema2.x <= extrema2.y - extrema1.x) {
        o = extrema1.y - extrema2.x;
    } else {
        o = extrema2.y - extrema1.x;
    }
    o = (o > 0) ? o : 0;
    return o;
}
