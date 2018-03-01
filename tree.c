/*
Name: Sonu Chavakula
Pawprint: avc9wb
Section: F
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <ctype.h>
#include <stdint.h>

#define FILESIZE 100000

typedef struct node{
	int value;
	struct node* left;
	struct node* right;
}Node;

//Function Prototypes
Node* Build_Tree(char* input_file);
Node* Add_Node(Node* root, int value);
void Free_Tree(Node* root);
int Search_Tree(Node* root, int value);
int Linear_Search(int* array, int value);
int* Build_Linear_Structure(char* input_file);

int main(int argc, char** argv){
	if(argc < 2){
		printf("Incorrect number of arguments, please try again.\n");
	}

	char* filename = argv[1];
	Node* root = Build_Tree(filename);
	int* array = Build_Linear_Structure(filename); 
	int search;
	do{
		printf("Enter a value to search between 1-10001:\n");
		scanf("%d", &search);
	}while(search<1 && search>10001);	
	struct timespec t, t2;
	uint64_t t3;
	clock_gettime(CLOCK_MONOTONIC_RAW, &t);
	int success = Linear_Search(array, search);
	clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
	t3 = (t2.tv_sec - t.tv_sec)*100000 + (t2.tv_nsec - t.tv_nsec)/1000;
	if(success == 1){
		printf("Your linear search was successfull, and took %lf milliseconds\n", (double)t3);	
	}
	else{
		printf("Your linear search was unsuccessfull, and took %lf milliseconds\n", (double)t3);	
	}


	clock_gettime(CLOCK_MONOTONIC_RAW, &t);
	success = Search_Tree(root, search);
	clock_gettime(CLOCK_MONOTONIC_RAW, &t2);
	t3 = (t2.tv_sec - t.tv_sec)*100000 + (t2.tv_nsec - t.tv_nsec)/1000;
	if(success == 1){
		printf("Your binary search was successfull, and took %lf milliseconds\n", (double)t3);	
	}
	else{
		printf("Your binary search was unsuccessfull, and took %lf milliseconds\n", (double)t3);	
	}


	Free_Tree(root);


	return 0;
}

Node* Build_Tree(char* input_file){
	Node* temp;
	//int i=0;
	int value;
	temp = (Node*)malloc(sizeof(Node));
	FILE* filename = fopen(input_file, "r");
	while(!feof(filename)){
		fscanf(filename, "%d", &value);
		/*if(i==0){
		  temp->value = value;
		  i++;
		  }*/
		if(value < temp->value){
			temp->left = temp;
		}
		else if(value > temp->value){
			temp->right = temp;
		}
	}
	temp->left=NULL;
	temp->right=NULL;
	return temp;
}

Node* Add_Node(Node* root, int value){
	if(root == NULL){
		Node* temp;
		temp = (Node*)malloc(sizeof(Node));
		temp->value = value;
		temp->left = temp->right = NULL;
		return temp;
	}
	if(value < (root->value)){
		root->left = Add_Node(root->left, value);
	}
	else if(value > (root->value)){
		root->right = Add_Node(root->right, value);
	}
	return root;
}

void Free_Tree(Node* root){
	if(root != NULL){
		Free_Tree(root->left);
		Free_Tree(root->right);
		free(root);
	}
}

int* Build_Linear_Structure(char* filename){
	//char* input_file;
	FILE* fptr;
	int j=0;
	int* number = malloc(sizeof(number)*FILESIZE);
	fptr = fopen(filename, "r");
	while(!feof(fptr)){
		fscanf(fptr, "%d", (number+j));
		j++;
	}		
	fclose(fptr);
	return number;
}

int Linear_Search(int* array, int value){
	int i;
	for(i=0; i<FILESIZE; i++){
		if(*(array+i) == value){
			return 1;
		}
	}
	return 0;
}

int Search_Tree(Node* root, int value){

	if(root->value == value){
		return 1;
	return Search_Tree(root->right, value);
	return Search_Tree(root->left, value);
}
return 0;
}
