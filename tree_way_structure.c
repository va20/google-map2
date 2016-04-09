#include "tree_way_structure.h"
//creation de l'arbre tree_way


AVL_tree_way* init_tree_way(){
	AVL_tree_way* tree_way=NULL;
	tree_way=(AVL_tree_way*)malloc(sizeof(AVL_tree_way));
	if(tree_way==NULL){
		printf("Allocation memoire way_tree a echoue\n");
		return NULL;
	}
	tree_way->root=NULL;
	return tree_way;
}
AVL_way* create_AVL_way(Way* way){
	AVL_way* avl_way=NULL;
	avl_way=(AVL_way*)malloc(sizeof(AVL_way));
	if(avl_way==NULL){
		printf("allocation memoire avl_way a echoue\n");
		return NULL;
	}
	avl_way->hauteur=0;
	avl_way->left=NULL;
	avl_way->right=NULL;
	avl_way->way_tag=way->way_tag;
	avl_way->id=way->id;
	avl_way->visible=way->visible;
	avl_way->ref=NULL;
	return avl_way;
}
//methode pour calculer la hauteur d'un noeud

int max_way(int a,int b){
	return a>b ? a:b;
}

int height_way(AVL_way* avl_tree_way){
	if(avl_tree_way!=NULL){
		return avl_tree_way->hauteur;
	}
	return -1;
}

//Rotation gauche
AVL_way* left_To_leftRot_way(AVL_way* way){
	AVL_way* tmp1=NULL;
	AVL_way* tmp2=NULL;
	
	tmp1=way;
	tmp2=tmp1->left;
	
	tmp1->left=tmp2->right;
	tmp2->right=tmp1;
	
	tmp2->hauteur=max_way(height_way(tmp2->left),height_way(tmp2->right))+1;
	tmp1->hauteur=max_way(height_way(tmp1->left),height_way(tmp1->right))+1;
	return tmp2;
}

AVL_way* right_To_rightRot_way(AVL_way* way){
	AVL_way* tmp1=NULL;
	AVL_way* tmp2=NULL;
	
	tmp1=way;
	tmp2=way->right;

	tmp1->right=tmp2->left;
	tmp2->left=tmp1;
	
	tmp2->hauteur=max_way(height_way(tmp2->left),height_way(tmp2->right))+1;
	tmp1->hauteur=max_way(height_way(tmp1->left),height_way(tmp1->right))+1;
	return tmp2;

}

AVL_way* left_To_rightRot_way(AVL_way* way){
	/*AVL_way *tmp = way -> left;
	way -> left = tmp -> right;
	tmp -> right = way;
	return tmp;*/

	AVL_way* tmp1=NULL;
	AVL_way* tmp2=NULL;
	AVL_way* tmp3=NULL;
	
	tmp1=way;
	tmp2=way->left;
	tmp3=tmp2->right;

	tmp1->left=tmp3->right;
	tmp2->right=tmp3->left;
	tmp3->left=tmp2;
	tmp3->right=tmp1;

	tmp3->hauteur=max_way(height_way(tmp3->left),height_way(tmp3->right))+1;
	tmp2->hauteur=max_way(height_way(tmp2->left),height_way(tmp2->right))+1;
	tmp1->hauteur=max_way(height_way(tmp1->left),height_way(tmp1->right))+1;
	return tmp3;
}

AVL_way* right_To_leftRot_way(AVL_way* way){
	/*AVL_way *tmp = way -> right;
	way -> right = tmp-> left;
	tmp  -> left  = way;
	return tmp;*/

	
	AVL_way* tmp1=NULL;
	AVL_way* tmp2=NULL;
	AVL_way* tmp3=NULL;
	
	tmp1=way;
	tmp2=way->right;
	tmp3=tmp2->left;
	
	tmp1->right=tmp3->left;
	tmp2->left=tmp3->right;
	tmp3->left=tmp1;
	tmp3->right=tmp2;
	
	tmp3->hauteur=max_way(height_way(tmp3->left),height_way(tmp3->right))+1;
	tmp2->hauteur=max_way(height_way(tmp2->left),height_way(tmp2->right))+1;
	tmp1->hauteur=max_way(height_way(tmp1->left),height_way(tmp1->right))+1;

	return tmp3;
	
}



