#include "function_parser.h"


xmlDocPtr Document_Parser(char *file){
	xmlDocPtr xmlFile;
	xmlFile=xmlParseFile(file);
	if(xmlFile==NULL){
		fprintf(stderr, "Document n'est pas parsé \n");
		return NULL;
	}
	return xmlFile;
}


xmlNodePtr Root_Retrieve(xmlDocPtr xmlFile){
	xmlNodePtr nodePtr;
	nodePtr=xmlDocGetRootElement(xmlFile);
	if(nodePtr==NULL){
		fprintf(stderr,"Le document est vide \n");
		xmlFreeDoc(xmlFile);
		return NULL;
	}
	if (xmlStrcmp(nodePtr->name,(const xmlChar *)"osm")){
		fprintf(stderr, "Le document est vide \n");
		xmlFreeDoc(xmlFile);
		return NULL;
	}
	return nodePtr;
}
Bounds* Bounds_Retrieve(xmlNodePtr xml_node){
	Bounds* bounds=NULL;
	bounds=malloc(sizeof(Bounds));
	xmlAttrPtr attr_list_bounds;
	attr_list_bounds=xml_node->properties;
	while(attr_list_bounds!=NULL){
		if ((!xmlStrcmp(attr_list_bounds->name,(const xmlChar *)"minlat")))
		{
			bounds->minlat=(char *)xmlGetProp(xml_node,attr_list_bounds->name);
			//printf("minlat : %s\n",bounds->minlat);
		}
		else if((!xmlStrcmp(attr_list_bounds->name,(const xmlChar *)"minlon"))){
			bounds->minlon=(char *)xmlGetProp(xml_node,attr_list_bounds->name);	
			//printf("minlon : %s\n",bounds->minlon);
		}
		else if((!xmlStrcmp(attr_list_bounds->name,(const xmlChar *)"maxlat"))){

			bounds->maxlat=(char *)xmlGetProp(xml_node,attr_list_bounds->name);	
			//printf("maxlat : %s\n",bounds->maxlat);
		}
		else if((!xmlStrcmp(attr_list_bounds->name,(const xmlChar *)"maxlon"))){

			bounds->maxlon=(char *)xmlGetProp(xml_node,attr_list_bounds->name);	
			//printf("maxlon : %s\n",bounds->maxlon);
		}
		attr_list_bounds=attr_list_bounds->next;
		//printf("bounds attributs name: %s\n",attr_list_bounds->name );
		//printf("bounds attributs valeur : %s\n",xmlGetProp(xml_node,attr_list_bounds->name));
		
	}
	printf("bounds est fini\n");
	return bounds;
}

Node* Node_Retrieve(xmlNodePtr xml_node){
	Node* node;
	node=malloc(sizeof(Node));
	xmlAttrPtr attr_list_node=NULL;
	attr_list_node=xml_node->properties;
	while(attr_list_node!=NULL){
		if((!xmlStrcmp(attr_list_node->name,(const xmlChar *)"id"))){
			node->id=(char *)xmlGetProp(xml_node,attr_list_node->name);
			printf("node id: %s\n",node->id );
		}
		else if((!xmlStrcmp(attr_list_node->name,(const xmlChar *)"visible"))){
			node->visible=(char *)xmlGetProp(xml_node,attr_list_node->name);
			printf("node visible: %s\n",node->visible);

		}
		else if((!xmlStrcmp(attr_list_node->name,(const xmlChar *)"lon"))){
			node->lon=(char *)xmlGetProp(xml_node,attr_list_node->name);						
			printf("node lon: %s\n",node->lon);

		}
		else if((!xmlStrcmp(attr_list_node->name,(const xmlChar *)"lat"))){
			node->lat=(char *)xmlGetProp(xml_node,attr_list_node->name);
			printf("node lat: %s\n",node->lat);

		}
		//printf("node attributs name: %s\n",attr_list_node->name );
		//printf("node attributs valeur : %s\n",xmlGetProp(xml_node,attr_list_node->name));
		attr_list_node=attr_list_node->next;
	}
	node->node_child=NULL;
	node->suivant=NULL;
	node->precedent=NULL;
	return node;
}

