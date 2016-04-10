#ifndef GRAPHIQUE
#define GRAPHIQUE
#include <SDL2/SDL.h>
#include <math.h>
#include "tree_node_structure.h"
#include "tree_way_structure.h"

SDL_Window* Create_Window(char*,char*,char*,char*);
void draw_points(Node* list_node,SDL_Renderer*);
Sint16* create_tab_poly(Way*);
void init_tab_poly(Sint16*,Sint16*,Way*,double,double,double,int,int);
int isBuilding(Tag*,char*);
char* valueOf(Tag*,char*);


#endif /* GRAPHIQUE */

