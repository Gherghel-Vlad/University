
#include <stdio.h>

int determine_minimum_from_array(int array[], int length); 
void write_number_in_file(char filename[], int number);


int main()
{
	/*
	Read a string of unsigned numbers in base 10 from keyboard. Determine the minimum value
	of the string and write it in the file min.txt (it will be created) in 16 base.
	*/

	int sir[50], length;
	int i = 0;
	int minimumNumber = 0;
	printf("Enter the numbers: ");

	while (1) {
		scanf_s("%d", &sir[i]);
		if (sir[i] == -1) {
			break;
		}
		i++;
	}
	length = i;

	minimumNumber = determine_minimum_from_array(sir, length);

	write_number_in_file(minimumNumber);

	return 0;

}
