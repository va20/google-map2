#include "function_parser.h"

xmlDocPtr Document_Parser(char*);

xmlNodePtr Root_Retrieve(xmlDocPtr);

void Tree_Retrieve(xmlNodePtr,Array_All*);

Node* Node_Retrieve(xmlNodePtr );

Way* Way_Retrieve(xmlNodePtr);

Tag* Tag_Retrieve(xmlNodePtr);

void Tag_List(xmlNodePtr,Node*);

Bounds* Bounds_Retrieve(xmlNodePtr);