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

//methode pour recuperer les valeurs des attributs de bounds
Bounds* Bounds_Retrieve(xmlNodePtr xml_node){
	Bounds* bounds=NULL;
	bounds=malloc(sizeof(Bounds));
	bounds->minlat=(char *)xmlGetProp(xml_node,(const xmlChar *)"minlat");
	bounds->minlon=(char *)xmlGetProp(xml_node,(const xmlChar *)"minlon");
	bounds->maxlat=(char *)xmlGetProp(xml_node,(const xmlChar *)"maxlat");	
	bounds->maxlon=(char *)xmlGetProp(xml_node,(const xmlChar *)"maxlon");
	return bounds;
}

//methode pour recuperer les valeurs des attributs d'un noeud

Node* Node_Retrieve(xmlNodePtr xml_node){
	Node* node;
	node=malloc(sizeof(Node));
	node->id=(char *)xmlGetProp(xml_node,(const xmlChar *)"id");
	node->visible=(char *)xmlGetProp(xml_node,(const xmlChar *)"visible");
	node->lon=(char *)xmlGetProp(xml_node,(const xmlChar *)"lon");
	node->lat=(char *)xmlGetProp(xml_node,(const xmlChar *)"lat");
	node->node_child=NULL;
	node->suivant=NULL;
	node->precedent=NULL;
	return node;
}
//methode pour recuperer les valeurs de chaque tag

Tag* Tag_Retrieve(xmlNodePtr xml_node){
	Tag* tag;
	tag=malloc(sizeof(Tag));
	tag->key=(char *)xmlGetProp(xml_node,(const xmlChar *)"k");
	tag->value=(char *)xmlGetProp(xml_node,(const xmlChar *)"v");
	return tag;
}

//methode pour parcourir la liste des tags dans chaque noeud
void Tag_List(xmlNodePtr tag,Node* node_with_tag){
	Tag* tmp_tag=NULL;
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
		tag=tag->next;
	}
	return;
}

//methode pour parcourir le fichier xml et stocker les valeurs recupere
void Tree_Retrieve(xmlNodePtr nodePtr,Array_All* tab){
	printf("Tree : %s\n",nodePtr->name);
	nodePtr=nodePtr->xmlChildrenNode;
	nodePtr=nodePtr->next;
	while(nodePtr!=NULL){
		if((!xmlStrcmp(nodePtr->name,(const xmlChar *)"bounds"))){
			tab->Array_Bounds=Bounds_Retrieve(nodePtr);

		}
		if((!xmlStrcmp(nodePtr->name,(const xmlChar *)"node"))){
			Node* tmp=NULL;
			if(tab->Array_Node==NULL){
				tmp=Node_Retrieve(nodePtr);
				tab->Array_Node=tmp;
			}
			else{
				tmp=Node_Retrieve(nodePtr);
				tmp->suivant=tab->Array_Node->suivant;
				tmp->precedent=tab->Array_Node;
				tab->Array_Node->suivant=tmp;
				tab->Array_Node->suivant->precedent=tmp;
			}
			if(nodePtr->children!=NULL){
				Tag_List(nodePtr->children,tab->Array_Node);
			}
		}
		nodePtr=nodePtr->next;
		
		
	}
	return;
}