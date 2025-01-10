#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void countingSort(int * list, int len);
void quickSort(int * list, int len);

void countingSort(int * list, int len)
{
	
	int * cpy_list = malloc(sizeof(int)*len);
	int greatest = 0;

	for (int i = 0; i < len; i++)
	{
		cpy_list[i] = list[i];
		if (list[i] > greatest)
			greatest = list[i];
	}

	int * index = malloc(sizeof(int) * (greatest+1));
	memset(index, 0, (greatest+1) * sizeof(int));

	for (int i = 0; i < len; i++)
	{
		index[list[i]] = index[list[i]] + 1;
	}

	for (int i = 1; i <= greatest; i++)
	{
		index[i] += index[i - 1];
        }
	
	for (int i = len - 1; i >= 0; i--)
	{
		list[index[cpy_list[i]] - 1] = cpy_list[i];
		index[cpy_list[i]]--;
	}

	free(index);
	free(cpy_list);
}

void quickSort(int * list, int len)
{
	int pivot = list[len-1];
	int i = 0;
	int j = -1;
	int temp = 0;
	int * first_half = 0;
	int * second_half = 0;

	for (i = 0; i < len; i++)
	{
		if (list[i] <= pivot)
		{
			j++;
			temp = list[i];
			list[i] = list[j];
			list[j] = temp;
		}
	}

	first_half = list;
	second_half = list + j + 1;
	
	if (len >= 2)
	{
		quickSort(first_half, j);
		quickSort(second_half, i-j-1);
	}
}
