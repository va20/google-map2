#include "tree_structure.h"
//creation de l'arbre tree_node


AVL_tree_node* init_tree_node(){
	AVL_tree_node* tree_node=NULL;
	tree_node=(AVL_tree_node*)malloc(sizeof(AVL_tree_node));
	if(tree_node==NULL){
		printf("Allocation memoire node_tree a echoue\n");
		return NULL;
	}
	tree_node->root=NULL;
	return tree_node;
}
//creation de l'arbre tree_way
AVL_tree_way* init_tree_way(){
	AVL_tree_way* tree_way=NULL;
	tree_way=(AVL_tree_way*)malloc(sizeof(AVL_tree_way));
	if(tree_way==NULL){
		printf("Allocation memoire node_way a echoue\n");
		return NULL;
	}
	tree_way->root=NULL;
	return tree_way;	
}

AVL_node* create_AVL_node(Node* node){
	AVL_node* avl_node=NULL;
	avl_node=(AVL_node*)malloc(sizeof(AVL_node));
	if(avl_node==NULL){
		printf("allocation memoire avl_node a echoue\n");
		return NULL;
	}
	avl_node->left=NULL;
	avl_node->right=NULL;
	avl_node->node_tag=node->node_tag;
	avl_node->id=node->id;
	avl_node->visible=node->visible;
	avl_node->lon=node->lon;
	avl_node->lat=node->lat;
	return avl_node;
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

//methode pour calculer la hauteur d'un noeud

int max(int a,int b){
	return a>b ? a:b;
}

int height_node(AVL_node* avl_tree_node){
	int left_height=0;
	int right_height=0;
	if(avl_tree_node->left!=NULL){
		left_height=1+height_node(avl_tree_node->left);
	}
	if(avl_tree_node->right!=NULL){
		right_height=1+height_node(avl_tree_node->right);
	}
	//printf(" hauteur left %d\n",left_height );
	//printf("hauteur right %d\n",right_height );
	return max(left_height,right_height);
}

int balance_node(AVL_node* avl_tree_node){
	int left_height=0;
	int right_height=0;
	if (avl_tree_node->left!=NULL)
	{
		left_height=height_node(avl_tree_node);
	}
	if (avl_tree_node->right!=NULL)
	{
		/* code */
		right_height=height_node(avl_tree_node);
	}
	return left_height-right_height;
}

//Rotation gauche
AVL_node* left_To_leftRot(AVL_node* node){
	AVL_node* tmp=NULL;
	AVL_node* tmp2=NULL;
	tmp=node;
	tmp2=tmp->left;
	tmp->left=tmp2->right;
	tmp2->right=tmp;
	printf("dans left to left \n");
	affiche(tmp2);
	return tmp2;
}

AVL_node* right_To_rightRot(AVL_node* node){
	AVL_node* tmp=NULL;
	AVL_node* tmp2=NULL;
	tmp=node;
	tmp2=node->right;
	tmp->right=tmp2->left;
	tmp2->left=tmp;
	return tmp2;

}

AVL_node* left_To_rightRot(AVL_node* node){
	/*AVL_node *tmp = node -> left;
	node -> left = tmp -> right;
	tmp -> right = node;
	return tmp;*/

	AVL_node* tmp=NULL;
	AVL_node* tmp2=NULL;
	AVL_node* tmp3=NULL;
	tmp=node;
	tmp2=node->left;
	tmp3=tmp2->right;
	tmp->left=tmp3->right;
	tmp2->right=tmp3->left;
	tmp3->left=tmp2;
	tmp3->right=tmp;
	return tmp3;
}

AVL_node* right_To_leftRot(AVL_node* node){
	/*AVL_node *tmp = node -> right;
	node -> right = tmp-> left;
	tmp  -> left  = node;
	return tmp;*/

	
	AVL_node* tmp=NULL;
	AVL_node* tmp2=NULL;
	AVL_node* tmp3=NULL;
	tmp=node;
	tmp2=node->right;
	tmp3=tmp2->left;
	tmp->right=tmp3->left;
	tmp2->left=tmp3->right;
	tmp3->left=tmp;
	tmp3->right=tmp2;
	return tmp3;
	
}



AVL_node* getNode_balanced(AVL_node* node){
	/*int lh = height_node(node -> left);
	int ll = height_node(node -> right);
	if (abs(lh - ll) <= 1)
		return node;*/
	//AVL_node* new_node=NULL;
	int balance_value=0;
	if(node->left!=NULL){
		node->left=getNode_balanced(node->left);
	}
	if(node->right!=NULL){
		node->right=getNode_balanced(node->right);
	}
	balance_value=balance_node(node);
	printf("factor %d\n",balance_value );
	if(balance_value>=2){
		int n=balance_node(node->left);
		if(n<=-1){
			printf("left to right\n");
			node=left_To_rightRot(node);
		}
		else{
			printf("left to left\n");
			node=left_To_leftRot(node);
		}
	}
	else if(balance_value<=-2){
		int n=balance_node(node->right);
		if(n>=1){
			printf("right to left\n");
			node=right_To_leftRot(node);
		}
		else{
			printf("right to right\n");
			node=right_To_rightRot(node);
		}
	}

	return node;
}
void insertion_node(AVL_tree_node* avl_tree_node,Node* list_node){
	printf("je suis dans insertion\n");
	AVL_node* tmp=NULL;
	if(avl_tree_node->root==NULL){
		avl_tree_node->root=create_AVL_node(list_node);
		printf("rien a faire\n");
		return;
	}
	else{
		tmp=avl_tree_node->root;
		//printf("dans else\n");
		while(tmp!=NULL && strcmp(tmp->id,list_node->id)!=0){
			//printf("dans while\n");
			//printf("%s\n",tmp->id );
			//printf("list node %s\n",list_node->id );
			if(strcmp(tmp->id,list_node->id)>0){
				//printf("dans if while\n");
				if(tmp->left!=NULL){
					//printf("dans if 2 while\n");
					tmp=tmp->left;
				}
				else{
					tmp->left=create_AVL_node(list_node);
					printf("avant equilibrage\n");
					affiche(avl_tree_node->root);
					avl_tree_node->root=getNode_balanced(avl_tree_node->root);
					printf("apres equilibrage\n");
					affiche(avl_tree_node->root);
				}
			}
			else if(strcmp(tmp->id,list_node->id)<0){
				//printf("dans else if while\n");
				if(tmp->right!=NULL){
					//printf("dans if 2 else if \n");
					tmp=tmp->right;
				}
				else{
					printf("avant equilibre droit\n");
					tmp->right=create_AVL_node(list_node);
					avl_tree_node->root=getNode_balanced(avl_tree_node->root);
					printf("apres equilibre droit\n");
				}
			}
		}
	}
}
AVL_node* search(AVL_node* avl_node,char* ref){
	AVL_node* tmp=NULL;
	tmp=avl_node;
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

void print_spc(int k) {
	int i;
	for (i = 0; i < k; i++)
		printf (" ");
}

void affiche_indent(AVL_node* node, int k){
	if(node==NULL){return;}
	printf("%s\n",node->id);
	affiche_indent(node->left,k + 1);
	print_spc(k);
	
	affiche_indent(node->right, k + 1);
}

void affiche_suffixe(AVL_node* node, int k){
	if(node==NULL){return;}
	affiche_suffixe(node->left,k + 1);
	printf("%s\n",node->id);
	print_spc(k);
	
	affiche_suffixe(node->right, k + 1);
}
void affiche(AVL_node *node) {
	affiche_indent(node, 0);
	printf("affiche suffixe\n");
	affiche_suffixe(node, 0);
}