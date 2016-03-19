#include "function_parser.h"


typedef struct AVL_tree_way AVL_tree_way;

typedef struct AVL_way AVL_way;

struct AVL_way{
	char *id;
	char *visible;
	Nd* ref;
	Tag* way_tag;
	AVL_way* left;
	AVL_way* right;
};

struct AVL_tree_way{
	AVL_way* root;
};

AVL_tree_way* init_tree_way();

AVL_way* create_AVL_way(Way*);

int height_way(AVL_way*);

int max_way(int,int);

int balance_way(AVL_way*);

AVL_way* left_To_leftRot_Way(AVL_way*);

AVL_way* left_To_rightRot_Way(AVL_way*);

AVL_way* right_To_rightRot_Way(AVL_way*);

AVL_way* right_To_leftRot_Way(AVL_way*);

AVL_way* getway_balanced(AVL_way*);

void insertion_way(AVL_tree_way*,Way*);

AVL_way* search_way(char*);

void affiche_Way(AVL_way*);

void print_spc_way(int);

void affiche_suffixe_Way(AVL_way*,int);

void affiche_indent_Way(AVL_way*,int);

void getTree_belanced_Way(AVL_tree_way*);