/*
 * Name: Abhiram Chavakula
 * Pawprint:avc9wb
 * Lab code: random number generator
 * Student #14207755
 */


#include<stdio.h>
#include<stdlib.h>
#include<time.h>

int random_number();
void display_option();
int check_guess(int);
int throw_dice();
int lucky_seven(int, int);
int sum;


int main ()
{
int guess, a;

srand(time(NULL));
display_option();
scanf("%d", &guess);

while (check_guess(guess)==0)
{
printf("Invalid choice\n");
display_option();
scanf("%d",&guess);
}


sum=throw_dice();

a=lucky_seven(guess, sum);
if (a==1)
{
printf("You win! Your guess is correct, the sum of the dice is %d\n", sum);
}

else
{
printf("You lose! Your guess is incorrect, the sum of the dice is %d\n", sum);
}




//int x;

//x=random_number();

//printf("\n Random number is %d \n", x);

return 0;
}


/*int random_number()
{

int num;
num= rand()%10;
return num;
}*/

void display_option()
{
printf("Enter your guess (1) Lucky 7 (2) Above 7 (3) Below 7:\n Please select an option:");
}

int check_guess(int guess)
{
if (guess<1 || guess>3)
{
return 0;
}
else 
return 1;
}

int throw_dice()
{
int x, y;
x=rand()%6+1;
y=rand()%6+1;

sum=x+y;

return sum;
}

int lucky_seven(guess, sum)
{

switch (guess)
{

case 1: 

if (sum==7)
{

return 1;
} 
else
{
return 0;
}

break;

case 2:

if (sum>7)
{

return 1;
}
else
{
return 0;
}

break;

case 3:

if (sum<7)
{

return 1;
}
else
{
return 0;
}

break;

return 1;

}
return 0;
}



































