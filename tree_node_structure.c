#include "tree_node_structure.h"
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
AVL_node* create_AVL_node(Node* node){
	AVL_node* avl_node=NULL;
	avl_node=(AVL_node*)malloc(sizeof(AVL_node));
	if(avl_node==NULL){
		printf("allocation memoire avl_node a echoue\n");
		return NULL;
	}
	avl_node->hauteur=0;
	avl_node->left=NULL;
	avl_node->right=NULL;
	avl_node->node_tag=node->node_tag;
	avl_node->id=node->id;
	avl_node->visible=node->visible;
	avl_node->lon=node->lon;
	avl_node->lat=node->lat;
	//avl_node->hauteur=0;
	return avl_node;
}
//methode pour calculer la hauteur d'un noeud

int max_node(int a,int b){
	return a>b ? a:b;
}

int height_node(AVL_node* avl_tree_node){
	if(avl_tree_node!=NULL){
		return avl_tree_node->hauteur;
	}
	return -1;
}

//Rotation gauche
AVL_node* left_To_leftRot(AVL_node* node){
	AVL_node* tmp1=NULL;
	AVL_node* tmp2=NULL;
	
	tmp1=node;
	tmp2=tmp1->left;
	
	tmp1->left=tmp2->right;
	tmp2->right=tmp1;
	
	tmp2->hauteur=max_node(height_node(tmp2->left),height_node(tmp2->right))+1;
	tmp1->hauteur=max_node(height_node(tmp1->left),height_node(tmp1->right))+1;
	return tmp2;
}

AVL_node* right_To_rightRot(AVL_node* node){
	AVL_node* tmp1=NULL;
	AVL_node* tmp2=NULL;
	
	tmp1=node;
	tmp2=node->right;

	tmp1->right=tmp2->left;
	tmp2->left=tmp1;
	
	tmp2->hauteur=max_node(height_node(tmp2->left),height_node(tmp2->right))+1;
	tmp1->hauteur=max_node(height_node(tmp1->left),height_node(tmp1->right))+1;
	return tmp2;

}

AVL_node* left_To_rightRot(AVL_node* node){
	/*AVL_node *tmp = node -> left;
	node -> left = tmp -> right;
	tmp -> right = node;
	return tmp;*/

	AVL_node* tmp1=NULL;
	AVL_node* tmp2=NULL;
	AVL_node* tmp3=NULL;
	
	tmp1=node;
	tmp2=node->left;
	tmp3=tmp2->right;

	tmp1->left=tmp3->right;
	tmp2->right=tmp3->left;
	tmp3->left=tmp2;
	tmp3->right=tmp1;

	tmp3->hauteur=max_node(height_node(tmp3->left),height_node(tmp3->right))+1;
	tmp2->hauteur=max_node(height_node(tmp2->left),height_node(tmp2->right))+1;
	tmp1->hauteur=max_node(height_node(tmp1->left),height_node(tmp1->right))+1;
	return tmp3;
}

AVL_node* right_To_leftRot(AVL_node* node){
	/*AVL_node *tmp = node -> right;
	node -> right = tmp-> left;
	tmp  -> left  = node;
	return tmp;*/

	
	AVL_node* tmp1=NULL;
	AVL_node* tmp2=NULL;
	AVL_node* tmp3=NULL;
	
	tmp1=node;
	tmp2=node->right;
	tmp3=tmp2->left;
	
	tmp1->right=tmp3->left;
	tmp2->left=tmp3->right;
	tmp3->left=tmp1;
	tmp3->right=tmp2;
	
	tmp3->hauteur=max_node(height_node(tmp3->left),height_node(tmp3->right))+1;
	tmp2->hauteur=max_node(height_node(tmp2->left),height_node(tmp2->right))+1;
	tmp1->hauteur=max_node(height_node(tmp1->left),height_node(tmp1->right))+1;

	return tmp3;
	
}



AVL_node* getNode_balanced(AVL_node* node){
	int balance_value=0;
	balance_value=height_node(node->left)-height_node(node->right);
	//printf("facteur du noeud : %s\n",node->id );
	//printf("factor %d\n",balance_value );
	if(balance_value>=2){
		int n=0;
		if (node->left->right!=NULL && node->left->left == NULL){
			n=0-height_node(node->left->right);
			if(n<=-1){
			printf("left to right\n");
			node=left_To_rightRot(node);
		}
	}
		
		else{
			printf("left to left\n");
			node=left_To_leftRot(node);
		}
	}
	else if(balance_value<=-2){
		int n=0;
		if (node->right->left!=NULL && node->right->right==NULL){
			n=height_node(node->right->left)-0;
			if(n>=1){
				printf("right to left\n");
				node=right_To_leftRot(node);
			}
		}
		else{
			printf("right to right\n");
			node=right_To_rightRot(node);
		}
	}
	return node;
}

AVL_node* insertion_node(AVL_node* avl_node,Node* list_node){
	//printf("je suis dans insertion\n");
	if(avl_node==NULL){
		avl_node=create_AVL_node(list_node);
		//printf("rien a faire\n");
	}
	else if(strcmp(avl_node->id,list_node->id)>0){
		avl_node->left=insertion_node(avl_node->left,list_node);
		int balance=0;
		balance=height_node(avl_node->left)-height_node(avl_node->right);
		//printf("balance pour le noeud : %s\n",avl_node->id );
		//printf("balance dans insertion %d\n",balance );
		if(balance>=2 || balance<-1){
			avl_node=getNode_balanced(avl_node);
		}
		
	}
	else if(strcmp(avl_node->id,list_node->id)<0){
		avl_node->right=insertion_node(avl_node->right,list_node);
		int balance=0;
		balance=height_node(avl_node->left)-height_node(avl_node->right);
		if(balance>=2 || balance<-1){
			avl_node=getNode_balanced(avl_node);
		}
	}
	avl_node->hauteur=max_node(height_node(avl_node->left),height_node(avl_node->right))+1;
	return avl_node;
}

AVL_node* search_node(AVL_node* avl_node,char* ref){
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