#include <stdlib.h>
#include <string.h>
#include <stdio.h>

void countingSort(int * list, int len);
void quickSort(int * list, int len);

int main()
{
	int list[] = {9, 3, 1, 7, 7, 0, 2};

	countingSort(list, sizeof(list)/sizeof(int));

	for (int i = 0; i < sizeof(list)/sizeof(int); i++) printf("%d, ", list[i]);
	printf("\n");

	return 0;
}

void countingSort(int * list, int len)
{
	int i = 0;
	int largest = 0;
	int i_position = 0;

	int * list_cpy = malloc(sizeof(int) * len);
	
	for (i = 0; i < len; i++)
	{
		if (list[i] > largest)
			largest = list[i];
		
		list_cpy[i] = list[i];
	}

	int * frequency = malloc(sizeof(int) * (largest + 1));
	memset(frequency, 0, (largest + 1) * sizeof(int));

	for (i = 0; i < len; i++)
	{
		frequency[list[i]] = frequency[list[i]] + 1;
	}


	for (i = 1; i <= largest; i++)
	{
		frequency[i] += frequency[i-1];
	}

	for (i = len - 1; i >= 0; i--)
	{
		i_position = frequency[list_cpy[i]] - 1;
		list[i_position] = list_cpy[i];
		frequency[list_cpy[i]] = frequency[list_cpy[i]] - 1;
	}

	free(frequency);
	free(list_cpy);
}
