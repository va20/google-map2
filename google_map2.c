#include "google_map2.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
/*
unite.h def de types+prototypes utiliser par d'autre unité
unite.c implementation


 */

int main(int argc,char *argv[]){

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



	SDL_Window* fenetre=Create_Window(all.Array_Bounds->maxlat,all.Array_Bounds->minlat,
		all.Array_Bounds->maxlon,all.Array_Bounds->minlon);

	double lat_mx,lat_m,lon_mx,lon_m;
    lat_mx=lat_m=lon_mx=lon_m=0;
    lat_mx=strtod(all.Array_Bounds->maxlat,NULL);
    lat_m=strtod(all.Array_Bounds->minlat,NULL);
    lon_mx=strtod(all.Array_Bounds->maxlon,NULL);
    lon_m=strtod(all.Array_Bounds->minlon,NULL);
    double x,y;
    x=y=0;
    x=lon_mx-lon_m;
    y=lat_mx-lat_m;
    int height;

    if(x>y){
        height=(y*1200)/x;
    }
    else{
        height=1200;

    }
    //double k=(800*360)/((lat_mx-lat_m);
    double k2=(height*360)/((lon_mx-lon_m)*cos(lat_mx));
	SDL_Renderer* map=SDL_GetRenderer(fenetre);
    SDL_SetRenderDrawColor(map, 200, 200, 200, 255);
    SDL_RenderClear(map);
    SDL_RenderPresent(map);
    //draw_points(all.Array_Node,map);
    //Boucle qui tiens la fenêtre ouverte.
    SDL_Event event;
    int repeat = 0;
    while(!repeat){
        /*while(all.Array_Node!=NULL){
        	SDL_SetRenderDrawColor(map,30,30,30,255);
        	double lon_x=strtod(all.Array_Node->lon,NULL);
    		double lat_y=strtod(all.Array_Node->lat,NULL);
    		int x,y;
    		x=y=0;
    		x=((lon_x-lon_m)*k2)/360;
    		y=((lat_y-lat_m)*k2*cos(lat_y))/360;
    		printf("lon %d\n",x);
    		printf("lat %d\n",y);

        	SDL_RenderDrawPoint(map,(int)x,(int)y);
        	SDL_RenderPresent(map);
        	all.Array_Node=all.Array_Node->suivant;
        }*/
        while(all.Array_Way!=NULL){
        	double x_pred,y_pred,x_cour,y_cour;
        	x_pred=y_pred=x_cour=y_cour=100000;
        	Nd* tmp=all.Array_Way->ref;
        	while(tmp!=NULL){
        		x_cour=strtod(tmp->value_ref->lon,NULL);
        		y_cour=strtod(tmp->value_ref->lat,NULL);
        		x_cour=((x_cour-lon_m)*k2*cos(y_cour))/360;
    			y_cour=((y_cour-lat_m)*k2)/360;
        		if(x_pred==100000){
        			x_pred=x_cour;
        			y_pred=y_cour;
        		}
        		else{
        			SDL_SetRenderDrawColor(map,0,0,0,255);
        			SDL_RenderDrawLine(map,(int)y_pred,(int)x_pred,(int)y_cour,(int)x_cour);
        			SDL_RenderPresent(map);
        			x_pred=x_cour;
        			y_pred=y_cour;
        		}
        		tmp=tmp->next_nd;
        	}
        	all.Array_Way=all.Array_Way->next_way;
        }
        SDL_PollEvent(&event);
        switch(event.type){
        case SDL_QUIT:
            repeat=1;
            break;
        }
    }
    SDL_DestroyWindow(fenetre);
	
	//AVL_node* tree_node=NULL;
	//AVL_way* tree_way=NULL;


	//int cmpNode=0;
	//int cmpTag=0;
	int cmpTag_way=0;
	int cmp_way=0;
	int cmpNd=0;
	//int cmp_Relation=0;
	//int cmp_member=0;
	//int cmp_member_tag=0;	
	/*tree_node=insertion_node(tree_node,all.Array_Node);
	printf("affichage main\n");
	printf("%s\n",tree_node->id );
	printf("%p\n",tree_node->left);
	all.Array_Node=all.Array_Node->suivant;
	tree_node=insertion_node(tree_node,all.Array_Node);
	all.Array_Node=all.Array_Node->suivant;
	tree_node=insertion_node(tree_node,all.Array_Node);
	printf("affichage main\n");
	affiche(tree_node);
	all.Array_Node=all.Array_Node->suivant;
	tree_node=insertion_node(tree_node,all.Array_Node);
	printf("affichage main\n");
	affiche(tree_node);
	all.Array_Node=all.Array_Node->suivant;
	tree_node=insertion_node(tree_node,all.Array_Node);
	printf("affichage main\n");
	affiche(tree_node);
	all.Array_Node=all.Array_Node->suivant;
	tree_node=insertion_node(tree_node,all.Array_Node);
	printf("affichage main\n");
	affiche(tree_node);
	all.Array_Node=all.Array_Node->suivant;
	tree_node=insertion_node(tree_node,all.Array_Node);
	printf("affichage main\n");
	affiche(tree_node);
	all.Array_Node=all.Array_Node->suivant;
	tree_node=insertion_node(tree_node,all.Array_Node);
	printf("affichage main\n");
	affiche(tree_node);
	all.Array_Node=all.Array_Node->suivant;
	tree_node=insertion_node(tree_node,all.Array_Node);
	printf("affichage main\n");
	affiche(tree_node);
	all.Array_Node=all.Array_Node->suivant;
	tree_node=insertion_node(tree_node,all.Array_Node);
	printf("affichage main\n");
	affiche(tree_node);
	all.Array_Node=all.Array_Node->suivant;
	tree_node=insertion_node(tree_node,all.Array_Node);
	printf("affichage main\n");
	affiche(tree_node);
	all.Array_Node=all.Array_Node->suivant;
	tree_node=insertion_node(tree_node,all.Array_Node);
	printf("affichage main\n");
	affiche(tree_node);
	all.Array_Node=all.Array_Node->suivant;
	tree_node=insertion_node(tree_node,all.Array_Node);
	printf("affichage main\n");
	affiche(tree_node);
	all.Array_Node=all.Array_Node->suivant;
	tree_node=insertion_node(tree_node,all.Array_Node);
	printf("affichage main\n");
	affiche(tree_node);
	all.Array_Node=all.Array_Node->suivant;
	tree_node=insertion_node(tree_node,all.Array_Node);
	printf("affichage main\n");
	affiche(tree_node);
	all.Array_Node=all.Array_Node->suivant;
	tree_node=insertion_node(tree_node,all.Array_Node);
	printf("affichage main\n");
	affiche(tree_node);*/
	
	//while(all.Array_Node!=NULL){
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
		
		//tree_node=insertion_node(tree_node,all.Array_Node);
		//all.Array_Node=all.Array_Node->suivant;
	//}
	while(all.Array_Way!=NULL){
		if(all.Array_Way->way_tag!=NULL){
			Tag* tmp=NULL;
			tmp=all.Array_Way->way_tag;
			Nd* tmp2=NULL;
			tmp2=all.Array_Way->ref;
			while(tmp!=NULL){
				cmpTag_way++;
				tmp=tmp->suivant;
			}
			while(tmp2!=NULL){
				//printf("node ref %s\n",tmp2->value_ref->id);
				cmpNd++;
				tmp2=tmp2->next_nd;
			}
		}
		cmp_way++;
		//tree_way=insertion_way(tree_way,all.Array_Way);
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