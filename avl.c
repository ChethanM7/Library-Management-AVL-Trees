
#include<stdio.h> 
#include<stdlib.h>
#include <string.h>
#define MAX_LIMIT 25 
struct Node 
{ 
	int key;
	char book[20]; 
	char name[40];
	int srn;
	struct Node *left; 
	struct Node *right; 
	int height; 
}; 

int max(int a, int b); 
int height(struct Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return N->height; 
} 

int max(int a, int b) 
{ 
	return (a > b)? a : b; 
} 

struct Node* newNode(int key,char*book,char*name,int srn) 
{ 
	struct Node* node = (struct Node*) 
						malloc(sizeof(struct Node)); 
	node->key = key;
	strcpy(node->book,book);
	strcpy(node->name,name);
	//node->book=book;
	//node->name=name;
	node->srn=srn;
	node->left = NULL; 
	node->right = NULL; 
	node->height = 1;
	return(node); 
} 
struct Node *rightRotate(struct Node *y) 
{ 
	struct Node *x = y->left; 
	struct Node *T2 = x->right; 
	x->right = y; 
	y->left = T2;  
	y->height = max(height(y->left), height(y->right))+1; 
	x->height = max(height(x->left), height(x->right))+1;  
	return x; 
} 
struct Node *leftRotate(struct Node *x) 
{ 
	struct Node *y = x->right; 
	struct Node *T2 = y->left; 

	// Perform rotation 
	y->left = x; 
	x->right = T2; 
 
	x->height = max(height(x->left), height(x->right))+1; 
	y->height = max(height(y->left), height(y->right))+1; 
	return y; 
} 
int getBalance(struct Node *N) 
{ 
	if (N == NULL) 
		return 0; 
	return height(N->left) - height(N->right); 
} 

struct Node* insert(struct Node* node, int key,char*book,char*name,int srn) 
{ 
	if (node == NULL) 
		return(newNode(key,book,name,srn)); 

	if (key < node->key) 
		node->left = insert(node->left, key,book,name,srn); 
	else if (key > node->key) 
		node->right = insert(node->right, key,book,name,srn); 
	else {
		printf("\nA Book with the same Id is already present in Library\n");
		return node; 
	}
	node->height = 1 + max(height(node->left), 
						height(node->right)); 
	int balance = getBalance(node); 
	if (balance > 1 && key < node->left->key) 
		return rightRotate(node); 
	if (balance < -1 && key > node->right->key) 
		return leftRotate(node); 
	if (balance > 1 && key > node->left->key) 
	{ 
		node->left = leftRotate(node->left); 
		return rightRotate(node); 
	} 

	if (balance < -1 && key < node->right->key) 
	{ 
		node->right = rightRotate(node->right); 
		return leftRotate(node); 
	} 
	return node; 
} 


struct Node * minValueNode(struct Node* node) 
{ 
	struct Node* current = node; 
	while (current->left != NULL) 
		current = current->left; 

	return current; 
} 
struct Node* deleteNode(struct Node* root, int key,char*name,int srn) 
{
	if (root == NULL){
		printf("\nThe requested book is not available\n");
		return root;
	} 
	if ( key < root->key ) 
		root->left = deleteNode(root->left, key,name,srn); 
	else if( key > root->key ) 
		root->right = deleteNode(root->right, key,name,srn);  
	else if(key==root->key)
	{   if(root->srn!=-1)
		{
			printf("\nThis book is already taken\n");
			return root;
		}
		strcpy(root->name,name);
		root->srn=srn;
		//printf("12 book id:%d book name:%s name:%s srn:%d\n",root->key,root->book,root->name,root->srn );
	} 
	

	return root; 
} 
struct Node* returning(struct Node* root, int key) 
{
	if (root == NULL){
		printf("\nYou have not borrowed this book\n");
		return root;
	} 
	if ( key < root->key ) 
		root->left = returning(root->left, key); 
	else if( key > root->key ) 
		root->right = returning(root->right, key);  
	else if(key==root->key)
	{   
			root->srn=-1;
			strcpy(root->name,"");
			return root;
	} 
	return root;	
}
void preOrder(struct Node *root) 
{ 
	char*status;
	if(root != NULL) 
	{ 
		if(root->srn==-1){
			status="available";
			printf("\nBook id:%3d  Book name:%7s Status:%s",root->key,root->book,status); 		
		}
		else{
			status="unavailable";
		printf("\nBook id:%3d  Book name:%7s Status:%s ---> Student Name:%sSrn:%d", root->key,root->book,status,root->name,root->srn); 
		}
		preOrder(root->left); 
		preOrder(root->right); 
	} 
} 

int main() 
{ 
	struct Node *root = NULL;
	root = insert(root, 132,"book1","DS BY SUMANTH",-1); 
	root = insert(root, 45,"book2","DML BY MONISH",-1);
	root = insert(root, 65,"book3","IDS BY AKSHAY",-1);
	root = insert(root, 42,"book4","WEB-TECH BY RITHVIK",-1);
	root = insert(root, 15,"book5","DDCO BY UDDHAR",-1);
	root = insert(root, 54,"book6","PHY BY RISHI",-1);
	root = insert(root, 73,"book7","CHEM BY SUPREET",-1);
	root = insert(root, 28,"book8","BIO BY KAUSTAB",-1);
	root = insert(root, 40,"book10","MECHANICS BY SAI CHARAN",-1);
	root = insert(root, 99,"book9","MECHANICAL BY CHETHAN",-1);
	root = insert(root, 91,"book11","ELECTRICAL BY ANIRUDH",-1);
	root = insert(root, 26,"book12","ELECTRONICS BY SAGAR",-1); 
	int a=1;
	int srn;
	char str[20];
	int xy;
	int choice;
	int borrow[10];
	int o=1;
	while(a)
	{
		printf("\nOptions\n");
		printf("1. Display Books\n");
		printf("2. Borrow\n");
		printf("3. Return\n");
		printf("4. Add a new book\n");
		printf("5. exit\n");
		scanf("%d",&choice);
		printf("\n");
		
		if(choice==1)
		{
			printf("\nLibrary has the following books");
			preOrder(root);
			printf("\n");
		}
		if(choice==2)
		{
			int id1;	
			memset(str,'\0',20);
			printf("Enter the book id of the book u wish to borrow:");
			scanf("%d",&id1);
			printf("Enter your srn:");
			scanf("%d",&srn);
			printf("Enter your First name:");
			scanf("\n");
			fgets(str, MAX_LIMIT, stdin);
			//printf("%s\n",str);
			root=deleteNode(root,id1,str,srn);
			printf("\n");
			printf("To see changes press 1 (Display)\n");
			
		}
		if(choice ==3)
		{
			printf("Enter the id of the book you are returning:");
			scanf("%d",&xy);
			root=returning(root,xy);
			printf("\n");
			printf("To see changes press 1 (Display)\n");
		}
		if(choice==4)
		{
			int j;
			char str2[20];
			char c;
			printf("Enter the book id of the new book to be added:");
			scanf("%d",&j);
			printf("Enter the name of the book:");
			scanf("%s",str2);
			root=insert(root,j,str2,"",-1);
			printf("\n");
			printf("To see changes press 1 (Display)\n");
		}
		if(choice==5)
			break;
		

		
	
	}

	return 0; 
} 

