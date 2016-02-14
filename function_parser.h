#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlstring.h>
//#include <libxml/xmlmemory>

#define TAILLE_TABLE 4

typedef struct Tag Tag;
typedef struct Node Node;
typedef struct Way Way;
typedef struct Bounds Bounds;
typedef struct Array_All Array_All;

struct Bounds{
	char *minlat;
	char *minlon;
	char *maxlat;
	char *maxlon;
};

struct Tag{
	char *key;
	char *value;
	Tag* suivant;
};

struct Node{
	char *id;
	char *visible;
	char *lon;
	char *lat;
	Tag* node_child;
	Node* suivant;
	Node* precedent;
};



struct Way{
	char *id;
	char *visible;
	Node* ref;
	char *ref_value;
	Tag* child_way;
};

struct Array_All{
	Node* Array_Node;
	Way* Array_Way;
	Bounds* Array_Bounds;
};

