/*
Name: Sonu Chavakula
Pawprint: avc9wb
Section: F
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define ROUNDS 3
#define MAX_NAME 25

typedef struct player{
	char* Full_Name;
	int player_ID;
	double batting_rating;
	double defense_rating;
	double pitching_rating;
} Player;

typedef struct node{
	Player player;
	struct node* next;
} node_t;

//Function Prototypes
node_t* Generate_Draft_List(char* File, int number_of_players);
void print_list(node_t* head);
node_t* add_node(node_t* head_of_list, Player playa);
void Draft(node_t** head_a, node_t** head_b, node_t** head_c, node_t** draft_list, char* team_a, char* team_b, char* team_c);
double computeAverage(node_t* Team_List);
void Free_List(node_t* linked_list);

int main(int argc, char* argv[]){
	if(argc > 6){
		printf("Incorrect input, please try again.\n");
	}
	int number_of_players=atoi(argv[1]);
	node_t* head=0;
	head = Generate_Draft_List(argv[2], number_of_players);
	printf("\nOutput for step 1:\n");
	print_list(head);
	node_t* head_a = NULL;
	node_t* head_b = NULL;
	node_t* head_c = NULL;
	Draft(&head_a, &head_b, &head_c, &head, argv[3], argv[4], argv[5]);

	node_t* current_a = head_a;
	node_t* current_b = head_b;	
	node_t* current_c = head_c;
	printf("\nOutout for step 2:\n");
	printf("\nTeam A:\n");
	print_list(current_a);
	printf("\nTeam B:\n");
	print_list(current_b);
	printf("\nTeam C:\n");
	print_list(current_c);	

	double teamA = computeAverage(head_a);
	printf("\nThe average for Team A is: %lf\n", teamA);
	double teamB = computeAverage(head_b);
	printf("\nThe average for Team B is: %lf\n", teamB);
	double teamC = computeAverage(head_c);
	printf("\nThe average for Team C is: %lf\n", teamC);
	printf("\nTherefore, the winner is Team C.\n");
	Free_List(head);
	Free_List(head_a);
	Free_List(head_b);	
	Free_List(head_c);

	return 0;
}

node_t* Generate_Draft_List(char* File, int number_of_players){
	FILE* filename=fopen(File, "r");
	node_t* head = NULL;



	if(File == NULL){
		printf("Error opening text file.\n");
	}

	int i = 0;
	while(i < number_of_players){
		Player* temp = malloc(sizeof(Player));
		temp->Full_Name=malloc(sizeof(MAX_NAME));
		fscanf(filename, "%s", temp->Full_Name);
		fscanf(filename, "%d", &(temp->player_ID));
		fscanf(filename, "%lf", &(temp->batting_rating));
		fscanf(filename, "%lf", &(temp->defense_rating));
		fscanf(filename, "%lf", &(temp->pitching_rating));
		head = add_node(head, *temp);
		i++;
	}


	fclose(filename);
	return head;
}

void print_list(node_t* head){

	while(head != NULL){

		printf("%s\n %d %.0lf %.0lf %.0lf\n", head->player.Full_Name, head->player.player_ID, head->player.batting_rating, head->player.defense_rating, head->player.pitching_rating);
		head  = head->next;
	}
}

node_t* add_node(node_t* head_of_list, Player playa){

	node_t* newPtr;
	node_t* currentPtr;
	node_t* previousPtr;

	newPtr = malloc(sizeof(node_t));

	if(newPtr != NULL){

		newPtr->player = playa;
		newPtr->next = NULL;
		previousPtr = NULL;
		currentPtr = head_of_list;

		while(currentPtr != NULL){
			previousPtr = currentPtr;
			currentPtr = currentPtr->next;
		}

		if(previousPtr == NULL){
			newPtr->next = head_of_list;
			head_of_list = newPtr;
			return head_of_list;
		}

		else{
			previousPtr->next = newPtr;
			newPtr->next = currentPtr;
			return head_of_list;
		}
		

	}
	else{
		printf("No memory available.\n");
	}
	return head_of_list;
}

void Draft(node_t** head_a, node_t** head_b, node_t** head_c, node_t** draft_list, char* team_a, char* team_b, char* team_c){

	FILE* taPtr = fopen(team_a, "r");
	FILE* tbPtr = fopen(team_b, "r");
	FILE* tcPtr = fopen(team_c, "r");
	int player_ID;
	int x = 1;
	printf("\n %d", x);

	while(x > 0){ 
		printf("\n %d", x);
		x = 0;
		if(!feof(taPtr)){
			int y = 0;
			x++;
			while(y == 0 && !feof(taPtr)){
				fscanf(taPtr, "%d", &player_ID);
				node_t* current = *draft_list;
				node_t* previous = NULL;
				while(current != NULL && current->player.player_ID != player_ID){
					previous = current;
					current = current->next;
				}
				if(current != NULL){
					y = 1;
					*head_a = add_node(*head_a, current->player);
					if(current == *draft_list){
						*draft_list = current->next;
					} 
					else{
						previous->next = current->next;
						current = NULL;
					}
					//free(current->player.Full_Name);
					//free(current);
				}
			}
			y = 0;
			while(y == 0 && !feof(tbPtr)){
				fscanf(tbPtr, "%d", &player_ID);
				node_t* current = *draft_list;
				node_t* previous = NULL;
				while(current != NULL && current->player.player_ID != player_ID){
					previous = current;
					current = current->next;
				}
				if(current != NULL){
					y = 1;
					*head_b = add_node(*head_b, current->player);
					if((current == *draft_list)){
						*draft_list = current->next;
					}
					else{
						previous->next = current->next;
					}
					//free(current->player.Full_Name);
					//free(current);
				}

			}
			y=0;
			while(y == 0 && !feof(tcPtr)){
				fscanf(tcPtr, "%d", &player_ID);
				node_t* current = *draft_list;
				node_t* previous = NULL;
				while(current != NULL && current->player.player_ID != player_ID){
					previous = current;	
					current = current->next;
				}
				if(current != NULL){
					y = 1;
					*head_c = add_node(*head_c, current->player);
					if((current == *draft_list)){
						*draft_list = current->next;
					}
					else{
						previous->next = current->next;
					}
					//free(current->player.Full_Name);
					//free(current);
				}
			}	
		}
	}
fclose(taPtr);
fclose(tbPtr);
fclose(tcPtr);
}


double computeAverage(node_t* Team_List){
	node_t* current = Team_List;

	double battingr = 0;
	double defenser = 0;
	double pitchingr = 0;
	int size = 0;

	while(current != NULL){
		size++;
		battingr += current->player.batting_rating;	
		defenser += current->player.defense_rating;
		pitchingr += current->player.pitching_rating;
		current = current->next;
	}

	double teamAverage = ((battingr + defenser + pitchingr)/(size * 3));
	return teamAverage;
}

void Free_List(node_t* linked_list){
	node_t* temp = NULL;

	while(linked_list != NULL){
		temp= linked_list;
		linked_list = linked_list->next;
		free(temp->player.Full_Name);
		free(temp);
	}

}
