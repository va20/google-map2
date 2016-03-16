#include <libxml/tree.h>
#include <libxml/parser.h>
#include <libxml/xmlstring.h>
#include <string.h>
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

struct Nd{
	char* ref;
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
	Tag* way_tag;
	Way* next_way;
};

struct Array_All{
	Node* Array_Node;
	Way* Array_Way;
	Bounds* Array_Bounds;
	Relation* Array_Relation;
};

struct Member{
	char* type;
	char* ref;
	char* role;
	Member* next_member;
};

struct Relation{
	char* id;
	char* visible;
	Member* member_fils;
	Tag* tag_fils;
	Relation* next_relation;
};