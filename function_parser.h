#ifndef FUNCTION_PARSER
#define FUNCTION_PARSER 
#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlstring.h>
#include <string.h>
#include <stddef.h>
//#include <libxml/xmlmemory>

#define TAILLE_TABLE 4

typedef struct Tag Tag;
typedef struct Nd Nd;
typedef struct Node Node;
typedef struct Way Way;
typedef struct Bounds Bounds;
typedef struct Relation Relation;
typedef struct Member Member;
typedef struct Array_All Array_All;
typedef struct AVL_tree_node AVL_tree_node;
typedef struct AVL_node AVL_node;
typedef struct AVL_tree_way AVL_tree_way;
typedef struct AVL_way AVL_way;

struct Bounds{
	char *minlat;
	char *minlon;
	char *maxlat;
	char *maxlon;
};

struct Tag{
	char *key;
	char *value;
	int multip_test;
	Tag* suivant;
};

struct AVL_node{
	AVL_node* left;
	AVL_node* right;
	Tag* node_tag;
	int hauteur;
	char* id;
	char *visible;
	char *lon;
	char *lat;
};


struct Nd{
	char* ref;
	Node* value_ref;
	Nd* next_nd;
};

struct Node{
	char *id;
	char *visible;
	char *lon;
	char *lat;

	Tag* node_tag;
	Node* suivant;
	Node* precedent;
};



struct Way{
	char *id;
	char *visible;
	Nd* ref;
	int islast;
	Nd* first;
	Nd* last;
	int nb_ref;
	char *way_type;
	Tag* way_tag;
	Way* next_way;
};


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

struct Array_All{
	Node* Array_Node;
	size_t size_list_node;
	Way* Array_Way;
	size_t size_list_way;
	Bounds* Array_Bounds;
	Relation* Array_Relation;
};

struct Member{
	char* type;
	char* ref;
	char* role;
	Node* node_ref;
	Way* way_ref;
	Member* next_member;
};

struct Relation{
	char* id;
	char* visible;
	Member* member_fils;
	Tag* tag_fils;
	int isMultiPolygon;
	Relation* next_relation;
};

struct AVL_tree_node{
	AVL_node* root;
};
#endif