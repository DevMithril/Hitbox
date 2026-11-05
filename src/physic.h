#include <SDL3/SDL.h>
#include <math.h>

#define abs_value(x) (double)(((x) > 0) ? (x) : -(x))

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
 * Normalise un vecteur
 */
void normalize(Vector2 *v);

/*
 * Calcule l'overlap minimal
 */
double get_overlap(double min1, double max1, double min2, double max2);

/*
 * Inverse le sens du mtv si celui-ci résoud la collision pour h2 au lieu de h1
 */
void assert_mtv_for_h1(Vector2 mid1, Vector2 mid2, Vector2 *mtv);

/*
 * Calcule le MTV final si le parametre mtv n'est pas NULL
 * Retourne la valeur de collision
 * Cette fonction est une annexe commune à aabb_rtriangle et rtriangle_rtriangle
 */
bool compute_mtv(double overlap, Vector2 normal, Vector2 *mtv, Vector2 mtv_aa);

/*
 * Calcule les extrema d'une Hitbox sur les axes du repère
 * \param h Hitbox dont on souhaite les extrema
 * \param min sortie des minima sur les axes du repère
 * \param max sortie des maxima sur les axes du repère
 */
void get_extrema(Hitbox *h, Vector2 *min, Vector2 *max);

/*
 * Calcule les extrema d'une Hitbox sur un axe donné
 * \param h Hitbox dont on souhaite les extrema
 * \param min sortie du minimum sur l'axe
 * \param max sortie du maximum sur l'axe
 * \param normal vecteur normal définissant l'axe voulu
 */
void get_extrema_sat(Hitbox *h, double *min, double *max, Vector2 *normal);

/*
 * Calcule le milieu d'une Hitbox
 */
Vector2 get_middle(Hitbox *h);

/*
 * Indique la collision entre deux Hitbox de type AABB_RECTANGLE
 * Calcule le MTV si le paramètre n'est pas NULL
 */
bool aabb_aabb(Hitbox *h1, Hitbox *h2, Vector2 *mtv);

/*
 * Indique la collision entre deux Hitbox de type RIGHT_TRIANGLE
 * Calcule le MTV si le paramètre n'est pas NULL
 */
bool rtriangle_rtriangle(Hitbox *h1, Hitbox *h2, Vector2 *mtv);

/*
 * Indique la collision entre des Hitbox AABB_RECTANGLE et RIGHT_TRIANGLE
 * Calcule le MTV si le paramètre n'est pas NULL
 */
bool aabb_rtriangle(Hitbox *h1, Hitbox *h2, Vector2 *mtv);

/*
 * Indique la collision entre deux Hitbox dont au moins une est un CIRCLE
 * Calcule le MTV si le paramètre n'est pas NULL
 */
bool circle(Hitbox *h1, Hitbox *h2, Vector2 *mtv);

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
