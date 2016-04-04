#include "graphic.h"


SDL_Window* Create_Window(char* lat_max,char* lat_min,char* lon_max,char* lon_min){
    double lat_mx,lat_m,lon_mx,lon_m;
    lat_mx=lat_m=lon_mx=lon_m=0;
    lat_mx=strtod(lat_max,NULL);
    lat_m=strtod(lat_min,NULL);
    lon_mx=strtod(lon_max,NULL);
    lon_m=strtod(lon_min,NULL);
    double x,y;
    int height,width;

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
/*
    x=lon_mx-lon_m;
    y=lat_mx-lat_m;
    if(x>y){
        width=1200;
        height=(y*1200)/x;
    }
    else{
        height=1200;
        width=(x*1200)/y;

    }
*/
    /*printf("lat max %f\n",lat_mx );
    printf("lat m %f\n",lat_m );
    printf("lon max %f\n",lon_mx );
    printf("lon m %f\n",lon_m );*/

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
    map=SDL_CreateRenderer(fenetre,-1,SDL_RENDERER_ACCELERATED|SDL_RENDERER_PRESENTVSYNC);
    if(map==NULL){
        printf("Erreur render %s\n",SDL_GetError());
        return NULL;
    }
    return fenetre;
}
void draw_points(Node* list_node,SDL_Renderer* map){
    int lat_y,lon_x;
    lat_y=lon_x=0;
    while(list_node!=NULL){
        lat_y=atoi(list_node->lat);
        lon_x=atoi(list_node->lon);
        SDL_Event event;
        int repeat = 0;
        while(!repeat){
            SDL_SetRenderDrawColor(map,0,0,0,255);
            SDL_RenderDrawPoint(map,lon_x,lat_y);
            SDL_RenderPresent(map);
            SDL_PollEvent(&event);
            switch(event.type){
            case SDL_QUIT:
                repeat=1;
                break;
            }
        }
    }
 }
