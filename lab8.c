/*
Name: Sonu Chavakula
Pawprint: avc9wb
Lab Code:
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX 10

typedef struct node{
	char* word;
	struct node* next;
	struct node* previous;
} Node;

Node* add_to_front(char* word, Node* head);
void print(Node* head);
void menu();
Node* remove_from_front(Node* head);
Node* add_to_back(Node* head, char* word);
Node* remove_from_back(Node* head);

int main(void){
	int choice=0;
	//Node* head=NULL;
	char* word;
	while(choice != -1){
		printf("Enter '1' to add a word to the sentence\n");
		printf("Enter '2' to undo\n");
		printf("Enter '3' to redo\n");
		printf("Enter '-1' to exit:");
		scanf("%d", &choice);

		if(choice == 1){
			printf("Enter a word to add to the document: \n");
			word = malloc(sizeof(char) * MAX);
			scanf(" %s", word);
		}
		if(choice == 2){


		}
		if(choice == 3){


		}
	}

	//remove_from_back(head);

	return 0;
}

/*Node* add_to_front(char* word, Node* head){




}*/

/*void print(Node* head){


  }*/

/*Node* remove_from_front(Node** head){


}*/

Node* add_to_back(Node* head, char* word){








return head;
}

Node* remove_from_back(Node* head){
	Node* currentPtr;
	Node* previousPtr;
	previousPtr = NULL;

	for(currentPtr = head; currentPtr != NULL; previousPtr = currentPtr){
		if(currentPtr->word){
			if((previousPtr = NULL))
				head = currentPtr->next;
			}else{
				previousPtr->next = currentPtr->next;
			}
	}
	free(currentPtr);
return head;
}
