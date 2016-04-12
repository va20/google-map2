#ifndef GRAPHIQUE
#define GRAPHIQUE
#include <SDL2/SDL.h>
#include <math.h>
#include "tree_node_structure.h"
#include "tree_way_structure.h"
#include "SDL2/SDL2_gfxPrimitives.h"
#define pi 3.14159265359

SDL_Window* Create_Window(int,int);

int isBuilding(Tag*,char*);

char* valueOf(Tag*,char*);

#endif /* GRAPHIQUE */

