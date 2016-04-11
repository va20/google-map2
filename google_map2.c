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
    all.size_list_node=0;
    all.size_list_way=0;
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



	

    lat_mx=strtod(all.Array_Bounds->maxlat,NULL);
    lat_m=strtod(all.Array_Bounds->minlat,NULL);
    lon_mx=strtod(all.Array_Bounds->maxlon,NULL);
    lon_m=strtod(all.Array_Bounds->minlon,NULL);
    double x,y;
    x=y=0;
    int height=0;
    int width=0;
    double x_lat_max = (lon_mx - lon_m) * cos (lat_mx * 3.14 / 180);

    double x_lat_min = (lon_mx - lon_m) * cos (lat_m  * 3.14 / 180);
    x = (x_lat_max > x_lat_min) ? x_lat_max : x_lat_min;
    y = lat_mx - lat_m;
    if(x>y){
        width=1200;
        height=(y*1200)/x;
    }
    else{
        height=1200;
        width=(x*1200)/y;

    }
    SDL_Window* fenetre=Create_Window(height,width);
    //double k=(800*360)/((lat_mx-lat_m);
    
    double k2=(height*360)/y;
	SDL_Renderer* map=SDL_GetRenderer(fenetre);
    SDL_SetRenderDrawColor(map, 200, 200, 200, 255);
    SDL_RenderClear(map);

    SDL_Texture *autoroutes = SDL_CreateTexture (map,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,width,height);
    SDL_SetTextureBlendMode(autoroutes,SDL_BLENDMODE_BLEND);
    SDL_Texture *primaires = SDL_CreateTexture (map,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,width,height);
    SDL_SetTextureBlendMode(primaires,SDL_BLENDMODE_BLEND);
    SDL_Texture *secondaires = SDL_CreateTexture (map,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,width,height);
    SDL_SetTextureBlendMode(secondaires,SDL_BLENDMODE_BLEND);
    SDL_Texture *tertiaires = SDL_CreateTexture (map,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,width,height);
    SDL_SetTextureBlendMode(tertiaires,SDL_BLENDMODE_BLEND);
    SDL_Texture *restes = SDL_CreateTexture (map,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,width,height);
    SDL_SetTextureBlendMode(restes,SDL_BLENDMODE_BLEND);

    SDL_Texture *internes = SDL_CreateTexture (map,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,width,height);
    SDL_SetTextureBlendMode(internes,SDL_BLENDMODE_BLEND);
    SDL_Texture *buildings = SDL_CreateTexture (map,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,width,height);
    SDL_SetTextureBlendMode(buildings,SDL_BLENDMODE_BLEND);
    SDL_Texture *water = SDL_CreateTexture (map,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,width,height);
    SDL_SetTextureBlendMode(water,SDL_BLENDMODE_BLEND);
    SDL_Texture *others = SDL_CreateTexture (map,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,width,height);
    SDL_SetTextureBlendMode(others,SDL_BLENDMODE_BLEND);
    SDL_Texture *background = SDL_CreateTexture(map,SDL_PIXELFORMAT_RGBA8888,SDL_TEXTUREACCESS_TARGET,width,height);
    SDL_SetTextureBlendMode(background,SDL_BLENDMODE_NONE);
    SDL_SetRenderTarget(map,background);
    SDL_SetRenderDrawColor(map,200,200,200,255);
    SDL_RenderClear(map);
    SDL_SetRenderTarget(map,NULL);
    //draw_points(all.Array_Node,map);
    //Boucle qui tiens la fenêtre ouverte.
    SDL_Event event;
    int repeat = 0;
    int building=0;
    int highway=0;
    int waterway=0;
    int natural=0;
    int landuse=0;
    int leisure=0;
    int railway=0;
    while(!repeat){
        /*if(all.Array_Way!=NULL){
            map=draw_ways(map,all.Array_Way,lon_m,lat_m,k2,height);
        }*/
        while(all.Array_Way != NULL){
        	double x_cour,y_cour;

        	//initialisation pour le premier point
        	
        	Nd* tmp=all.Array_Way->ref;
        
        	int i=0;
        	Sint16 *tabPoly_X=NULL;
        	Sint16 *tabPoly_Y=NULL;
        	tabPoly_X=malloc((all.Array_Way->nb_ref)*sizeof(Sint16));
        	tabPoly_Y=malloc((all.Array_Way->nb_ref)*sizeof(Sint16));
        	if(isBuilding(all.Array_Way->way_tag,"building")){
        		building=1;	
        	}
            if(isBuilding(all.Array_Way->way_tag,"railway")){
                railway=1; 
            }
        	if(isBuilding(all.Array_Way->way_tag,"highway")){
        		highway=1;
        	}
        	if(isBuilding(all.Array_Way->way_tag,"waterway")){
        		waterway=1;
        	}
        	if(isBuilding(all.Array_Way->way_tag,"natural")){
        		natural=1;
        	}
            if(isBuilding(all.Array_Way->way_tag,"landuse")){
                landuse=1;
            } 
            if(isBuilding(all.Array_Way->way_tag,"leisure")){
                leisure=1;
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
        	if(natural){
        		int tmp = i-1;
                SDL_SetRenderTarget(map,water);
        		char* value=NULL;
        		value=valueOf(all.Array_Way->way_tag,"natural");
        		if(strcmp(value,"water")==0){
        			filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i, 102,178,255,255);
       				polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
       				//thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       					//tabPoly_Y[tmp-1],30,153,204,255,255);       				
        		}
				else if(strcmp(value,"canal")==0){
        			thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       					tabPoly_Y[tmp-1],30,153,204,255,255);
        		}
        		else if(strcmp(value,"stream")){
        			//thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       					//tabPoly_Y[tmp-1],1,102,178,255,255);
                    filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i, 102,178,255,255);
                    polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
        		}
                else if(strcmp(value,"coastline")==0){

                    filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i, 102,178,255,255);
                    polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);              
                }
        		natural=0;
        	}
       		
        	if(waterway){
        		int tmp = i-1;
                SDL_SetRenderTarget(map,water);
        		char* value=NULL;
        		value=valueOf(all.Array_Way->way_tag,"waterway");
        		if(strcmp(value,"river")==0){
        			thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       				tabPoly_Y[tmp-1],20,153,204,255,255);
        		}
				else if(strcmp(value,"canal")==0){
        			thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       				tabPoly_Y[tmp-1],30,153,204,255,255);
        			//filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i, 102,178,255,255);
        		}
        		else if(strcmp(value,"stream")){
        			//thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       					//tabPoly_Y[tmp-1],5,153,204,255,255);
        			filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i, 102,178,255,255);
                     //polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
        		}
                else if(strcmp(value,"riverbank")==0){
                    //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                    //tabPoly_Y[tmp-1],20,153,204,255,255);
                    filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i, 102,178,255,255);
                    polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);

                }
        		waterway=0;
        	}
            if(leisure){
              //int tmp=i-1;
                SDL_SetRenderTarget(map,others);
                char* value=NULL;
                value=valueOf(all.Array_Way->way_tag,"leisure");
                if(strcmp(value,"park")==0){
                    //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                    //tabPoly_Y[tmp-1],20,102,255,102,255);
                    filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i,102,255,102,255);
                    polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                }
                else if(strcmp(value,"garden")==0){
                    //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                    //tabPoly_Y[tmp-1],20,102,255,102,255);
                    filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i,0,102,0,255);
                    polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                }
                else if(strcmp(value,"playground")==0){
                    //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                    //tabPoly_Y[tmp-1],20,102,255,102,255);
                    filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i,80,255,80,255);
                    polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                }
                else if(strcmp(value,"bandstand")==0){
                    //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                    //tabPoly_Y[tmp-1],20,102,255,102,255);
                    filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i,80,255,80,255);
                    polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                }
                else if(strcmp(value,"pitch")==0){
                    //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                    //tabPoly_Y[tmp-1],20,102,255,102,255);
                    filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i,80,255,80,255);
                    polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                }
            leisure = 0;
          }
        	if(landuse){
        		//int tmp=i-1;
                SDL_SetRenderTarget(map,others);
        		char* value=NULL;
        		value=valueOf(all.Array_Way->way_tag,"landuse");
        		if(strcmp(value,"grass")==0){
        			//thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       					//tabPoly_Y[tmp-1],20,102,255,102,255);
                    filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i,102,255,102,255);
                    polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
        		}
                else if(strcmp(value,"forest")==0){
                    //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                    //tabPoly_Y[tmp-1],20,102,255,102,255);
                    filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i, 102,255,102,255);
                    polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                }
                else if(strcmp(value,"basin")==0){
                    //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                    //tabPoly_Y[tmp-1],20,102,255,102,255);
                    filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i, 102,255,102,255);
                    polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                }
                else if(strcmp(value,"village_green")==0){
                    //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                    //tabPoly_Y[tmp-1],20,102,255,102,255);
                    filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i, 102,255,102,255);
                    polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                }
                else if(strcmp(value,"railway")==0){
                    //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                    //tabPoly_Y[tmp-1],20,255,204,204,255);
                    filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i, 255,204,204,255);
                    polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                }
                landuse=0;
        	}
       		if(highway){
       			int tmp = i-1;
       			while(tmp>0){
       				char *value=NULL;
       				value=valueOf(all.Array_Way->way_tag,"highway");

       				if(strcmp(value,"motorway")==0){
                        SDL_SetRenderTarget(map,autoroutes);
       					thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       					tabPoly_Y[tmp-1],20,255,102,102,255);
       				}
       				else if(strcmp(value,"trunk")==0){
                        SDL_SetRenderTarget(map,autoroutes);
       					thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       					tabPoly_Y[tmp-1],20,255,153,51,255);
       				}
       				else if(strcmp(value,"primary")==0){
                        SDL_SetRenderTarget(map,primaires);
       					thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       					tabPoly_Y[tmp-1],10,255,178,102,255);
       				}
    				else if(strcmp(value,"secondary")==0){
                        SDL_SetRenderTarget(map,secondaires);
       					thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       					tabPoly_Y[tmp-1],10,204,102,0,255);
    				}
       				else if(strcmp(value,"tertiary")==0){
                        SDL_SetRenderTarget(map,tertiaires);
       					thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       					tabPoly_Y[tmp-1],10,224,224,224,255);
       				}
       				else if(strcmp(value,"unclassified")==0){
                        SDL_SetRenderTarget(map,restes);
       					thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       					tabPoly_Y[tmp-1],5,224,224,224,255);
       				}
       				else if(strcmp(value,"residential")==0){
                        SDL_SetRenderTarget(map,restes);
       					thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       					tabPoly_Y[tmp-1],5,224,224,224,255);
       				}
       				else if(strcmp(value,"service")==0){
                        SDL_SetRenderTarget(map,restes);
       					thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       					tabPoly_Y[tmp-1],3,224,224,224,255);
       				}
       				else if(strcmp(value,"pedestrian")==0){
                        SDL_SetRenderTarget(map,restes);
       					thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       					tabPoly_Y[tmp-1],3,224,224,224,255);

       				}
       				else{
                        SDL_SetRenderTarget(map,restes);
       					thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
       					tabPoly_Y[tmp-1],5,224,224,224,255);
       				}
       				tmp--;
       						
    			}
       			highway=0;
       		}
            if(railway){
                int tmp = i-1;
                SDL_SetRenderTarget(map,others);
                char* value=NULL;
                value=valueOf(all.Array_Way->way_tag,"railway");
                if(strcmp(value,"rail")==0){
                    thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                      tabPoly_Y[tmp-1],10,102,0,0,255);
                    //filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i, 102,0,0,255);
                    //polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                }
                else if(strcmp(value,"tram")==0){
                    thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                        tabPoly_Y[tmp-1],7,102,0,0,255);
                }
                else if(strcmp(value,"disused")==0){
                    thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                        tabPoly_Y[tmp-1],7,102,0,0,255);
                }
                railway = 0;
            }

       		if(building){
                SDL_SetRenderTarget(map,buildings);
       			filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i, 150,150,150,255);
       			building = 0;
       			polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);  
     		}
       		free(tabPoly_X);
       		free(tabPoly_Y);
       		i = 0;
            SDL_SetRenderTarget(map,NULL);
            all.Array_Way = all.Array_Way->next_way;
        }
        




        Sint16 tabPoly_X[2000];
        Sint16 tabPoly_Y[2000];
        while(all.Array_Relation!=NULL){

            if(all.Array_Relation->isMultiPolygon){
                Member* member=NULL;
                Tag* tag=NULL;
                Tag* tagway=NULL;
                Way* way_tmp=NULL;
                Nd* first = NULL;
                Way* next_tmp=NULL;
                
                way_tmp=malloc(sizeof(Way));
                next_tmp=malloc(sizeof(Way));

                member=all.Array_Relation->member_fils;
                tag=all.Array_Relation->tag_fils;
                
                while(member!=NULL){

                    
                    if(member->node_ref!=NULL){
                       
                        double x_cour,y_cour;
                        x_cour=strtod(member->node_ref->lon,NULL);
                        y_cour=strtod(member->node_ref->lat,NULL);
                        x_cour=((x_cour-lon_m)*k2*cos(y_cour*(3.14/180)))/360;
                        y_cour=((y_cour-lat_m)*k2)/360;
                        pixelRGBA(map,(Sint16)x_cour,(Sint16)y_cour,255,255,255,255);
                        
                    }
                    else if(member->way_ref!=NULL){
                        if(first==NULL){
                            first = member->way_ref->first;
                        }

                        int i=0;
                        tagway = member->way_ref->way_tag;

                        double x_cour,y_cour;
                        Nd* tmp=member->way_ref->ref;
                        if(way_tmp==NULL){
                            way_tmp=member->way_ref;
                            
                        }
                        else{
                            next_tmp->next_way=member->way_ref;
                            way_tmp=next_tmp;
                        }



                        if(isBuilding(tag,"building") | isBuilding(tagway,"building")){
                            building=1;
                        }
                        else if(isBuilding(tag,"railway") | isBuilding(tagway,"railway")){
                            railway=1; 
                        }
                        else if(isBuilding(tag,"highway") | isBuilding(tagway,"highway")){
                            highway=1;
                        }
                        else if(isBuilding(tag,"waterway") | isBuilding(tagway,"waterway")){
                            waterway=1;
                        }
                        else if(isBuilding(tag,"natural") | isBuilding(tagway,"natural")){
                            natural=1;
                        }
                        else if(isBuilding(tag,"landuse") | isBuilding(tagway,"landuse")){
                            landuse=1;
                        } 
                        else if(isBuilding(tag,"leisure") | isBuilding(tagway,"leisure")){
                            leisure=1;
                        }
                        else if(isBuilding(tag,"type")){

                        }



                        if(strcmp(member->way_ref->last->ref,first->ref)==0){
                           
                            

                            x_cour=strtod(member->way_ref->ref->value_ref->lon,NULL);
                            y_cour=strtod(member->way_ref->ref->value_ref->lat,NULL);
                            x_cour=((x_cour-lon_m)*k2*cos(y_cour*(3.14/180)))/360;
                            y_cour=((y_cour-lat_m)*k2)/360;
                            
                            first=NULL;

                           
                            
                            //way_tmp=way_tmp->next_way;
                            while(way_tmp!=NULL){
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
                                way_tmp = way_tmp->next_way;
                            }

                            if(strcmp(member->role,"outer")==0){


                                
                                if(landuse){


                                    char* value=NULL;
                                    SDL_SetRenderTarget(map,others);

                                    value=valueOf(all.Array_Relation->tag_fils,"landuse");
                                    if(value!=NULL && strcmp(value,"grass")==0){
                                    //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                                    //tabPoly_Y[tmp-1],20,102,255,102,255);
                                        filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i,102,255,102,255);
                                        polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                                    }
                                    
                                    
                                }
                                else if(leisure){


                                    char* value=NULL;
                                    SDL_SetRenderTarget(map,others);
                                    value=valueOf(all.Array_Relation->tag_fils,"leisure");
                                    if(value!=NULL && strcmp(value,"park")==0){
                                    //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                                    //tabPoly_Y[tmp-1],20,102,255,102,255);
                                        filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i,102,255,102,255);
                                        polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                                    }
                                    else if(value!=NULL && strcmp(value,"garden")==0){
                                        //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                                        //tabPoly_Y[tmp-1],20,102,255,102,255);
                                        filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i,0,102,0,255);
                                        polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                                    }
                                    else if(value!=NULL && strcmp(value,"playground")==0){
                                        //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                                        //tabPoly_Y[tmp-1],20,102,255,102,255);
                                        filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i,80,255,80,255);
                                        polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                                    }
                                    else if(value!=NULL && strcmp(value,"bandstand")==0){
                                        //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                                        //tabPoly_Y[tmp-1],20,102,255,102,255);
                                        filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i,80,255,80,255);
                                        polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                                    }
                                    else if(value!=NULL && strcmp(value,"pitch")==0){
                                        //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                                        //tabPoly_Y[tmp-1],20,102,255,102,255);
                                        filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i,80,255,80,255);
                                        polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                                    }
                                }
                                else if(natural){

                                    int tmp = i-1;
                                    char* value=NULL;
                                    SDL_SetRenderTarget(map,water);

                                    value=valueOf(all.Array_Relation->tag_fils,"natural");
                                    if(value!=NULL && strcmp(value,"water")==0){
                                    //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                                    //tabPoly_Y[tmp-1],20,102,255,102,255);
                                        filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i,102,178,255,255);
                                        polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                                    }
                                    else if(strcmp(value,"canal")==0){
                                        thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                                            tabPoly_Y[tmp-1],30,153,204,255,255);
                                    }
                                    else if(strcmp(value,"stream")){
                                        //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                                            //tabPoly_Y[tmp-1],1,102,178,255,255);
                                        filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i, 102,178,255,255);
                                        polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                                    }
                                    else if(strcmp(value,"coastline")==0){

                                        filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i, 102,178,255,255);
                                        polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);              
                                    }
                                }

                                else if(building){
                                    SDL_SetRenderTarget(map,buildings);
                                    filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i,150,150,150,255);
                                    polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);

                                }


                                else {
                                    SDL_SetRenderTarget(map,internes);
                                    filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i, 150,150,150,255);
                                    polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                                }

                            }
                            else{
                                    //INNERS

                                
                                
                                if(landuse){


                                    char* value=NULL;  
                                    SDL_SetRenderTarget(map,others);
                                    value=valueOf(all.Array_Relation->tag_fils,"landuse");
                                    if(value!=NULL && strcmp(value,"grass")==0){
                                    //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                                    //tabPoly_Y[tmp-1],20,102,255,102,255);
                                        filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i,102,255,102,255);
                                        polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                                
                                }
                            }
                                
                                else if(leisure){


                                    char* value=NULL;
                                    SDL_SetRenderTarget(map,others);
                                    value=valueOf(all.Array_Relation->tag_fils,"leisure");
                                    if(value!=NULL && strcmp(value,"park")==0){
                                    //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                                    //tabPoly_Y[tmp-1],20,102,255,102,255);
                                        filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i,50,255,50,255);
                                        polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                                    }
                                    else if(value!=NULL && strcmp(value,"garden")==0){
                                        //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                                        //tabPoly_Y[tmp-1],20,102,255,102,255);
                                        filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i,0,102,0,255);
                                        polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                                    }
                                    else if(value!=NULL && strcmp(value,"playground")==0){
                                        //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                                        //tabPoly_Y[tmp-1],20,102,255,102,255);
                                        filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i,80,255,80,255);
                                        polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                                    }
                                    else if(value!=NULL && strcmp(value,"bandstand")==0){
                                        //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                                        //tabPoly_Y[tmp-1],20,102,255,102,255);
                                        filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i,80,255,80,255);
                                        polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                                    }
                                    else if(value!=NULL && strcmp(value,"pitch")==0){
                                        //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                                        //tabPoly_Y[tmp-1],20,102,255,102,255);
                                        filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i,80,255,80,255);
                                        polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                                    }
                            }
                                else if(natural){

                                    int tmp = i-1;
                                    char* value=NULL;
                                    SDL_SetRenderTarget(map,water);
                                    value=valueOf(all.Array_Relation->tag_fils,"natural");
                                    if(value!=NULL && strcmp(value,"water")==0){
                                    //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                                    //tabPoly_Y[tmp-1],20,102,255,102,255);
                                        filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i,102,178,255,255);
                                        polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                                    }
                                    else if(strcmp(value,"canal")==0){
                                        thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                                            tabPoly_Y[tmp-1],30,153,204,255,255);
                                    }
                                    else if(strcmp(value,"stream")){
                                        //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                                            //tabPoly_Y[tmp-1],1,102,178,255,255);
                                        filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i, 102,178,255,255);
                                        polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                                    }
                                    else if(strcmp(value,"coastline")==0){

                                        filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i, 102,178,255,255);
                                        polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);              
                                    }
                                }
                                else if(building){
                                    SDL_SetRenderTarget(map,buildings);
                                    filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i,200,200,200,255);
                                    polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);

                                }

                                else{
                                    SDL_SetRenderTarget(map,internes);
                                    filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i,255,0,0,255);
                                    polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
                                }   
                            }   
                        }
                    }
                    way_tmp=NULL;
                    next_tmp=NULL;
                    SDL_SetRenderTarget(map,NULL);
                    member=member->next_member;
                }
            }
            building = 0;
            leisure = 0;
            landuse = 0;
            natural = 0;
            highway = 0;
            all.Array_Relation=all.Array_Relation->next_relation;
        }

        //Ordre d'affichage
        SDL_RenderCopy(map,background,NULL,NULL);
        SDL_RenderCopy(map,others,NULL,NULL);
        SDL_RenderCopy(map,water,NULL,NULL);
        SDL_RenderCopy(map,buildings,NULL,NULL);
        //SDL_RenderCopy(map,internes,NULL,NULL);
        SDL_RenderCopy(map,restes,NULL,NULL);
        SDL_RenderCopy(map,tertiaires,NULL,NULL);
        SDL_RenderCopy(map,secondaires,NULL,NULL);
        SDL_RenderCopy(map,primaires,NULL,NULL);
        SDL_RenderCopy(map,autoroutes,NULL,NULL);

        SDL_RenderPresent(map);
        SDL_PollEvent(&event);
        switch(event.type){
        case SDL_QUIT:
            repeat=1;
            break;
        }
    }
    SDL_DestroyTexture(autoroutes);
    SDL_DestroyTexture(primaires);
    SDL_DestroyTexture(secondaires);
    SDL_DestroyTexture(tertiaires);
    SDL_DestroyTexture(restes);
    SDL_DestroyTexture(buildings);
    SDL_DestroyTexture(water);
    SDL_DestroyTexture(others);
    SDL_DestroyTexture(background);
    SDL_DestroyWindow(fenetre);
	return 0;
}