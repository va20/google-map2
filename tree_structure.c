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
	return max(left_height,right_height);
}

int balance_node(AVL_node* avl_tree_node){
	int left_height=0;
	int right_height=0;
	if (avl_tree_node->left!=NULL)
	{
		left_height=height_node(avl_tree_node->left);
	}
	if (avl_tree_node->right!=NULL)
	{
		/* code */
		right_height=height_node(avl_tree_node->right);
	}
	return left_height-right_height;
}

//Rotation gauche
AVL_node* left_To_leftRot(AVL_node* node){
	AVL_node* tmp=NULL;
	AVL_node* tmp2=NULL;
	tmp=node;
	tmp2=node->left;
	tmp->left=tmp2->right;
	tmp2->right=tmp;
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
	AVL_node* new_node=NULL;
	int balance_value=0;
	if(node->left!=NULL){
		node->left=getNode_balanced(node->left);
	}
	if(node->right!=NULL){
		node->right=getNode_balanced(node->right);
	}
	balance_value=balance_node(node);
	if(balance_value>=2){
		int n=balance_node(node->left);
		if(n<=-1){
			new_node=left_To_rightRot(node);
		}
		else{
			new_node=left_To_leftRot(node);
		}
	}
	else if(balance_value<=-2){
		int n=balance_node(node->right);
		if(n>=1){
			new_node=right_To_leftRot(node);
		}
		else{
			new_node=right_To_rightRot(node);
		}
	}
	else{
		new_node=node;
	}

	return new_node;
}
void insertion_node(AVL_node* avl_node,Node* list_node){
	AVL_node* tmp=NULL;
	AVL_node* new_node=NULL;
	tmp=avl_node;
	if(avl_node==NULL){
		avl_node=create_AVL_node(list_node);
	}
	else{
		while(tmp!=NULL){
			if(strcmp(tmp->id,list_node->id)>0){
				if(tmp->left!=NULL){
					tmp=tmp->left;
				}
			}
			else if(strcmp(tmp->id,list_node->id)<0){
				if(tmp->right!=NULL){
					tmp=tmp->right;
				}
			}
		}
		new_node=create_AVL_node(list_node);
		if(strcmp(tmp->id,list_node->id)>0){
			tmp->left=new_node;
		}
		else if(strcmp(tmp->id,list_node->id)<0){
			tmp->right=new_node;
		}
	}
	getNode_balanced(avl_node);
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