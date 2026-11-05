## Hitbox

Une librairie de gestion et de résolution de collisions, avec un affichage
des boites de collisions utilisant la librairie SDL3.

Cette librairie propose une structure Hitbox et ses fonctions associées.
La fonction de collision utilise le SAT (Separating Axis Theorem)
pour obtenir le MTV (Minimal Translation Vector) permettant de résoudre
l'éventuelle collision.

Plusieurs types de hitbox sont disponibles :
 - `HITBOX_AABB` : représente un rectangle dont les côtés sont parallèles aux
 axes du repère
 - `HITBOX_TRIANGLE` : représente un triangle rectangle dont les côtés adjacents
 sont parallèles aux axes du repère
 - `HITBOX_CIRCLE` : représente un cercle

Chacun de ces types possède sa variante `*_NS` (pour 'No Slopes') qui permet
de manipuler des hitbox sans aucune interprétation du MTV (MTV 'brut'),
tandis que les types de base subissent une interprétation du
MTV permettant d'implémenter aisément une gestion basique des pentes.

#### Compilation :

(Re)Compilez `libhitbox.so` avec :

    $ make lib

#### Utilisation :

Copiez `hitbox.h` et `libhitbox.so` dans votre projet, `#include "hitbox.h"`
dans votre code.

Puis compilez avec les flags adéquats :

    $ gcc -o your_project your_project.c -L./ -Wl,-rpath=./ -lhitbox

#### Demo :

    $ make demo

Affiche diverses hitbox et permet d'en contrôler une avec la souris.
Le résultat de la résolution de collision est affiché en bleu.

Appuyer sur : 
 - `Space` pour changer la hitbox contrôlée.
 - `u` pour passer en mode pentes
 - `j` pour passer en mode MTV brut.
