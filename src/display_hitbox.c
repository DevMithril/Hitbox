#include "types.h"

void display_hitbox(Hitbox *h, double ofx, double ofy, SDL_Renderer *renderer) {
    Vector2 min, max, A, B, C;

    switch (h->type & 0x7) {
    case HITBOX_AABB :
        min = (Vector2){round(h->x + ofx), round(h->y + ofy)};
        max = (Vector2){round(h->w + min.x), round(h->h + min.y)};
        
        SDL_RenderLine(renderer, min.x, min.y, max.x, min.y);
        SDL_RenderLine(renderer, max.x, min.y, max.x, max.y);
        SDL_RenderLine(renderer, max.x, max.y, min.x, max.y);
        SDL_RenderLine(renderer, min.x, max.y, min.x, min.y);
        break;
    case HITBOX_TRIANGLE :
        A = (Vector2){round(h->x + ofx), round(h->y + ofy)};
        B = (Vector2){round(h->w + A.x), A.y};
        C = (Vector2){A.x, round(h->h + A.y)};

        SDL_RenderLine(renderer, A.x, A.y, B.x, B.y);
        SDL_RenderLine(renderer, B.x, B.y, C.x, C.y);
        SDL_RenderLine(renderer, C.x, C.y, A.x, A.y);
        break;
    case HITBOX_CIRCLE :
        A = (Vector2){round(h->x + ofx), round(h->y + ofy)};

        for (float x = 0, y = h->r; x < y; x++) {
            for (; y >= 0; y--) {
                SDL_RenderPoint(renderer, A.x+x, A.y+y);
                SDL_RenderPoint(renderer, A.x+x, A.y-y);
                SDL_RenderPoint(renderer, A.x-x, A.y+y);
                SDL_RenderPoint(renderer, A.x-x, A.y-y);

                SDL_RenderPoint(renderer, A.x+y, A.y+x);
                SDL_RenderPoint(renderer, A.x+y, A.y-x);
                SDL_RenderPoint(renderer, A.x-y, A.y+x);
                SDL_RenderPoint(renderer, A.x-y, A.y-x);

                if (x*x + (y-1)*(y-1) < h->r*h->r)
                    break;
            }
        }
        break;
    }
}
