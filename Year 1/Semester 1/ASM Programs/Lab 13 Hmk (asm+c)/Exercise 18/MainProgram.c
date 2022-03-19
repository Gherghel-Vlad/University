
#include <stdio.h>

int determine_minimum_from_array(int array[], int length);
void write_number_in_file(int number);


int main()
{
	/*
	Read a string of unsigned numbers in base 10 from keyboard. Determine the minimum value
	of the string and write it in the file min.txt (it will be created) in 16 base.
	*/

	int sir[50];
	int i = 0;
	int minimumNumber = 0;
	printf("Enter the numbers (the array must end with -1): ");

	while (1) {
		scanf("%d", &sir[i]);

		if (sir[i] == -1) {
			break;
		}
		i++;
	}
	minimumNumber = determine_minimum_from_array(sir, i);

	write_number_in_file(minimumNumber);

	return 0;

}
