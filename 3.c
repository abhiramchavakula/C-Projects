/*
Name: Sonu Chavakula
Pawprint: avc9wb	
Section: F
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXLINELENGTH 200
#define MAXCARPRICE 1000000

typedef struct node{
	char make[25];
	char model[25];
	int price;
	int year;
	char color[25];
	char type[25];
	int mileage;
	struct node* left;
	struct node* right;
} Node;

//Function Prototypes

Node* get_cars(char* filename);
Node* com_helper(char* key,char* pair,Node* node);
Node* add_to_tree(Node* head, Node* new);
void search_tree(Node* root, int year, int price, int* count);
int valid(char* pair, char* input);
void free_tree(Node* root);

int main(int argc, char** argv){
	if(argc != 2){
		printf("Incorrect input, please try again.\n");
	}
	int choice;
	//int key;
	//int year;
	//int price;

	Node* root = get_cars(argv[1]);	
	//printf("\n\nRoot Address = %p", root);
	while(choice != -1){
		int count = 0;
		printf("\nTo search for a vehicle newer than a specific year enter '1':\n");
		printf("To search for a vehicle that costs less than a certain price enter '2':\n");
		printf("To search for a vehicle with both of the above parameters enter '3':");
		scanf("%d", &choice);
		if(choice == -1){
			break;
		}

		if(choice == 1){
			int selection;
			printf("Enter the year you would like the vehicles to be newer than:");
			scanf("%d", &selection);
			//printf("%d", root->year);
			search_tree(root, selection, 0, &count);
			printf("There were %d cars found\n", count);
		}

		if(choice == 2){
			int selection;	
			printf("Enter the price you would like the vehicles to be less than:");
			scanf("%d", &selection);
			search_tree(root, 0, selection, &count);
			printf("There were %d cars found\n", count);
		}

		if(choice == 3){
			int selection;
			int select;
			printf("Enter the year you would like the vehicles to be newer than:");
			scanf("%d", &selection);
			printf("Enter the price you would like the vehicles to be less than:");
			scanf("%d", &select);
			search_tree(root, selection, select, &count);
			printf("There were %d cars found\n", count);
		}

	}






	return 0;
}


Node* get_cars(char* filename){
	//printf("get cars has been called");
	Node* root = NULL;
	FILE *fptr;
	fptr = fopen("input.txt", "r");
	char line[MAXLINELENGTH];
	char* value;
	char* key = malloc(sizeof(char)*25);
	char* pair = malloc(sizeof(char)*25);
	//int i =0;
	//printf("before getcars While");
	while(fgets(line, MAXLINELENGTH, fptr)){
		if(strcmp(line, " ")==0){
			printf("null line");
			break;
		}	
		Node* newNode = malloc(sizeof(Node));
		value = strtok(line, "|");
		if(key != NULL && value != NULL){
			key = strcpy(key, value);
		}
		value = strtok(NULL, "|");
		if(pair != NULL && value != NULL){
			pair = strcpy(pair, value);
		}
		//printf("\nnewNode : %p", newNode);
		newNode = com_helper(key, pair, newNode);
		//printf("\nnewNode : %p", newNode);
		if(newNode == NULL){
			free(newNode);
		} else {
			int i;
			for(i=0; i<6; i++){
				value = strtok(NULL, "|");
				if(key != NULL && value != NULL){
					key = strcpy(key, value);
				}
				value = strtok(NULL, "|");
				if(pair != NULL && value != NULL){
					pair = strcpy(pair, value);
				}
				if(pair != NULL && key != NULL)
					newNode = com_helper(key, pair, newNode);

				if(newNode == NULL){
					//printf("ALDKFJLAKDJFALDJFLADF");
					free(newNode);
					break;
				}
			}
		}
		//printf("%d", i++);
		if(newNode != NULL){
			root = add_to_tree(root, newNode);
		}
	}
	return root;
}	

Node* com_helper(char* key,char* pair,Node* node){
	//printf("\nnode: %p", node);
	if(strcmp(key, "price")==0){
		node->price = atoi(pair);
	}
	else if(strcmp(key, "model")==0){
		strcpy(node->model, pair);
	}
	else if(strcmp(key, "color")==0){
		if(valid(pair, "colors.txt")){
			strcpy(node->color, pair);
		}
	}else if(strcmp(key,"year")==0){
		node->year = atoi(pair);
	}
	else if(strcmp(key,"make")==0){
		if(valid(pair,"makes.txt")){
			strcpy(node->make, pair);
		}
	}
	else if(strcmp(key, "type")==0){
		if(valid(pair, "types.txt")){
			strcpy(node->type, pair);
		}
	}	
	else if(strcmp(key, "mileage")==0){
		node->mileage = atoi(pair);
	}

	else {
		//printf("INVALID KEY");
		return NULL;

	}
	//printf("\nnode: %p", node);
	return node;
}
int valid(char* pair, char* input){
	//printf("\n%s", input);
	FILE* fptr = fopen(input, "r");
	int valid = 0;
	char* x = malloc(sizeof(char)*25);
	//printf("made it to valid");
	while(!feof(fptr)){
		fscanf(fptr,"%s", x);
		//printf("\n%s", x);
		if(strcmp(x, pair) == 0){
			valid = 1;
			break;
		}
		valid++;
	}
	//printf("And got out");
	fclose(fptr);
	return valid;
	return 1;
}

Node* add_to_tree(Node* head, Node* new){
	if(head == NULL){
		new->left = new->right = NULL;
		return new;
	}
	else if(new->price < head->price){
		head->left = add_to_tree(head->left, new);
	}
	else if(new->price > head->price){
		head->right = add_to_tree(head->right, new);
	}

	return head;
}

void search_tree(Node* root, int year, int price, int* count){
	if(price == 0){
		price = 2000000000;
	}

	if(root != NULL){
		if(root->price <= price && root->year > year){
			(*count)++;
			printf("%d %s %s that cost $%d\n",root->year, root->make, root->model, root->price);
		}

		search_tree(root->left, year, price, count);
		if(root->price <= price){
			search_tree(root->right, year, price, count);
		}
	}
}

void free_tree(Node* root){
	if(root != NULL){
		free_tree(root->left);
		free_tree(root->right);
		free(root);
	}
}
