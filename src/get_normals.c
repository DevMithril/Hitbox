#include "types.h"

void normalize(Vector2 *v);
Vector2 get_middle(Hitbox *h);

void get_normals(Hitbox *h1, Hitbox *h2, Vector2 *normals) {
    int types = h1->type | h2->type;
    int i = 0;
    Vector2 mid1, mid2;

    if (types & AABB_RECTANGLE || types & RIGHT_TRIANGLE) {
        normals[i++] = (Vector2){1, 0};
        normals[i++] = (Vector2){0, 1};
    }
    if (h1->type & RIGHT_TRIANGLE) {
        normals[i] = (Vector2){h1->h, h1->w};
        normalize(&normals[i]);
        i++;
    }
    if (h2->type & RIGHT_TRIANGLE) {
        normals[i] = (Vector2){h2->h, h2->w};
        normalize(&normals[i]);
        i++;
    }
    if (types & CIRCLE) {
        mid1 = get_middle(h1);
        mid2 = get_middle(h2);
        normals[i] = (Vector2){mid2.x - mid1.x, mid2.y - mid1.y};
        normalize(&normals[i]);
        if (normals[i].x == 0 && normals[i].y == 0) {
            normals[i] = (Vector2){1, 0};
        }
        i++;
    }

    for (; i < MAX_NORMAL_COUNT; i++) {
        normals[i] = (Vector2){0, 0};
    }
}
