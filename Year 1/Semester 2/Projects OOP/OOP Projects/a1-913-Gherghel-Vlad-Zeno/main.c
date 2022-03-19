#include <stdio.h>

/// Computes the factorial of a number
/// \param x The number that will have it's factorial computed (integer)
/// \return An integer representing the factorial of the given number
int factorial(int x){
    if(x < 0){
        printf("Can't calculate the factorial of a negative number!\n");
        return 1;
    }

    int p = 1;
    int i;
    for(i=x;i>=1;i--)
        p = p * i;
    return p;
}

/// Computes the combination of m things taken k at a time
/// \param m Number of things
/// \param k Number of times takes
/// \return An integer representing the result of the combination
int combination(int m, int k){
    return (factorial(m)/(factorial(k)*factorial(m-k)));
}

/// Creates the Pascal Triangle with n rows and prints it in console
void pascal_triangle(){
    int i, j; //iterator
    int m =1; // current line
    int k = 0; // position of number on the line
    int n; // n represents the number of rows of the Pascal Triangle

    printf("Number of rows for pascal triangle:");
    scanf("%d", &n);

    int number_of_spaces = n; // used for spacing before writing the first number of a row

    for(m=0;m<n;m++){
        // creating the spaces for better reading
        for(j=0;j<number_of_spaces;j++){
            printf(" ");
        }
        // creating the pascal triangle numbers
        for(k=0;k<=m;k++)
            printf("%d ", combination(m, k));

        number_of_spaces -= 1;
        printf("\n");
    }
}

/// Checks if a number is a prime one or not
/// \param x The integer to be checked
/// \return 1 if it is a prime number, 0 if it isn't
int is_prime(int x){
    if(x == 2) return 1;
    if(x <= 1 || x%2 == 0) return 0;

    int i;
    for(i = 3;i*i<=x;i=i+2){
        if(x%i==0)
            return 0;

    }

    return 1;

}

/// Reads n integers and saves them in a vector
/// \param v The vector where the values will be saved
/// \param n The number of elements to be read
void read_vector(int v[], int n){
    int i=0;

    for(i=0;i<n;i++){
        printf("v[%d]=", i);
        scanf("%d", &v[i]);
    }
}

/// Computes the longest prime subsequence from a given sequence of numbers
void longest_prime_subsequence(){
    int n, max_l = 0, current_length; // dimensions
    int i, j; // iterators
    int v[100], res[100], current_vector_of_primes[100]; // vectors
    printf("Numarul de elemente:");
    scanf("%d", &n);

    read_vector(v, n);

    current_length = 0;
    for(i=0;i<n;i++){
        if(is_prime(v[i]) == 1){
            // number is prime case
            current_vector_of_primes[current_length++] = v[i];
        }
        else{
            // not a prime number
            if(current_length > max_l){
                // found a better result
                for(j=0;j<current_length;j++)
                    res[j] = current_vector_of_primes[j];
                max_l = current_length;

            }
            current_length = 0;
        }
    }

    // one last check after everything is done
    if(current_length > max_l){
        // found a better result
        for(j=0;j<current_length;j++)
            res[j] = current_vector_of_primes[j];
        max_l = current_length;

    }



    printf("Longest prime subsequence is: ");
    for(i=0;i<max_l;i++) {
        printf("%d ", res[i]);
    }
    printf("\n");
}

/// Computes and shows all the first n pairs of twin numbers (pairs of prime numbers that have the absolute difference 2)
void n_twin_pairs(){
    int i = 3, k=0, n;

    printf("Number of twin pairs to generate:");
    scanf("%d", &n);

    while(k<n){
        if(is_prime(i) && is_prime(i+2)) {
            printf("{%d, %d} ", i, i + 2);
            k++;
        }
        i= i+2;
    }
    printf("\n");
}



/// Main function of the program
/// \return 0, for good exit
int main() {
    int user_command = -1;
    int n;

    setbuf(stdout, 0);
    while (1) {
        printf("1 Pascal triangle with n rows.\n2 Longest subsequence of prime numbers.\n3 N twin numbers.\n0 Exit\n");
        printf("Number of command (1/2/3/0):");
        scanf("%d", &user_command);

        // exit when the user types 0
        if (user_command == 0) {
            break;
        }

        // cases of the console menu
        switch (user_command) {
            case 1:
                // Pascal triangle case
                pascal_triangle();
                break;
            case 2:
                // prime subsequence of numbers
                longest_prime_subsequence();
                break;
            case 3:
                // twin numbers case
                n_twin_pairs();
                break;
            default:
                printf("Incorrect command. Try again.\n");
                break;
        }
    }
    return 0;
}