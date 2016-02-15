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
//methode pour recuperer les valeurs de chaque tag
Tag* Tag_Retrieve(xmlNodePtr xml_node){
	static int cmpTag=0;
	Tag* tag;
	tag=malloc(sizeof(Tag));

	tag->key=(char *)xmlGetProp(xml_node,(const xmlChar *)"k");
	tag->value=(char *)xmlGetProp(xml_node,(const xmlChar *)"v");
	tag->suivant=NULL;
	cmpTag++;
	printf("tag %d\n",cmpTag );
	return tag;
}


Node* Tag_add_Node(xmlNodePtr tag_To_add,Node* node){
	Tag* tag=NULL;
	if(node->node_tag==NULL){
		tag=Tag_Retrieve(tag_To_add);
		node->node_tag=tag;
		return node;
	}
	tag=Tag_Retrieve(tag_To_add);
	tag->suivant=node->node_tag;
	node->node_tag=tag;
	return node;
}

Way* Tag_add_Way(xmlNodePtr tag_To_add,Way* way){
	Tag* tag=NULL;
	if(way->way_tag==NULL){
		tag=Tag_Retrieve(tag_To_add);
		way->way_tag=tag;
		return way;
	}
	tag=Tag_Retrieve(tag_To_add);
	tag->suivant=way->way_tag;
	way->way_tag=tag;
	return way;

}

Nd* Nd_Retrieve(xmlNodePtr xml_nd){
	static int nb_nd=0;
	Nd* nd=NULL;
	nd=malloc(sizeof(Nd));
	nd->ref=(char *)xmlGetProp(xml_nd,(const xmlChar *)"ref");
	nd->next_nd=NULL;
	nb_nd++;
	printf("nd %d\n",nb_nd );
	return nd;
}

Way* Nd_add_Way(xmlNodePtr nd_To_add,Way* way){
	Nd* nd=NULL;
	if(way->ref==NULL){
		nd=Nd_Retrieve(nd_To_add);
		way->ref=nd;
		return way;
	}
	nd=Nd_Retrieve(nd_To_add);
	nd->next_nd=way->ref;
	way->ref=nd;
	return way;
}
//methode pour recuperer les valeurs des attributs d'un noeud

Node* Node_Retrieve(xmlNodePtr xml_node){
	Node* node;
	node=malloc(sizeof(Node));
	node->id=(char *)xmlGetProp(xml_node,(const xmlChar *)"id");
	node->visible=(char *)xmlGetProp(xml_node,(const xmlChar *)"visible");
	node->lon=(char *)xmlGetProp(xml_node,(const xmlChar *)"lon");
	node->lat=(char *)xmlGetProp(xml_node,(const xmlChar *)"lat");
	node->node_tag=NULL;
	node->suivant=NULL;
	node->precedent=NULL;
	if(xml_node->children!=NULL){
		
		xml_node=xml_node->xmlChildrenNode;
		while(xml_node->next!=NULL){
			if((!xmlStrcmp(xml_node->name,(const xmlChar*)"tag"))){
				node=Tag_add_Node(xml_node,node);	
			}
			xml_node=xml_node->next;
		}
	}
	return node;
}



//pour ajouter les noeuds dans la liste (Array_node)
Array_All* Node_add(xmlNodePtr node_To_add,Array_All* all){
	Node* node=NULL;
	if(all->Array_Node==NULL){
		node=Node_Retrieve(node_To_add);
		all->Array_Node=node;
		return all;
	}
	node=Node_Retrieve(node_To_add);
	node->suivant=all->Array_Node->suivant;
	node->precedent=all->Array_Node;
	all->Array_Node->suivant=node;
	all->Array_Node->suivant->precedent=node;
	return all;
}

//methode pour recuperer les valeurs des chemins
Way* Way_Retrieve(xmlNodePtr xml_way){
	Way* way=NULL;
	way=malloc(sizeof(Way));
	way->id=(char *)xmlGetProp(xml_way,(const xmlChar *)"id");
	way->visible=(char *)xmlGetProp(xml_way,(const xmlChar *)"visible");
	way->next_way=NULL;
	way->ref=NULL;
	way->way_tag=NULL;
	if(xml_way->children!=NULL){
		xml_way=xml_way->xmlChildrenNode;
		while(xml_way->next!=NULL){
			if((!xmlStrcmp(xml_way->name,(const xmlChar*)"tag"))){
				way=Tag_add_Way(xml_way,way);
			}
			if((!xmlStrcmp(xml_way->name,(const xmlChar*)"nd"))){
				way=Nd_add_Way(xml_way,way);
			}
			xml_way=xml_way->next;
		}
	}
	return way;
}

Array_All* Way_add(xmlNodePtr way_To_add,Array_All* all){
	Way* way=NULL;
	if(all->Array_Way==NULL){
		way=Way_Retrieve(way_To_add);
		all->Array_Way=way;
		return all;
	}
	way=Way_Retrieve(way_To_add);
	way->next_way=all->Array_Way->next_way;
	all->Array_Way->next_way=way;
	return all;
}

//methode pour parcourir le fichier xml et stocker les valeurs recupere
void Tree_Retrieve(xmlNodePtr nodePtr,Array_All* tab){
	static int nombre_node=0;
	static int nombre_way=0;
	printf("Tree : %s\n",nodePtr->name);
	nodePtr=nodePtr->xmlChildrenNode;
	nodePtr=nodePtr->next;
	while(nodePtr!=NULL){
		if((!xmlStrcmp(nodePtr->name,(const xmlChar *)"bounds"))){
			tab->Array_Bounds=Bounds_Retrieve(nodePtr);

		}
		if((!xmlStrcmp(nodePtr->name,(const xmlChar *)"node"))){
			tab=Node_add(nodePtr,tab);
			nombre_node++;
		}
		if((!xmlStrcmp(nodePtr->name,(const xmlChar *)"way"))){
			tab=Way_add(nodePtr,tab);
			nombre_way++;

		}
		nodePtr=nodePtr->next;
		
		
	}
	printf("nombre de node dans tree : %d\n",nombre_node );
	printf("nombre de way dans tree : %d\n",nombre_way );
	return;
}