AVL_way* getway_balanced(AVL_way* way){
	/*int lh = height_way(way -> left);
	int ll = height_way(way -> right);
	if (abs(lh - ll) <= 1)
		return way;*/
	//AVL_way* new_way=NULL;
	int balance_value=0;
	balance_value=height_way(way)-height_way(way);
	//printf("balance pour le noeud : %s\n",way->id);
	//balance_value=balance_way(way);
	//printf("factor avant l'appel rec %d\n",balance_value );
	/*if(way->left!=NULL){
		way->left=getway_balanced(way->left);
	}
	if(way->right!=NULL){
		way->right=getway_balanced(way->right);
	}*/
	//printf("factor %d\n",balance_value );
	if(balance_value>=2){
		int n=height_way(way->left)-height_way(way->left);
		if(n<=-1){
			//printf("left to right\n");
			way=left_To_rightRot_way(way);
		}
		else{
			//printf("left to left\n");
			way=left_To_leftRot_way(way);
		}
	}
	else if(balance_value<=-2){
		int n=height_way(way->left)-height_way(way->right);
		if(n>=1){
			//printf("right to left\n");
			way=right_To_leftRot_way(way);
		}
		else{
			//printf("right to right\n");
			way=right_To_rightRot_way(way);
		}
	}
	return way;
}

AVL_way* insertion_way(AVL_way* avl_way,Way* list_way){
	//printf("je suis dans insertion\n");
	if(avl_way==NULL){
		avl_way=create_AVL_way(list_way);
		//printf("rien a faire\n");
	}
	else if(strcmp(avl_way->id,list_way->id)>0){
		avl_way->left=insertion_way(avl_way->left,list_way);
		int balance=0;
		balance=height_way(avl_way->left)-height_way(avl_way->right);
		if(balance>=2 || balance<-1){
			avl_way=getway_balanced(avl_way);
		}
		
	}
	else if(strcmp(avl_way->id,list_way->id)<0){
		avl_way->right=insertion_way(avl_way->right,list_way);
		int balance=0;
		balance=height_way(avl_way->left)-height_way(avl_way->right);
		if(balance>=2 || balance<-1){
			avl_way=getway_balanced(avl_way);
		}
	}
	avl_way->hauteur=max_way(height_way(avl_way->left),height_way(avl_way->right))+1;
	return avl_way;
}
AVL_way* search_way(AVL_way* avl_way,char* ref){
	AVL_way* tmp=NULL;
	tmp=avl_way;
	while(tmp!=NULL && strcmp(tmp->id,ref)!=0){
		if(strcmp(tmp->id,ref)>0){
			tmp=tmp->left;
		}
		else if (strcmp(tmp->id,ref)<0)
		{
			tmp=tmp->right;
		}
	}
	return tmp;
}

void print_spc_way(int k) {
	int i;
	for (i = 0; i < k; i++)
		printf (" ");
}

void affiche_indent_way(AVL_way* way, int k){
	if(way==NULL){return;}
	printf("%s\n",way->id);
	affiche_indent_way(way->left,k + 1);
	print_spc_way(k);
	
	affiche_indent_way(way->right, k + 1);
}

void affiche_suffixe_way(AVL_way* way, int k){
	if(way==NULL){return;}
	affiche_suffixe_way(way->left,k + 1);
	printf("%s\n",way->id);
	print_spc_way(k);
	
	affiche_suffixe_way(way->right, k + 1);
}
void affiche_way(AVL_way *way) {
	affiche_indent_way(way, 0);
	printf("affiche suffixe\n");
	affiche_suffixe_way(way, 0);
}