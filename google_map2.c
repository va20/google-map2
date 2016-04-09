#include "google_map2.h"
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "SDL2/SDL2_gfxPrimitives.h"
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

	//variables pour stocker les (lat_max,lon_max,lat_min,lon_min)
	double lat_mx,lat_m,lon_mx,lon_m;
    lat_mx=lat_m=lon_mx=lon_m=0;
	
	xmlDocPtr xmlFile=NULL;
	xmlNodePtr xml_nodePtr=NULL;
	xmlFile=Document_Parser(argv[1]);
	xml_nodePtr=Root_Retrieve(xmlFile);
	Tree_Retrieve(xml_nodePtr,&all);



	SDL_Window* fenetre=Create_Window(all.Array_Bounds->maxlat,all.Array_Bounds->minlat,
		all.Array_Bounds->maxlon,all.Array_Bounds->minlon);

    lat_mx=strtod(all.Array_Bounds->maxlat,NULL);
    lat_m=strtod(all.Array_Bounds->minlat,NULL);
    lon_mx=strtod(all.Array_Bounds->maxlon,NULL);
    lon_m=strtod(all.Array_Bounds->minlon,NULL);
    double x,y;
    x=y=0;
    int height=0;
    double x_lat_max = (lon_mx - lon_m) * cos (lat_mx * 3.14 / 180);

    double x_lat_min = (lon_mx - lon_m) * cos (lat_m  * 3.14 / 180);
    x = (x_lat_max > x_lat_min) ? x_lat_max : x_lat_min;
    y = lat_mx - lat_m;
    if(x>y){
        //width=1200;
        height=(y*1200)/x;
    }
    else{
        height=1200;
        //width=(x*1200)/y;

    }
    //double k=(800*360)/((lat_mx-lat_m);
    double k2=(height*360)/y;
	SDL_Renderer* map=SDL_GetRenderer(fenetre);
    SDL_SetRenderDrawColor(map, 200, 200, 200, 255);
    SDL_RenderClear(map);
    SDL_RenderPresent(map);
    //draw_points(all.Array_Node,map);
    //Boucle qui tiens la fenêtre ouverte.
    SDL_Event event;
    int repeat = 0;
    int building=0;
    int highway=0;
    int natural=0;
    while(!repeat){
        while(all.Array_Way != NULL){
        	double x_cour,y_cour;
        	
        	//initialisation pour le premier point
        	
        	Nd* tmp=all.Array_Way->ref;
        	//printf("avant if \n");
        	//printf("%s\n",all.Array_Way->way_tag->key);
        	int i=0;
        	Sint16 *tabPoly_X=NULL;
        	Sint16 *tabPoly_Y=NULL;
        	tabPoly_X=malloc((all.Array_Way->nb_ref)*sizeof(Sint16));
        	tabPoly_Y=malloc((all.Array_Way->nb_ref)*sizeof(Sint16));
        	if(isBuilding(all.Array_Way->way_tag,"building")){
        		building=1;	
        	}
        	if(isBuilding(all.Array_Way->way_tag,"highway")){
        		highway=1;
        	}
        	if(isBuilding(all.Array_Way->way_tag,"natural")){
        		natural=1;
        	}
        	
        	while(tmp!=NULL){
        		x_cour=strtod(tmp->value_ref->lon,NULL);
        		y_cour=strtod(tmp->value_ref->lat,NULL);
        		x_cour=((x_cour-lon_m)*k2*cos(y_cour*(3.14/180)))/360;
    			y_cour=((y_cour-lat_m)*k2)/360;
        		tabPoly_X[i]=(Sint16) x_cour;
        		tabPoly_Y[i]=(Sint16) (height - y_cour);
        		i++;
        		tmp=tmp->next_nd;
        	}
       		if(highway){
       			int tmp = i-1;

       			while(tmp>0){
       				char *value=NULL;
       				value=valueOf(all.Array_Way->way_tag,"highway");

       					if(strcmp(value,"motorway")==0){
       						thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       							tabPoly_Y[tmp-1],20,255,102,102);
       					}
       					else if(strcmp(value,"trunk")==0){
       						thickLineColor(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       							tabPoly_Y[tmp-1],20,255,153,51);
       					}
       					else if(strcmp(value,"primary")==0){
       						thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       							tabPoly_Y[tmp-1],20,255,178,102,255);
       					}
       					else if(strcmp(value,"secondary")==0){
       						thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       							tabPoly_Y[tmp-1],20,229,255,204,255);
       					}
       					else if(strcmp(value,"tertiary")==0){
       						thickLineColor(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       							tabPoly_Y[tmp-1],20,0xFFFFFFFF);
       					}
       					else if(strcmp(value,"unclassified")==0){
       						thickLineColor(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       							tabPoly_Y[tmp-1],10,0xFFFFFFFF);
       					}
       					else if(strcmp(value,"residential")==0){
       						thickLineColor(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       							tabPoly_Y[tmp-1],10,0xFFFFFFFF);
       					}
       					else if(strcmp(value,"service")==0){
       						thickLineColor(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       							tabPoly_Y[tmp-1],5,0xFFFFFFFF);
       					}
       					else if(strcmp(value,"pedestrian")==0){
       						thickLineColor(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       							tabPoly_Y[tmp-1],5,0xFFFFFFFF);
       					}
       					else{
       						thickLineColor(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       							tabPoly_Y[tmp-1],5,0xFFFFFFFF);	
       					}
       					tmp--;
       						
       				}
       				
       				
       				//printf("je suis la\n");
       			
       			highway=0;
       		}
       		if(building){
       			filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i, 192,192,192,255);
       			building = 0;
       			polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
       		}


       		
       		free(tabPoly_X);
       		free(tabPoly_Y);
       		i = 0;
        	all.Array_Way = all.Array_Way->next_way;
        }
        SDL_RenderPresent(map);
        SDL_PollEvent(&event);
        switch(event.type){
        case SDL_QUIT:
            repeat=1;
            break;
        }
    }
    SDL_DestroyWindow(fenetre);
	return 0;
}