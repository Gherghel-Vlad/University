def bubble_sort(arr):
    n = len(arr)
    for i in range(n - 1):
        for j in range(0, n - i - 1):
            if arr[j] > arr[j + 1]:
                aux = arr[j]
                arr[j] = arr[j + 1]
                arr[j + 1] = aux


arr = [1, 5, 3, 2, 4, 6, 9, 8, 2]

bubble_sort(arr)
print(arr)
