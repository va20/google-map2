#include "function_parser.h"

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

Bounds* Bounds_Retrieve(xmlNodePtr);
