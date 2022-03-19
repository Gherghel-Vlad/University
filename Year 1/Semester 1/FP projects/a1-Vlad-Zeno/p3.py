#
# Implement the program to solve the problem statement from the third set here
#

# Exercise 14 set 3

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


def main():
    n = int(input("Please give which position from the sequence you want to see the number of: "))
    i = 1
    while True:
        if prime(i) or i==1:
            n -= 1
            if n==0:
                print("Found it: ", i)
        else:
            for j in range(2, int(i/2)+1):
                if prime(j):
                    for k in range(0,j):
                        n-=1
                        if n==0:
                            print("Found it: ", j)
                            break
                    if n==0:
                        break
                if n==0:
                    break
        if n==0:
            break
        i+=1



main()








