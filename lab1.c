/*
 * Pawprint: avc9wb
 * Name: Abhiram Chavakula
 * Section: F
 * Lab Code: FirstDay 
*/


#include <stdlib.h>
#include <stdio.h>

/*Funtion Prototypes*/

double* read_file(char* filename, double*, int length);
double find_min(double* array, int length);
double find_max(double* array, int length);
void write_to_file(char* filename, double* array, int length);
double median(double* array, int length);
double mode(double* array, int length);

int main(int argc, char** argv){

	if(argc<3){
		printf("\nInsufficient arguments\n");
		return 0;
		}
	int length=atoi(argv[1]);
	double min;
	double max;
	 double *array=malloc(sizeof(double)*length);
	read_file(argv[2],array, length);
	if(length==0){
		printf("\nUnable to open input file\n");
	}
	min=find_min(array, length);
	max=find_max(array, length);
	printf("min: %lf\nmax: %lf\n",min, max);
	write_to_file(argv[3], array, length);
return 0;
}

/*
 * Parameters:
 * filename-The name of the input file
 * length-The number of items in the input file
 *
 * Return:
 * An array of doubles with 'length' number of elements,
 * NULL if the file failed to open or if the length is <=0.
 */

double* read_file(char* filename,double* array, int length){
	int i=0;
	FILE* file=fopen(filename, "r");

	if(file==NULL){
		return 0;
	}
	
	for(i=0; i<length; i++){
		fscanf(file, "%lf", array+i);
	}
	
	fclose(file);
	return 0;
}

/*
 * Parameters:
 * array- An array of doubles
 * length- The size of the array
 *
 * Return:
 * The smallest value in the array
 */
double find_min(double* array, int length){
	int i;
	double num=9;

	for(i=0; i<length; i++){
		if(*(array+i)<num){
			num=*(array+i);
				}
				}
return num;
}	

/*
 * Parameters:
 * array- An array of doubles
 * length- The size of the array
 *
 * Return:
 * The smallest value in the array
 */
double find_max(double* array, int length){
	int i;
	double num=9;

	for(i=0; i<length; i++){
		if(*(array+i)>num){
			num=*(array+i);
				}
				}
return num;
}

/*
 * Parameters:
 * filename: The name of the output file to write to 
 * array - An array of doubles
 * length - The length of the array
 *
 * Return: None
 *
 * This function will write the values of the array
 * to the file backwards. So the last item at 
 * array[length - 2] the second, etc
 */

void write_to_file(char* filename, double* array, int length){
	int l=length;
	int begin=l-l-1;
	double temp;
	while(l>begin){
		temp=*(array+begin);
		*(array+begin)=*(array+l);
		*(array+l)=temp;
		begin++;
		l--;
	}
	int i=0;
	FILE* file=fopen(filename, "w");
	for(i=0; i<length; i++){
		fprintf(file, "%.2lf\n", *(array+i));
	}
	fclose(file);
	}

double median(double* array, int length){
	double temp;
	int i, j;
	for(i=0; i<length-1; i++){
		for(j=i+1; j<length; j++){
			if(*(array+j) < *(array+i)){
			temp= *(array+i);
			*(array+i)= *(array+j);
			*(array+j)= temp;
			}
		}
	}
	if(length%2==0){
		return((*(array+(length/2))+(*(array+(length/2-1))) / 2.0));
	} else {
		return(*array+(length/2));
		}
	}

double mode(double* array, int length){
	double number = array[0];
	int i;
	int mode = number;
	int count = 1;
	int countMode = 1;
	
	for(i=1; i<length; i++){
		if(*(array+i) == number){
			countMode++;
		}
		else
		{
			if(count > countMode)
		{
			countMode = count;
			mode = number;
		}
			count = 1;
			number = *(array+i);
		}
	}
}



