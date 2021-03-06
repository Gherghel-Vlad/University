"""
Created on Dec 7, 2016

@author: Arthur
"""
import timeit
from texttable import Texttable


def hanoi(n, x, y, z):
    """
    n - number of disks on the x stick
    x - source Stick
    y - destination stick
    z - intermediate stick
    """
    if n == 1:
        return
    hanoi(n - 1, x, z, y)
    hanoi(n - 1, z, y, x)


def hanoi_verbose(n, x, y, z):
    """
    n - number of disks on the x stick
    x - source Stick
    y - destination stick
    z - intermediate stick
    """
    if n == 1:
        print("Disk 1 from ", x, " to ", y)
        return
    hanoi(n - 1, x, z, y)
    print("Disk ", n, " from ", x, " to ", y)
    hanoi(n - 1, z, y, x)


'''
    NB!
    To run the function below, you must have installed the texttable component from:
    https://github.com/foutaise/texttable
'''


def build_result_table():
    table = Texttable()
    table.add_row(['disks', 'seconds'])
    for term in range(10, 26):
        t1 = timeit.default_timer()
        hanoi(term, "X", "Y", "Z")
        t2 = timeit.default_timer()
        table.add_row([term, t2 - t1])
    return table


print(build_result_table().draw())

'''
    In case you cannot run the example, this is what it is supposed to look like:
    
    +-------+-------------+
    | Disks | Miliseconds |
    +-------+-------------+
    | 10    | 0           |
    +-------+-------------+
    | 11    | 0           |
    +-------+-------------+
    | 12    | 1           |
    +-------+-------------+
    | 13    | 1           |
    +-------+-------------+
    | 14    | 3           |
    +-------+-------------+
    | 15    | 5           |
    +-------+-------------+
    | 16    | 10          |
    +-------+-------------+
    | 17    | 19          |
    +-------+-------------+
    | 18    | 39          |
    +-------+-------------+
    | 19    | 76          |
    +-------+-------------+
    | 20    | 154         |
    +-------+-------------+
    | 21    | 312         |
    +-------+-------------+
    | 22    | 614         |
    +-------+-------------+
    | 23    | 1223        |
    +-------+-------------+
    | 24    | 2440        |
    +-------+-------------+
    | 25    | 4891        |
    +-------+-------------+

    NB!
    0 miliseconds is not really 0, it's just too short to measure accurately
'''
