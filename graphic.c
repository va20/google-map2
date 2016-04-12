#include "graphic.h"


SDL_Window* Create_Window(int height,int width){

    SDL_Window* fenetre=NULL;
    SDL_Renderer* map=NULL;
    if(SDL_VideoInit(NULL)<0){
        printf("Erreur initialisation %s\n",SDL_GetError());
        return NULL;
    }
    fenetre=SDL_CreateWindow("Google_Map_2",SDL_WINDOWPOS_CENTERED,SDL_WINDOWPOS_CENTERED,
        width,height,0);
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



