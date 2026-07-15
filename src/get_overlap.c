#include "physic.h"

double get_overlap(double min1, double max1, double min2, double max2) {
    double o = (max1 - min2 <= max2 - min1) ? max1 - min2 : max2 - min1;
    o = (o > 0) ? o : 0;
    return o;
}
