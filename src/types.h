#ifndef _TYPES_H
#define _TYPES_H
#include <SDL3/SDL.h>
#include <math.h>

// TODO : retirer abs_value() et passer en ISO C99
#define abs_value(x) (double)(((x) > 0) ? (x) : -(x))
#define MAX_NORMAL_COUNT 4
#define MAX_OVERLAP (double)(1000000000.0)

typedef struct Vector2 {
    double x;
    double y;
} Vector2;

typedef enum HitboxType {
    HITBOX_AABB = 0x1,
    HITBOX_TRIANGLE = 0x2,
    HITBOX_CIRCLE = 0x4,
    HITBOX_AABB_NS = 0x8 | HITBOX_AABB,
    HITBOX_TRIANGLE_NS = 0x8 | HITBOX_TRIANGLE,
    HITBOX_CIRCLE_NS = 0x8 | HITBOX_CIRCLE
} HitboxType;

typedef struct Hitbox {
    double x;
    double y;
    union {
        double w;
        double r;
    };
    double h;
    HitboxType type;
} Hitbox;

#endif
