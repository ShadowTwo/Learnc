#include <stdio.h>
#include <stdlib.h>
#include <errno.h>
#include <string.h>

void die(const char *messages)
{
	if (errno) { perror(messages);}
	else{ printf("Error: %s\n", messages);}
	exit(1);
}

//create a fake type. this is a function pointer
typedef int (*compare_cb) (int a, int b);

//bubble sort
int *bubble_sort(int *numbers, int count, compare_cb cmp)
{
	int temp = 0;
	int i = 0;
	int j = 0;
	int *target = malloc(count * sizeof(int));

	if (!target) {die("Line 24, Target Mem Allocation Error.");}
	
	memcpy (target, numbers, count * sizeof(int));
	
	for (i = 0; i < count; i++)
	{
		for (j = 0; j <count -1; j++)
		{
			if (cmp(target[j],target[j+1])>0)
			{
				temp = target[j];
				target[j] = target[j+1];
				target[j+1] = temp;
			}	
		}//End of Innter Loop (j)
	}//Endof OuterLoop (i)
	
	return target;
}//End of BubbleSort

//different compair functions
//Normal
int sorted_order (int a, int b) {return a - b;}
//Reverse
int reverse_order (int a, int b) {return b - a;}
//strance 
int strange_order (int a, int b)
{
	if (a == 0 || b == 0) {return 0;}
	else {return a % b;}
}

//test sort
void test_sort(int *numbers, int count, compare_cb cmb, char *label)
{
	int i = 0;
	int *sorted = bubble_sort(numbers, count, cmb);
	
	if (!sorted) {die("Failed to Sort. Line 62");}
	
	printf("%s: ", label);
	for (i = 0; i < count; i++) {printf("%d ", sorted[i]);}
	printf("\n");
	
	free(sorted);
}//End of Test_Sort

int main (int argc, char *argv[])
{
	if (argc < 2 ){die("USAGE ex18 1 2 3 4");}
	
	int count = argc - 1;
	int i = 0;
	
	char **inputs = argv + 1;
	int *numbers = malloc(sizeof(int) * count);
	
	if (!numbers) {die("Error creating numebrs. Line 81");}
	
	for (i=0; i < count; i++){numbers[i] = atoi(inputs[i]);}
	
	test_sort(numbers, count, sorted_order, "Sorted");
	test_sort(numbers, count, reverse_order, "Reversed");
	test_sort(numbers, count, strange_order, "Strange");
	
	free(numbers);
	
	return 0;

}//end of main

