"""
Created on Sep 23, 2016

@author: Arthur
"""

"""
    Print a message to the console
"""
print("Hello world!")

"""
    Read from the console
"""
a = input("Enter the first number: ")
b = input("Enter the second number: ")

"""
    NB!
    What is printed out and why?
"""
print(a + b)

# This is a line comment

"""
    NB!
    What does this do?
"""
x = int(a)
y = int(b)

print(x + y)

"""
    NB!
    This is all very confusing... how do I know what is what? 
"""
print("this should be a string - ", type(a))
print("and this is an integer -", type(x))