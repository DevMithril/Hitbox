#include <stdio.h>
#include <stdlib.h>
#include <SDL3/SDL.h>
#include "../physic.h"

typedef struct Input {
    bool key[SDL_SCANCODE_COUNT];
    bool quit;
    SDL_Point mouse_pos;
    SDL_Scancode key_up, key_down, key_left, key_right, key_jump;
    bool up, down, left, right, jump;
} Input;

void update_Input(Input *input) {
    SDL_Event event;
    while(SDL_PollEvent(&event)) {
        switch (event.type) {
        case SDL_EVENT_QUIT :
            input->quit = true;
            break;
        case SDL_EVENT_KEY_DOWN :
            input->key[event.key.scancode] = true;
            break;
        case SDL_EVENT_KEY_UP :
            input->key[event.key.scancode] = false;
            break;
        case SDL_EVENT_MOUSE_MOTION :
            input->mouse_pos.x = event.motion.x;
            input->mouse_pos.y = event.motion.y;
            break;
        }
    }
    input->down = input->key[input->key_down];
    input->left = input->key[input->key_left];
    input->right = input->key[input->key_right];
    input->up = input->key[input->key_up];
    input->jump = input->key[input->key_jump];
}

void resetKeyState_Input(SDL_Scancode key, Input *input) {
    input->key[key] = false;
}

void load_Input(Input *input) {
    input->key_down = SDL_GetScancodeFromKey(SDLK_J, NULL);
    input->key_up = SDL_GetScancodeFromKey(SDLK_U, NULL);
    input->key_right = SDL_GetScancodeFromKey(SDLK_K, NULL);
    input->key_left = SDL_GetScancodeFromKey(SDLK_H, NULL);
    input->key_jump = SDL_GetScancodeFromKey(SDLK_SPACE, NULL);
}

typedef struct App {
    Hitbox level[7];
    Hitbox cursor[6];
    Hitbox ghost;
    int current_hitbox;
    Input input;
    SDL_Renderer *renderer;
    SDL_Window *window;
} App;

void app_quit(App *app, int status) {
    if (app->renderer)
        SDL_DestroyRenderer(app->renderer);
    if (app->window)
        SDL_DestroyWindow(app->window);
    SDL_Quit();
    exit(status);
}

void app_init(App *app, const char window_name[], int res_x, int res_y, bool fullscreen) {
    if (!SDL_Init(SDL_INIT_VIDEO || SDL_INIT_AUDIO)) {
        printf("SDL_Init() : %s\n", SDL_GetError());
        app_quit(app, EXIT_FAILURE);
    }
    if (fullscreen) {
        app->window = SDL_CreateWindow(window_name, res_x, res_y, SDL_WINDOW_FULLSCREEN | SDL_WINDOW_HIGH_PIXEL_DENSITY);
    } else {
        app->window = SDL_CreateWindow(window_name, res_x, res_y, SDL_WINDOW_HIGH_PIXEL_DENSITY);
    }
    if (!app->window) {
        printf("SDL_CreateWindow() : %s\n", SDL_GetError());
        app_quit(app, EXIT_FAILURE);
    }
    app->renderer = SDL_CreateRenderer(app->window, NULL);
    if (!app->renderer) {
        printf("SDL_CreateRenderer() : %s\n", SDL_GetError());
        app_quit(app, EXIT_FAILURE);
    }
    SDL_SetRenderLogicalPresentation(app->renderer, res_x, res_y, SDL_LOGICAL_PRESENTATION_LETTERBOX);
}

void app_load_assets(App *app) {
    load_Input(&app->input);

    app->level[0].type = AABB_RECTANGLE;
    app->level[0].x = 150;
    app->level[0].y = 150;
    app->level[0].w = 50;
    app->level[0].h = 50;

    app->level[1].type = AABB_RECTANGLE;
    app->level[1].x = 200;
    app->level[1].y = 300;
    app->level[1].w = -50;
    app->level[1].h = -50;

    app->level[2].type = RIGHT_TRIANGLE;
    app->level[2].x = 250;
    app->level[2].y = 150;
    app->level[2].w = 50;
    app->level[2].h = 50;

    app->level[3].type = RIGHT_TRIANGLE;
    app->level[3].x = 300;
    app->level[3].y = 250;
    app->level[3].w = -50;
    app->level[3].h = 50;

    app->level[4].type = RIGHT_TRIANGLE;
    app->level[4].x = 300;
    app->level[4].y = 400;
    app->level[4].w = -50;
    app->level[4].h = -50;

    app->level[5].type = RIGHT_TRIANGLE;
    app->level[5].x = 250;
    app->level[5].y = 500;
    app->level[5].w = 50;
    app->level[5].h = -50;

    app->level[6].type = CIRCLE;
    app->level[6].x = 375;
    app->level[6].y = 175;
    app->level[6].r = 25;
    app->level[6].h = 0;

    app->cursor[0].type = AABB_RECTANGLE;
    app->cursor[0].x = 0;
    app->cursor[0].y = 0;
    app->cursor[0].w = 50;
    app->cursor[0].h = 50;

    app->cursor[1] = app->cursor[0];
    app->cursor[1].type = RIGHT_TRIANGLE;

    app->cursor[2] = app->cursor[1];
    app->cursor[2].w = -50;
    app->cursor[2].h = 50;

    app->cursor[3] = app->cursor[1];
    app->cursor[3].w = -50;
    app->cursor[3].h = -50;

    app->cursor[4] = app->cursor[1];
    app->cursor[4].w = 50;
    app->cursor[4].h = -50;

    app->cursor[5] = app->cursor[0];
    app->cursor[5].type = CIRCLE;
    app->cursor[5].r = 25;
    app->cursor[5].h = 0;

    app->current_hitbox = 0;
    app->ghost = app->cursor[0];
}

void render_demo(App *app) {
    SDL_SetRenderDrawColor(app->renderer, 255, 0, 0, 255);
    for (int i = 0; i < 7; i++) {
        display_hitbox(&app->level[i], 0, 0, app->renderer);
    }
    display_hitbox(&app->cursor[app->current_hitbox], 0, 0, app->renderer);
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 255, 255);
    display_hitbox(&app->ghost, 0, 0, app->renderer);
    SDL_SetRenderDrawColor(app->renderer, 0, 0, 0, 255);
}

int main(void) {
    App app = {.renderer = NULL, .window = NULL};
    Vector2 mtv;

    app_init(&app, "Demo Hitbox", 800, 800, false);
    app_load_assets(&app);

    while (!app.input.quit) {
        update_Input(&app.input);
        SDL_RenderClear(app.renderer);

        if (app.input.jump) {
            app.current_hitbox = (app.current_hitbox + 1) % 6;
            resetKeyState_Input(app.input.key_jump, &app.input);
        }

        app.cursor[app.current_hitbox].x = app.input.mouse_pos.x;
        app.cursor[app.current_hitbox].y = app.input.mouse_pos.y;

        app.ghost = app.cursor[app.current_hitbox];

        collide_bulk(&app.ghost, app.level, 7, sizeof(Hitbox), &mtv);
        move_hitbox(&app.ghost, mtv.x, mtv.y);

        render_demo(&app);
        SDL_RenderPresent(app.renderer);

        SDL_Delay((int)(1000 / 60));
    }

    app_quit(&app, EXIT_SUCCESS);
}
