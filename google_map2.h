#include "graphic.h"


xmlDocPtr Document_Parser(char*);

xmlNodePtr Root_Retrieve(xmlDocPtr);

void Tree_Retrieve(xmlNodePtr,Array_All*);

Node* Node_Retrieve(xmlNodePtr );

Way* Way_Retrieve(xmlNodePtr);

Tag* Tag_Retrieve(xmlNodePtr);

Tag* Tag_List(xmlNodePtr,void*,char*);

Array_All* Node_add(xmlNodePtr,Array_All*);

Node* Tag_add_Node(xmlNodePtr,Node*);

Way* Tag_add_Way(xmlNodePtr,Way*);

Array_All* Way_add(xmlNodePtr,Array_All*);

Way* Nd_add_Way(xmlNodePtr,Way*);

Nd* Nd_Retrieve(xmlNodePtr);

Relation* Relation_Retrieve(xmlNodePtr);

Relation* Tag_add_Relation(xmlNodePtr,Relation*);

Relation* Member_add_Relation(xmlNodePtr,Relation*);

Array_All* Relation_add(xmlNodePtr,Array_All*);

Bounds* Bounds_Retrieve(xmlNodePtr);