Tag* Tag_Retrieve(xmlNodePtr xml_node){

	Tag* tag;
	tag=malloc(sizeof(Tag));
	xmlAttrPtr attr_list_tag=NULL;
	attr_list_tag=xml_node->properties;
	while(attr_list_tag!=NULL){
		if((!xmlStrcmp(attr_list_tag->name,(const xmlChar *)"k"))){
			tag->key=(char *)xmlGetProp(xml_node,attr_list_tag->name);
			//printf("tag key %s\n",tag->key);
		}
		else if((!xmlStrcmp(attr_list_tag->name,(const xmlChar *)"v"))){
			tag->value=(char *)xmlGetProp(xml_node,attr_list_tag->name);
			//printf("tag value %s\n",tag->value);
		}
		//printf("tag attributs name: %s\n",attr_list_tag->name );
		//printf("tag attributs valeur : %s\n",xmlGetProp(xml_node,attr_list_tag->name));
		attr_list_tag=attr_list_tag->next;
	}
	return tag;
}

void Tag_List(xmlNodePtr tag,Node* node_with_tag){
	Tag* tmp_tag=NULL;
	static int cmpTag=0;
	while(tag!=NULL){
		if(node_with_tag->node_child==NULL){
			tmp_tag=Tag_Retrieve(tag);
			node_with_tag->node_child=tmp_tag;
		}
		else{
			tmp_tag=Tag_Retrieve(tag);
			tmp_tag->suivant=node_with_tag->node_child;
			node_with_tag->node_child=tmp_tag;
		}
		cmpTag++;
		tag=tag->next;
	}
	printf("nombre de tag dans Tag liste %d\n", cmpTag);
	return;
}

void Tree_Retrieve(xmlNodePtr nodePtr,Array_All* tab){
	int cmpNode=0;
	printf("Tree : %s\n",nodePtr->name);
	nodePtr=nodePtr->xmlChildrenNode;
	nodePtr=nodePtr->next;
	while(nodePtr!=NULL){
		if((!xmlStrcmp(nodePtr->name,(const xmlChar *)"bounds"))){
			printf("on est dans la boucle \n");
			tab->Array_Bounds=Bounds_Retrieve(nodePtr);
			printf("bounds recupere\n");

		}
		if((!xmlStrcmp(nodePtr->name,(const xmlChar *)"node"))){
			cmpNode++;
			Node* tmp=NULL;
			if(tab->Array_Node==NULL){
				tmp=Node_Retrieve(nodePtr);
				tab->Array_Node=tmp;
			}
			else{
				//printf("precedent %s\n", tab->Array_Node->suivant);
				tmp=Node_Retrieve(nodePtr);
				//printf("precedent %s\n", tab->Array_Node->suivant);
				//printf("apres le 1er etape\n");
				tmp->suivant=tab->Array_Node->suivant;
				//printf("apres le 2eme etape\n");
				//printf("precedent %s\n", tab->Array_Node->suivant);
				tmp->precedent=tab->Array_Node;
				//printf("apres le 3eme etape\n");
				tab->Array_Node->suivant=tmp;
				//printf("apres le 4eme etape\n");
				tab->Array_Node->suivant->precedent=tmp;
				//printf("apres le 5eme etape\n");
			}
			if(nodePtr->children!=NULL){
				printf("%s\n",nodePtr->children->name);
				printf("%p\n",nodePtr->children);
				Tag_List(nodePtr->children,tab->Array_Node);
			}
		}
		nodePtr=nodePtr->next;
		
		
	}
	printf("nombre de node dans Tree%d\n",cmpNode );
	printf("on a fini avec tree\n");
	return;
}