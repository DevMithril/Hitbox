#include "types.h"

void get_normals(Hitbox *h1, Hitbox *h2, Vector2 *normals);
void get_extrema(Hitbox *h, Vector2 *extrema, Vector2 normal);
double get_overlap(Vector2 extrema1, Vector2 extrema2);
void get_mtv(double overlap, Vector2 normal, Vector2 *mtv);
void make_h1_mtv(Hitbox *h1, Hitbox *h2, Vector2 *mtv);

bool collide(Hitbox *h1, Hitbox *h2, Vector2 *mtv) {
    Vector2 normals[MAX_NORMAL_COUNT];
    Vector2 h1_extrema, h2_extrema;
    double overlap;

    if (mtv) {
        *mtv = (Vector2){MAX_OVERLAP, 0};
    }
    get_normals(h1, h2, normals);

    for (int i = 0; i < MAX_NORMAL_COUNT; i++) {
        if (normals[i].x == 0 && normals[i].y == 0) {
            continue;
        }
        get_extrema(h1, &h1_extrema, normals[i]);
        get_extrema(h2, &h2_extrema, normals[i]);
        overlap = get_overlap(h1_extrema, h2_extrema);
        if (!overlap) {
            if (mtv) {
                *mtv = (Vector2){0, 0};
            }
            return false;
        }
        if (mtv) {
            get_mtv(overlap, normals[i], mtv);
        }
    }

    if (mtv) {
        make_h1_mtv(h1, h2, mtv);
    }

    return true;
}
