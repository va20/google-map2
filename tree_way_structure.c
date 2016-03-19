#include "tree_way_structure.h"

//creation de l'arbre tree_way
AVL_tree_way* init_tree_way(){
	AVL_tree_way* tree_way=NULL;
	tree_way=(AVL_tree_way*)malloc(sizeof(AVL_tree_way));
	if(tree_way==NULL){
		printf("Allocation memoire way_way a echoue\n");
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
	avl_way->left=NULL;
	avl_way->right=NULL;
	avl_way->id=way->id;
	avl_way->visible=way->visible;
	avl_way->way_tag=way->way_tag;
	avl_way->ref=NULL;
	return avl_way;
}

int max_way(int a,int b){
	return a>b ? a:b;
}

int height_way(AVL_way* avl_tree_way){
	int left_height=0;
	int right_height=0;
	if (avl_tree_way->left!=NULL)
	{
		left_height=1+height_way(avl_tree_way->left);
	}
	if (avl_tree_way->right!=NULL)
	{
		right_height=1+height_way(avl_tree_way->right);
	}
	//printf(" hauteur left %d\n",left_height );
	//printf("hauteur right %d\n",right_height );
	return max_way(left_height,right_height);
}

int balance_way(AVL_way* avl_tree_way){
	int left_height=0;
	int right_height=0;
	if (avl_tree_way->left!=NULL)
	{
		left_height=1+height_way(avl_tree_way->left);
	}
	if (avl_tree_way->right!=NULL)
	{
		right_height=1+height_way(avl_tree_way->right);
	}
	//printf("left height in balance : %d\n",left_height );
	//printf("right height in balance : %d\n",right_height );
	return left_height-right_height;
}

//Rotation gauche
AVL_way* left_To_leftRot_Way(AVL_way* way){
	AVL_way* tmp1=NULL;
	AVL_way* tmp2=NULL;
	tmp1=way;
	tmp2=tmp1->left;
	tmp1->left=tmp2->right;
	tmp2->right=tmp1;
	//printf("dans left to left \n");
	//affiche(tmp2);
	return tmp2;
}

AVL_way* right_To_rightRot_Way(AVL_way* way){
	AVL_way* tmp1=NULL;
	AVL_way* tmp2=NULL;
	tmp1=way;
	tmp2=way->right;
	tmp1->right=tmp2->left;
	tmp2->left=tmp1;
	return tmp2;

}

AVL_way* left_To_rightRot_Way(AVL_way* way){
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
	return tmp3;
}

AVL_way* right_To_leftRot_Way(AVL_way* way){
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
	return tmp3;
	
}



AVL_way* getway_balanced(AVL_way* way){
	/*int lh = height_way(way -> left);
	int ll = height_way(way -> right);
	if (abs(lh - ll) <= 1)
		return way;*/
	//AVL_way* new_way=NULL;
	int balance_value=0;
	//printf("balance pour le noeud : %s\n",way->id);
	balance_value=balance_way(way);
	//printf("factor avant l'appel rec %d\n",balance_value );
	if(way->left!=NULL){
		way->left=getway_balanced(way->left);
	}
	if(way->right!=NULL){
		way->right=getway_balanced(way->right);
	}
	//printf("factor %d\n",balance_value );
	if(balance_value>=2){
		int n=balance_way(way->left);
		if(n<=-1){
			//printf("left to right\n");
			way=left_To_rightRot_Way(way);
		}
		else{
			//printf("left to left\n");
			way=left_To_leftRot_Way(way);
		}
	}
	else if(balance_value<=-2){
		int n=balance_way(way->right);
		if(n>=1){
			//printf("right to left\n");
			way=right_To_leftRot_Way(way);
		}
		else{
			//printf("right to right\n");
			way=right_To_rightRot_Way(way);
		}
	}
	return way;
}
void getTree_belanced_Way(AVL_tree_way* tree){
	AVL_way* tmp=NULL;
	tmp=getway_balanced(tree->root);
	if(tree->root!=tmp){
		tree->root=tmp;
	}
}
void insertion_way(AVL_tree_way* avl_tree_way,Way* list_way){
	//printf("je suis dans insertion\n");
	AVL_way* tmp=NULL;
	if(avl_tree_way->root==NULL){
		avl_tree_way->root=create_AVL_way(list_way);
		printf("rien a faire\n");
		return;
	}
	else{
		tmp=avl_tree_way->root;
		//printf("dans else\n");
		while(tmp!=NULL && strcmp(tmp->id,list_way->id)!=0){
			//printf("dans while\n");
			//printf("%s\n",tmp->id );
			//printf("list way %s\n",list_way->id );
			if(strcmp(tmp->id,list_way->id)>0){
				//printf("dans if while\n");
				if(tmp->left!=NULL){
					//printf("dans if 2 while\n");
					tmp=tmp->left;
				}
				else{
					tmp->left=create_AVL_way(list_way);
					//printf("avant equilibrage\n");
					//affiche(avl_tree_way->root);
					//avl_tree_way->root=getway_balanced(avl_tree_way->root);
					//printf("apres equilibrage\n");
					//affiche(avl_tree_way->root);
				}
			}
			else if(strcmp(tmp->id,list_way->id)<0){
				//printf("dans else if while\n");
				if(tmp->right!=NULL){
					//printf("dans if 2 else if \n");
					tmp=tmp->right;
				}
				else{
					//printf("avant equilibre droit\n");
					tmp->right=create_AVL_way(list_way);
					//avl_tree_way->root=getway_balanced(avl_tree_way->root);
					//printf("apres equilibre droit\n");
				}
			}
		}
	}
	getTree_belanced_Way(avl_tree_way);
}
void print_spc_way(int k) {
	int i;
	for (i = 0; i < k; i++)
		printf (" ");
}

void affiche_indent_Way(AVL_way* way, int k){
	if(way==NULL){return;}
	printf("%s\n",way->id);
	affiche_indent_Way(way->left,k + 1);
	print_spc_way(k);
	
	affiche_indent_Way(way->right, k + 1);
}

void affiche_suffixe_Way(AVL_way* way, int k){
	if(way==NULL){return;}
	affiche_suffixe_Way(way->left,k + 1);
	printf("%s\n",way->id);
	print_spc_way(k);
	
	affiche_suffixe_Way(way->right, k + 1);
}
void affiche_Way(AVL_way *way) {
	affiche_indent_Way(way, 0);
	printf("affiche suffixe\n");
	affiche_suffixe_Way(way, 0);
}