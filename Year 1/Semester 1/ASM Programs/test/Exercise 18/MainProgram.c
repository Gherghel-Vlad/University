
#include <stdio.h>

void write_number_in_file(int number);


int main()
{
	/*
	Read a string of unsigned numbers in base 10 from keyboard. Determine the minimum value
	of the string and write it in the file min.txt (it will be created) in 16 base.
	*/

	int sir[50];
	char filename[50] = "min.txt\0";
	int i = 0;
	int minimumNumber = -1;
	printf("Eneter the numbers (the array must end with -1): ");

	while (1) {
		scanf_s("%d", &sir[i]);

		if (minimumNumber == -1) {
			minimumNumber = sir[i];
		}
		else {
			if (sir[i] != -1 && minimumNumber > sir[i])
				minimumNumber = sir[i];
		}

		if (sir[i] == -1) {
			break;
		}
		i++;
	}

	if (minimumNumber == -1)
		minimumNumber = 0;

	write_number_in_file(minimumNumber);

	return 0;

}
