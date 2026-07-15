#include <SDL3/SDL.h>
#include <stdbool.h>
#include <math.h>

typedef struct Vector2 {
    double x;
    double y;
} Vector2;

/*
 * +-------------------------------------------------------------------------+
 * |                                HITBOX                                   |
 * +-------------------------------------------------------------------------+
 */

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

/*
 * Indique la collision entre deux Hitbox
 * \param h1 première Hitbox
 * \param h2 deuxième Hitbox
 * \param mtv paramètre de sortie du MTV (Minimal Translation Vector)
 * \return true si h1 et h2 sont en collision, false sinon
 * \note le MTV fourni permet de résoudre la collision en l'applicant sur 'h1'
 * \note si on ne souhaite pas calculer le MTV, 'mtv' peut être NULL
 */
bool collide(Hitbox *h1, Hitbox *h2, Vector2 *mtv);

/*
 * Indique la collision entre une Hitbox et plusieurs Hitbox
 * \param h Hitbox à tester
 * \param h_arr tableau des Hitbox à tester
 * \param len taille du tableau
 * \param stride taille d'un élément du tableau
 * \param mtv paramètre de sortie du MTV (Minimal Translation Vector)
 * \return true si 'h' est en collision avec au moins une Hitbox de 'h_arr'
 * \note 'stride' permet d'utiliser un tableau ne contenant pas que des Hitbox
 * \note le MTV fourni permet de résoudre la collision en l'applicant sur 'h'
 * \note si on ne souhaite pas calculer le MTV, 'mtv' peut être NULL
 */
bool collide_bulk(Hitbox *h, Hitbox *h_arr, int len, int stride, Vector2 *mtv);

/*
 * Déplace une Hitbox
 * \param h Hitbox à déplacer
 * \param x déplacement horizontal à effectuer
 * \param y déplacement vertical à effectuer
 */
void move_hitbox(Hitbox *h, double x, double y);

/*
 * Affiche une Hitbox
 * \param h Hitbox à afficher
 * \param ofx décalage horizontal de l'affichage (offset x)
 * \param ofy décalage vertical de l'affichage (offset y)
 * \param renderer destination d'affichage
 */
void display_hitbox(Hitbox *h, double ofx, double ofy, SDL_Renderer *renderer);

/*
 * +------------------------------------------------------------------------+
 * |                                PHYSIC                                  |
 * +------------------------------------------------------------------------+
 */

typedef struct Body {
    Hitbox hitbox;
    Vector2 velocity;
    Vector2 mtv;
    Vector2 friction;
    double weight;
    double gravity;
} Body;

void update_body(Body *b);

void add_velocity(Body *b, double x, double y);

void add_mtv(Body *b, Vector2 mtv);
