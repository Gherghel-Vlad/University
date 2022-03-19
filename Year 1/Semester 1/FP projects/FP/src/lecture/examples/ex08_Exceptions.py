"""
Created on Oct 25, 2016

@author: Arthur

Part of this code is taken from:
    https://docs.python.org/3/tutorial/errors.html
"""

"""
    Try to enter various (non-integer) values at the prompt given by the code snippet below 
"""

# while True:
#     try:
#         x = int(input("Please enter a number: "))
#         break
#     except ValueError:
#         print("Oops!  That was no valid number.  Try again...")


'''
    Try running the program below, and see what happens on different inputs
    
    NB! 
        This is not a correct way to implement error handling, it's just example code :)
'''
end = False
while not end:
    try:
        val = input("T - TypeError, V - ValueErorr, K - KeyError, 0 - Exit")

        if val.lower() == 't':
            raise TypeError("Well this is a type error!")
        elif val.lower() == 'k':
            raise KeyError("Your program just raised a key error!")
        elif val.lower() == 'v':
            raise ValueError("value error!")
        else:
            end = True
    except KeyError as ke:
        print("There was a " + str(type(ke)) + " " + str(ke))
    except ValueError as ve:
        print("There was a ValueError")
    except:
        print("There was an exception that was not handled above!")
    else:
        print("There was no error")
