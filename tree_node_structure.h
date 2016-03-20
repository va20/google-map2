#include "function_parser.h"

AVL_tree_node* init_tree_node();

AVL_node* create_AVL_node(Node*);

int height_node(AVL_node*);

int max_node(int,int);

int balance_node(AVL_node*);

AVL_node* left_To_leftRot(AVL_node*);

AVL_node* left_To_rightRot(AVL_node*);

AVL_node* right_To_rightRot(AVL_node*);

AVL_node* right_To_leftRot(AVL_node*);

AVL_node* getNode_balanced(AVL_node*);

AVL_node* insertion_node(AVL_node*,Node*);

AVL_node* search_node(AVL_node*,char*);

void print_spc(int);

void affiche(AVL_node*);

void affiche_suffixe(AVL_node*,int);

void affiche_indent(AVL_node*,int);

void getTree_belanced(AVL_tree_node*);