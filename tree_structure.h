#include "function_parser.h"


typedef struct AVL_tree_node AVL_tree_node;

typedef struct AVL_tree_way AVL_tree_way;

typedef struct AVL_node AVL_node;

typedef struct AVL_way AVL_way;

struct AVL_node{
	AVL_node* left;
	AVL_node* right;
	Tag* node_tag;
	char* id;
	char *visible;
	char *lon;
	char *lat;
};

struct AVL_way{
	char *id;
	char *visible;
	Nd* ref;
	Tag* way_tag;
	AVL_way* left;
	AVL_way* right;
};

struct AVL_tree_node{
	AVL_node* root;
};

struct AVL_tree_way{
	AVL_way* root;
};

AVL_tree_node* init_tree_node();

AVL_tree_way* init_tree_way();

AVL_node* create_AVL_node(Node*);

AVL_way* create_AVL_way(Way*);

int height_node(AVL_node*);

int max(int,int);

int left_tree_height(AVL_node*);

int right_tree_height(AVL_node*);

int balance_node(AVL_node*);

AVL_node* left_To_leftRot(AVL_node*);

AVL_node* left_To_rightRot(AVL_node*);

AVL_node* right_To_rightRot(AVL_node*);

AVL_node* right_To_leftRot(AVL_node*);

AVL_node* getNode_balanced(AVL_node*);

void insertion_node(AVL_node*,Node*);

AVL_node* search_node(char*);

