#include "tree_node_structure.h"
#include "tree_way_structure.h"

static AVL_node* tree_node=NULL;
//static AVL_way* tree_way=NULL;

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
	Tag* tag=NULL;
	tag=malloc(sizeof(Tag));

	tag->key=(char *)xmlGetProp(xml_node,(const xmlChar *)"k");
	tag->value=(char *)xmlGetProp(xml_node,(const xmlChar *)"v");
	tag->suivant=NULL;
	cmpTag++;
	//printf("tag %d\n",cmpTag );
	return tag;
}

Member* Member_Retrieve(xmlNodePtr xml_member){
	static int cmpMem=0;
	Member* member=NULL;
	member=malloc(sizeof(Member));
	member->type=(char*)xmlGetProp(xml_member,(const xmlChar*)"type");
	member->ref=(char*)xmlGetProp(xml_member,(const xmlChar*)"ref");
	member->role=(char*)xmlGetProp(xml_member,(const xmlChar*)"role");
	member->next_member=NULL;
	cmpMem++;
	//printf("member %d\n",cmpMem);
	return member;
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

void get_AVL_TreeNode(Node* node_list){
	while(node_list!=NULL){
		tree_node=insertion_node(tree_node,node_list);
		printf("node insere %s\n",node_list->id );
		node_list=node_list->suivant;
	}
	printf("tree node\n");
	affiche(tree_node);
}


Nd* Nd_Retrieve(xmlNodePtr xml_nd){
	static int nb_nd=0;
	Nd* nd=NULL;
	nd=malloc(sizeof(Nd));
	char* ref_node=(char *)xmlGetProp(xml_nd,(const xmlChar *)"ref");
	nd->ref=ref_node; 
	nd->next_nd=NULL;
	//printf("node trouve %s\n",search_node(tree_node,nd->ref)->id);
	nd->value_ref=search_node(tree_node,nd->ref);
	nb_nd++;
	//printf("nd %d\n",nb_nd );
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

Relation* Member_add_Relation(xmlNodePtr member_To_add,Relation* relation){
	Member* member=NULL;
	if(relation->member_fils==NULL){
		member=Member_Retrieve(member_To_add);
		relation->member_fils=member;
		return relation;
	}
	member=Member_Retrieve(member_To_add);
	member->next_member=relation->member_fils;
	relation->member_fils=member;
	return relation;
}

Relation* Tag_add_Relation(xmlNodePtr tag_To_add,Relation* relation){
	Tag* tag=NULL;
	if(relation->tag_fils==NULL){
		tag=Tag_Retrieve(tag_To_add);
		relation->tag_fils=tag;
		return relation;
	}
	tag=Tag_Retrieve(tag_To_add);
	tag->suivant=relation->tag_fils;
	relation->tag_fils=tag;
	return relation;
}

Relation* Relation_Retrieve(xmlNodePtr xml_relation){
	Relation* relation=NULL;
	relation=malloc(sizeof(Relation));
	relation->id=(char*)xmlGetProp(xml_relation,(const xmlChar*)"id");
	relation->visible=(char*)xmlGetProp(xml_relation,(const xmlChar*)"visible");
	relation->member_fils=NULL;
	relation->tag_fils=NULL;
	relation->next_relation=NULL;
	if(xml_relation->children!=NULL){
		xml_relation=xml_relation->xmlChildrenNode;
		while(xml_relation->next!=NULL){
			if((!xmlStrcmp(xml_relation->name,(const xmlChar*)"tag"))){
				relation=Tag_add_Relation(xml_relation,relation);
			}
			if((!xmlStrcmp(xml_relation->name,(const xmlChar*)"member"))){
				relation=Member_add_Relation(xml_relation,relation);
			}
			xml_relation=xml_relation->next;
		}
	}
	return relation;
}

Array_All* Relation_add(xmlNodePtr relation_to_add,Array_All* all){
	Relation* relation=NULL;
	if(all->Array_Relation==NULL){
		relation=Relation_Retrieve(relation_to_add);
		all->Array_Relation=relation;
		return all;
	}
	relation=Relation_Retrieve(relation_to_add);
	relation->next_relation=all->Array_Relation->next_relation;
	all->Array_Relation->next_relation=relation;
	return all;
}

//methode pour parcourir le fichier xml et stocker les valeurs recupere
void Tree_Retrieve(xmlNodePtr nodePtr,Array_All* tab){
	static int nombre_node=0;
	static int nombre_way=0;
	static int nombre_relation=0;
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
			get_AVL_TreeNode(tab->Array_Node);
			tab=Way_add(nodePtr,tab);
			nombre_way++;

		}
		else if ((!xmlStrcmp(nodePtr->name,(const xmlChar *)"relation")))
		{
			tab=Relation_add(nodePtr,tab);
			nombre_relation++;
		}
		nodePtr=nodePtr->next;
		
		
	}
	printf("nombre de node dans tree : %d\n",nombre_node );
	printf("nombre de way dans tree : %d\n",nombre_way );
	printf("nombre de relation dans tree : %d\n",nombre_relation );
	return;
}