#ifndef _TYPES_H
#define _TYPES_H
#include <SDL3/SDL.h>
#include <math.h>

#define abs_value(x) (double)(((x) > 0) ? (x) : -(x))
#define MAX_NORMAL_COUNT 4
#define MAX_OVERLAP (double)(1000000000.0)

typedef struct Vector2 {
    double x;
    double y;
} Vector2;

typedef enum HitboxType {
    AABB_RECTANGLE = 0x1,
    RIGHT_TRIANGLE = 0x2,
    CIRCLE = 0x4
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
