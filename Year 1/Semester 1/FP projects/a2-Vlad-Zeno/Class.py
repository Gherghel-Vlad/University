

class SparseMatrix:
    def __init__(self, dim_i, dim_j):
        self._dim_i = dim_i
        self._dim_j = dim_j
        self._matrix_list_values = []
        self._matrix_list_positions = []

    def set(self, i, j, k):
        if i < 0 or i > self._dim_i - 1 or j < 0 or j > self._dim_j -1:
            raise ValueError("Invalid coordinates.")
        for r in range(len(self._matrix_list_positions)):
            if self._matrix_list_positions[r] == [i, j]:
                self._matrix_list_values[r] = k
                return
        self._matrix_list_positions.append([i, j])
        self._matrix_list_values.append(k)

    def get(self, i, j):
        for r in range(len(self._matrix_list_positions)):
            if self._matrix_list_positions[r] == [i, j]:
                return self._matrix_list_values[r]

    def __str__(self):
        string = ""
        for i in range(self._dim_i):
            for j in range(self._dim_j):
                ok = 0
                for r in range(len(self._matrix_list_positions)):
                    if self._matrix_list_positions[r] == [i, j]:
                        string += str(self._matrix_list_values[r]) + " "
                        ok = 1
                        break
                if ok == 0:
                    string += "0 "
            string += "\n"

        return string

# Initialise a 3x3 sparse matrix
m1 = SparseMatrix(3,4)
# Value at [1,1] is 2
m1.set(1,1,2)
# Value at [2,2] is 4
m1.set(2,2,4)
# Prints
# 0 0 0
# 0 2 0
# 0 0 4
print(m1)
# Prints '<class 'ValueError'>'
try:
    m1.set(3,3,99)
except Exception as e:
    print(type(e))
# Update value at [1,1] with 2 + 1
m1.set(1,1,m1.get(1,1)+1)
# Prints
# 0 0 0
# 0 3 0
# 0 0 4
print(m1)