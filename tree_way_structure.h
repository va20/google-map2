#include "function_parser.h"


typedef struct AVL_tree_way AVL_tree_way;

typedef struct AVL_way AVL_way;

struct AVL_way{
	AVL_way* left;
	AVL_way* right;
	Tag* way_tag;
	int hauteur;
	char* id;
	char *visible;
	Nd* ref;
};

struct AVL_tree_way{
	AVL_way* root;
};

AVL_tree_way* init_tree_way();

AVL_way* create_AVL_way(Way*);

int height_way(AVL_way*);

int max_way(int,int);

int balance_way(AVL_way*);

AVL_way* left_To_leftRot_way(AVL_way*);

AVL_way* left_To_rightRot_way(AVL_way*);

AVL_way* right_To_rightRot_way(AVL_way*);

AVL_way* right_To_leftRot_way(AVL_way*);

AVL_way* getway_balanced(AVL_way*);

AVL_way* insertion_way(AVL_way*,Way*);

AVL_way* search_way(AVL_way*,char*);

void print_spc_way(int);

void affiche_way(AVL_way*);

void affiche_suffixe_way(AVL_way*,int);

void affiche_indent_way(AVL_way*,int);
