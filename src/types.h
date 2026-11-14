#ifndef _TYPES_H
#define _TYPES_H
#include <SDL3/SDL.h>
#include <math.h>

#define MAX_NORMAL_COUNT 4
#define MAX_OVERLAP (double)(1000000000.0)

typedef struct Vector2 {
    double x;
    double y;
} Vector2;

typedef struct Mtv {
    double x;
    double y;
    double xs;
    double ys;
} Mtv;

typedef enum HitboxType {
    HITBOX_AABB = 0x1,
    HITBOX_TRIANGLE = 0x2,
    HITBOX_CIRCLE = 0x4
} HitboxType;

typedef struct Hitbox {
    double x;
    double y;
    double w;
    double h;
    double r;
    HitboxType type;
} Hitbox;

#endif
