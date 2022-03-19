#
# Implement the program to solve the problem statement from the second set here
#
# Exercise 7 set 2

def prime(n):
    """This function will verify if the parameter given to it is a prime number.
     If it is, it returns True, if it is not, it returns False."""
    if n<=1:
        return False
    else:
        if n == 2:
            return True
        else:
            if n%2 == 0:
                return False
            else:
                for i in range(3, int(n**0.5)+1, 2):
                    if n % i == 0:
                        return False
    return True


def print_result(p1):
    """
    Prints the result in the console
    :param p1: The first prime number
    :return:
    """
    print("The first twin prime numbers larger than the given number are: ", p1, p1 + 2)

def main():
    n = int(input("Please give a non-null natural number: "))
    # We simply start going from the next number bigger than the given number and search for
    # 2 prime number that have their subtraction 2
    p1 = n+1
    while True:
        if prime(p1) and prime(p1+2):
            print_result(p1)
            break
        else:
            p1 += 1

main()



