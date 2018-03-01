/*
 * Pawprint:avc9wb
 * Name: Abhiram Chavakula
 * Student #14207755
 */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>

/*Structure Variables 
 *
 * 
 * license plate - the license plate of the car
 * parking spot - the spot the car is parked in
 * num tickets - the number of tickets that have been issued to that car
 * time left - the amount of time (in minutes) remaining on that  car's parking spot
 */

typedef struct car {
	char *license_plate;
	int parking_spot;
	int num_tickets;

	int time_left;
} Car;

// LICENSEPLATELENGTH - the maximum size of the license plate

#define LICENSEPLATELENGTH 10

/*Function Prototypes*/

Car* import_cars(char* filename, int numCars);
void adjust_cars(Car* garage, int numCars);
int find_car(Car* garage, int spot, int numCars);
void add_time(Car* garage, int numCars);
void free_garage(Car* garage, int numCars);
void check_car(Car* garage, int numCars);
void print_to_file(char* filename, Car* garage, int numCars);

int main(int argc, char* argv[]){
	if(argc!=3){
		printf("Incorrect input\nCorrect usage ./a.out <numCars> <input/output file>");
		return 0;
	}

	int choice;
	int numCars=atoi(argv[1]);
	Car* garage=import_cars(argv[2], numCars);	
	while(choice != -1){
		printf("To add time enter '1'\n");
		printf("To check time enter '2'\n");
		printf("To exit enter '-1'\n");
		printf("Please enter your choice: ");
		scanf("%d", &choice);

		if(choice==1){
			add_time(garage, numCars);
		}
		if(choice==2){
			check_car(garage, numCars);	
		}

	}

	adjust_cars(garage, numCars);
	print_to_file(argv[2], garage, numCars);	
	free_garage(garage, numCars);	
	return 0;
}

/* Parameters
 **
 ** filename - the name of the input file
 ** numCars - the number of cars in the garage
 **
 ** Return - An array full of cars
 **
 **/
Car* import_cars(char* filename, int numCars){
	FILE *file;
	Car *garage=malloc(sizeof(Car)*numCars);
	int i=0;
	file=fopen("input.txt", "r");
	for(i=0; i<numCars; i++){
		garage[i].license_plate=malloc(sizeof(char)*numCars);
		fscanf(file, "%s",  garage[i].license_plate);
		fscanf(file, "%d",  &garage[i].parking_spot);
		fscanf(file, "%d",  &garage[i].num_tickets);
		fscanf(file, "%d",  &garage[i].time_left);		
	}
	fclose(file);
	return garage;

}

/* Parameters
 **
 ** garage- the array of cars
 ** numCars - the number of cars in the garage
 **
 ** This function will be called after the user exits
 ** the system. It will subtract 30 minutes from the
 ** time_left on each car. If the time left is <= 0 after subtraction, a
 ** ticket will be added to the car and the time_left
 ** will be reset to 60.
 **
 **/

void adjust_cars(Car* garage, int numCars){
	int i=0;
	for(i=0; i<numCars; i++){
		garage[i].time_left=garage[i].time_left-30;
		if(garage[i].time_left<=0){
			garage[i].time_left=60;			
			garage[i].num_tickets=garage[i].num_tickets+1;
		}
	}
}
/* Parameters
 **
 ** garage- the array of cars
 ** numCars - the number of cars in the garage
 **
 ** This function will be called after the user exits
 ** the system. It will subtract 30 minutes from the
 ** time_left on each car. If the time left is <= 0 after subtraction, a
 ** ticket will be added to the car and the time_left
 ** will be reset to 60.
 **
 **/
int find_car(Car* garage, int spot, int numCars){
	int i=0;
	for(i=0; i<numCars; i++){
		if(garage[i].parking_spot==spot){
			return i;

		}
	}
	return -1;

}

/* Parameters
 **
 ** garage - the array of cars
 ** numCars- The number of cars in the garage
 **
 ** description - this function allows the user
 ** to add time (in minutes) for the parking spot specified.  
 ** It may be beneficial to use the
 ** find car function inside this function.
 **
 **/
void add_time(Car* garage, int numCars){
	int lot, time, space;
	printf("Enter the parking spot of the car: ");
	scanf("%d", &lot);
	space=find_car(garage, lot, numCars);
	if(space==-1){
		printf("There is no car parked in that spot\n");
	}
	else{
		printf("Enter the amount of time you would like to add: ");
		scanf("%d", &time);
		garage[space].time_left=garage[space].time_left + time;
	}
}

/*Parameters
 **
 ** garage - the array of cars
 ** numCars - the number of cars in the garage
 **
 ** discription - this function will free the
 ** space allocated for the cars. Be sure to free
 ** all the memory that applies.
 **
 **/
void free_garage(Car* garage, int numCars){
	int i=0;
	for(i=0; i<numCars; i++){
		free(garage[i].license_plate);
	}
	free(garage);
}

/*Parameters
 **
 ** garage - the array of cars
 ** numCars - the number of cars in the garage
 **
 ** discription - This function will show the
 ** user the information stored in the garage 
 ** struct on the car in the spot specified. It may be beneficial
 ** to call the find_car function inside this function
 **
 **/

void check_car(Car* garage, int numCars){
	int lot, space;
	printf("Enter the spot the car is parked in: ");
	scanf("%d", &lot);
	space=find_car(garage, lot, numCars);
	if(space==-1){
		printf("There is no car parked in that space\n");
	}
	else{
		printf("License plate: %s\n", garage[space].license_plate);
		printf("Parking spot: %d\n", garage[space].parking_spot);
		printf("Number of Tickets: %d\n", garage[space].num_tickets);
		printf("Time left: %d\n", garage[space].time_left);
	}
}

/* Parameters
 **
 ** filename - the name of the output file
 ** garage - the array of cars
 ** numCars - the number of cars in the garage
 ** 
 ** discription - this function will output the final
 ** array of cars to the file. This means after the cars
 ** have been updated with the time adjustments and
 ** tickets from an above function. 
 **
 **/

void print_to_file(char* filename, Car* garage, int numCars){
	int i=0;
	FILE* file=fopen(filename, "w");
	for(i=0; i<numCars; i++){
		fprintf(file, "%s\n",  garage[i].license_plate);
		fprintf(file, "%d ",  garage[i].parking_spot);
		fprintf(file, "%d ",  garage[i].num_tickets);
		fprintf(file, "%d\n",  garage[i].time_left);
	}
	fclose(file);
}
