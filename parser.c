#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
/*
unite.h def de types+prototypes utiliser par d'autre unité
unite.c implementation


 */

int main(int argc,char *argv[]){
	
	AVL_node* tree=NULL;
	


	/*int cmpNode,cmpTag;
	cmpNode=0;cmpTag=0;
	int cmpTag_way=0;
	int cmp_way=0;
	int cmpNd=0;
	int cmp_Relation=0;
	int cmp_member=0;
	int cmp_member_tag=0;*/
	if(argc >2){
		fprintf(stderr, "erreur nombre d'arguments\n");
		return -1;
	}

	Array_All all;
	all.Array_Bounds=NULL;
	all.Array_Node=NULL;
	all.Array_Way=NULL;
	all.Array_Relation=NULL;

	
	xmlDocPtr xmlFile=NULL;
	xmlNodePtr xml_nodePtr=NULL;
	xmlFile=Document_Parser(argv[1]);
	xml_nodePtr=Root_Retrieve(xmlFile);
	Tree_Retrieve(xml_nodePtr,&all);
	
	/*tree=insertion_node(tree,all.Array_Node);
	printf("affichage main\n");
	printf("%s\n",tree->id );
	printf("%p\n",tree->left);
	all.Array_Node=all.Array_Node->suivant;
	tree=insertion_node(tree,all.Array_Node);
	all.Array_Node=all.Array_Node->suivant;
	tree=insertion_node(tree,all.Array_Node);
	printf("affichage main\n");
	affiche(tree);
	all.Array_Node=all.Array_Node->suivant;
	tree=insertion_node(tree,all.Array_Node);
	printf("affichage main\n");
	affiche(tree);
	all.Array_Node=all.Array_Node->suivant;
	tree=insertion_node(tree,all.Array_Node);
	printf("affichage main\n");
	affiche(tree);
	all.Array_Node=all.Array_Node->suivant;
	tree=insertion_node(tree,all.Array_Node);
	printf("affichage main\n");
	affiche(tree);
	all.Array_Node=all.Array_Node->suivant;
	tree=insertion_node(tree,all.Array_Node);
	printf("affichage main\n");
	affiche(tree);*/

	while(all.Array_Node!=NULL){
		/*if(all.Array_Node->node_tag!=NULL){
			Tag* tmp=NULL;
			tmp=all.Array_Node->node_tag;
			while(tmp!=NULL){
				cmpTag++;
				//printf("tag name : %s\n",tmp->key );
				//printf("tag val : %s\n",tmp->value );
				tmp=tmp->suivant;
			}
		}
		cmpNode++;*/
		
		tree=insertion_node(tree,all.Array_Node);
		all.Array_Node=all.Array_Node->suivant;
	}
	while(all.Array_Way!=NULL){
		/*if(all.Array_Way->way_tag!=NULL){
			Tag* tmp=NULL;
			tmp=all.Array_Way->way_tag;
			Nd* tmp2=NULL;
			tmp2=all.Array_Way->ref;
			while(tmp!=NULL){
				cmpTag_way++;
				tmp=tmp->suivant;
			}
			while(tmp2!=NULL){
				cmpNd++;
				tmp2=tmp2->next_nd;
			}
		}
		cmp_way++;*/
		all.Array_Way=all.Array_Way->next_way;
	}
	/*while(all.Array_Relation!=NULL){
		if (all.Array_Relation->member_fils!=NULL){
			Member* tmp=NULL;
			Tag* tmp2=NULL;
			tmp=all.Array_Relation->member_fils;
			tmp2=all.Array_Relation->tag_fils;
			while(tmp!=NULL){
				cmp_member++;
				tmp=tmp->next_member;
			}
			while(tmp2!=NULL){
				cmp_member_tag++;
				tmp2=tmp2->suivant;
			}
			cmp_Relation++;
			all.Array_Relation=all.Array_Relation->next_relation;

		}
	}*/
	/*printf("%d\n",height_node(&node) );
	printf("nombre de way %d\n",cmp_way );
	printf("nombre de tag_way %d\n",cmpTag_way);
	printf("nombre de nd dans way %d\n",cmpNd);
	printf("nombre de nodes %d\n",cmpNode );
	printf("nombre de tag %d\n",cmpTag);
	printf("nombre de relation %d\n",cmp_Relation);
	printf("nombre de member %d\n",cmp_member);
	printf("nombre de tag dans relation %d\n",cmp_member_tag );
	printf("c bon \n");*/
	return 0;
}