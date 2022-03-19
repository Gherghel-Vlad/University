
#include <stdio.h>

void concatDecimals(char result[], char str1[], char str2[]);

/*
Two strings containing characters are given. Calculate and display the result of the concatenation 
of all characters of type decimal number from the second string, and then followed by those from the 
first string, and vice versa, the result of concatenating the characters from the first string after
those from the second string.
*/

int main()
{
	char R[101] = ""; // result string
	char S1[50] = ""; // first string 
	char S2[50] = ""; // second string

	printf("First string: ");
	scanf("%s", S1); // read first string
	printf("Second string: ");
	scanf("%s", S2); // read second string 
	
	concatDecimals(R, S2, S1); // call the asm function
	printf("Decimals from the second string + decimals from the first string: %s\n", R);

	concatDecimals(R, S1, S2); // call the asm function 
	printf("Decimals from the first string + decimals from the second string: %s\n", R);

	
	return 0;
}

