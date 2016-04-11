#include "graphic.h"


SDL_Window* Create_Window(int height,int width){

    SDL_Window* fenetre=NULL;
    SDL_Renderer* map=NULL;
    if(SDL_VideoInit(NULL)<0){
        printf("Erreur initialisation %s\n",SDL_GetError());
        return NULL;
    }
    fenetre=SDL_CreateWindow("Google_Map_2",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
        width,height,SDL_WINDOW_RESIZABLE);
    if(fenetre==NULL){
        printf("Erreur fenetre %s\n",SDL_GetError());
        return NULL;
    }
    //map=SDL_CreateRenderer(fenetre,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    map=SDL_CreateRenderer(fenetre,-1,0);
    if(map==NULL){
        printf("Erreur render %s\n",SDL_GetError());
        return NULL;
    }
    return fenetre;
}

int isBuilding(Tag* tag,char* word){
    int rep=0;
    Tag* tmp=NULL;
    tmp=tag;
    while(tmp!=NULL){
        //printf("%s\n",tmp->key );
        if(strcmp(tmp->key,word)==0){
            rep=1;
            return rep;
        }
        tmp=tmp->suivant;
    }
    return 0;
}

char* valueOf(Tag* tag,char* word){
    
    Tag* tmp=NULL;
    tmp=tag;

    while(tmp!=NULL){
        //printf("%s\n",tmp->key );
        if(strcmp(tmp->key,word)==0){
            
            return tmp->value;
        }
        tmp=tmp->suivant;
    }
    return NULL;
}

SDL_Renderer* draw_ways(SDL_Renderer* map,Way* way,double lon_m,double lat_m,double k2,int height){
    int building=0;
    int highway=0;
    int waterway=0;
    int natural=0;
    int landuse=0;
    int leisure=0;
    int railway=0;

    double x_cour,y_cour;
            //initialisation pour le premier point
            
    Nd* tmp=way->ref;
    int i=0;

    while(way!=NULL){
        Sint16 *tabPoly_X=NULL;
        Sint16 *tabPoly_Y=NULL; 
        tabPoly_X=malloc((way->nb_ref)*sizeof(Sint16));
        tabPoly_Y=malloc((way->nb_ref)*sizeof(Sint16));
        if(isBuilding(way->way_tag,"building")){
            building=1;
        }
        if(isBuilding(way->way_tag,"railway")){
            railway=1; 
        }
        if(isBuilding(way->way_tag,"highway")){
            highway=1;
        }
        if(isBuilding(way->way_tag,"waterway")){
            waterway=1;
        }
        if(isBuilding(way->way_tag,"natural")){
            natural=1;
        }
        if(isBuilding(way->way_tag,"landuse")){
            landuse=1;
        } 
        if(isBuilding(way->way_tag,"leisure")){
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
            char* value=NULL;
            value=valueOf(way->way_tag,"natural");
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
            char* value=NULL;
            value=valueOf(way->way_tag,"waterway");
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
                    /*thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                        tabPoly_Y[tmp-1],5,153,204,255,255);*/
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
            char* value=NULL;
            value=valueOf(way->way_tag,"leisure");
            if(strcmp(value,"park")==0){
                //thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                //tabPoly_Y[tmp-1],20,102,255,102,255);
                filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i,255,255,102,255);
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
            char* value=NULL;
            value=valueOf(way->way_tag,"landuse");
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
                    value=valueOf(way->way_tag,"highway");

                    if(strcmp(value,"motorway")==0){
                        thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                        tabPoly_Y[tmp-1],20,255,102,102,255);
                    }
                    else if(strcmp(value,"trunk")==0){
                        thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                        tabPoly_Y[tmp-1],20,255,153,51,255);
                    }
                    else if(strcmp(value,"primary")==0){
                        thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                        tabPoly_Y[tmp-1],10,255,178,102,255);
                    }
                    else if(strcmp(value,"secondary")==0){
                        thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                        tabPoly_Y[tmp-1],10,204,102,0,255);
                    }
                    else if(strcmp(value,"tertiary")==0){
                        thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                        tabPoly_Y[tmp-1],10,224,224,224,255);
                    }
                    else if(strcmp(value,"unclassified")==0){
                        thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                        tabPoly_Y[tmp-1],5,224,224,224,255);
                    }
                    else if(strcmp(value,"residential")==0){
                        thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                        tabPoly_Y[tmp-1],5,224,224,224,255);
                    }
                    else if(strcmp(value,"service")==0){
                        thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                        tabPoly_Y[tmp-1],3,224,224,224,255);
                    }
                    else if(strcmp(value,"pedestrian")==0){
                        thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                        tabPoly_Y[tmp-1],3,224,224,224,255);

                    }
                    else{
                        thickLineRGBA(map,tabPoly_X[tmp],tabPoly_Y[tmp],tabPoly_X[tmp-1],
                        tabPoly_Y[tmp-1],5,224,224,224,255);
                    }
                    tmp--;
                            
                }
                highway=0;
            }
            if(railway){
                int tmp = i-1;
                char* value=NULL;
                value=valueOf(way->way_tag,"railway");
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
            filledPolygonRGBA(map,tabPoly_X,tabPoly_Y,i, 255,0,0,255);
            building = 0;
            polygonRGBA(map, tabPoly_X, tabPoly_Y, i, 0, 0, 0, 255);
        }
        free(tabPoly_X);
        free(tabPoly_Y);
        i = 0;
        way = way->next_way;
    }
    return map;
}

/*Way* get_Inner(Member *member,Way* way){
        if(way==NULL){
            way=member->way_ref;
        }
        else{
            Way* next_tmp=NULL;
            next_tmp=malloc(sizeof(Way));
            next_tmp->next_way=way;
            way=next_tmp;
        }
        member=member->next_member;
    }
    return way;
}*/


