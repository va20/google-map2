#include "parser.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
/*
unite.h def de types+prototypes utiliser par d'autre unité
unite.c implementation


 */

int main(int argc,char *argv[]){
	int cmpNode,cmpTag;
	cmpNode=0;cmpTag=0;
	if(argc >2){
		fprintf(stderr, "erreur nombre d'arguments\n");
		return -1;
	}
	/*if(argv[1]!="map.osm"){
		fprintf(stderr, "erreur format \n");
		return -2;
	}*/

	Array_All all;
	all.Array_Bounds=NULL;
	all.Array_Node=NULL;
	all.Array_Way=NULL;
	xmlDocPtr xmlFile=NULL;
	xmlNodePtr xml_nodePtr=NULL;
	xmlFile=Document_Parser(argv[1]);
	xml_nodePtr=Root_Retrieve(xmlFile);
	Tree_Retrieve(xml_nodePtr,&all);
	printf("avant while in main\n");
	if(all.Array_Bounds!=NULL){
		//printf("%d\n",sizeof(all));	
		printf("on est dans le main (bounds)\n");
		printf("%s\n",all.Array_Bounds->minlat);
		printf("%s\n",all.Array_Bounds->minlon);
		printf("%s\n",all.Array_Bounds->maxlat);
		printf("%s\n",all.Array_Bounds->minlon);
		
	}
	while(all.Array_Node!=NULL){
		if(all.Array_Node->node_child!=NULL){
			Tag* tmp=NULL;
			tmp=all.Array_Node->node_child;
			while(tmp!=NULL){
				cmpTag++;
				tmp=tmp->suivant;
			}
		}
		/*printf("on est dans le main (Node)\n");
		printf("%s\n",all.Array_Node->id);
		printf("%s\n",all.Array_Node->visible);
		printf("%s\n",all.Array_Node->lon);
		printf("%s\n",all.Array_Node->lat);*/
		cmpNode++;
		all.Array_Node=all.Array_Node->suivant;
	}
	printf("nombre de nodes %d\n",cmpNode );
	printf("nombre de tag %d\n",cmpTag);
	printf("c bon \n");
	return 0;
}