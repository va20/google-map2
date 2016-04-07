#ifndef GRAPHIQUE
#define GRAPHIQUE
#include <SDL2/SDL.h>
#include <SDL2/SDL2_gfxPrimitives.h>
#include "tree_node_structure.h"
#include "tree_way_structure.h"

SDL_Window* Create_Window(char*,char*,char*,char*);
void draw_points(Node* list_node,SDL_Renderer*);

#endif

