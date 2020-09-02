#include <stdio.h>
#include <stdlib.h>

void bubble_sort(int* list, const int n) {
	int i, j, temp;

	for (i = 0; i < n; i++) {
		for (j = 0; j < n - 1; j++) {
			if (list[j] > list[j + 1])
			{
				temp = list[j];
				list[j] = list[j + 1];
				list[j + 1] = temp;
			}
		}
	}

}

int main(int argc, char* argv[]) {

	if (argc != 2) {
		printf("Not enough arguments\n");
		return 1;

	}
	char* filename = argv[1];

	int MaxDataIDX = 10;
	int* InputData = (int*)malloc(sizeof(int) * MaxDataIDX);


	FILE* fin;
	int tempInt;
	int tempIter = 0;

	fin = fopen(filename, "r");
	while (fscanf(fin, "%d", &tempInt) != EOF) {
		InputData[tempIter++] = tempInt;

	}
	fclose(fin);

	printf("Input data: \n");
	for (int i = 0; i < MaxDataIDX; i++)
	{
		printf("%d ", InputData[i]);
	}
	printf("\n");

	bubble_sort(InputData, MaxDataIDX);

	printf("Output data: \n");

	for (int i = 0; i < MaxDataIDX; i++) {
		printf("%d ", InputData[i]);
	}
	printf("\n");

	FILE* fout;
	fout = fopen("OutputData.txt", "w");
	for (int i = 0; i < MaxDataIDX; i++) {
		fprintf(fout, "%d ", InputData[i]);

	}
	
	fprintf(fout, "\n");
	fclose(fout);
	free(InputData);
	return 0;

	
}
