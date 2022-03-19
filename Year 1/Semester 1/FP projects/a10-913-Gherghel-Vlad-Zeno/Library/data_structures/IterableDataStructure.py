from Library.domain.client import Client


class IterableDataStructure:
    def __init__(self):
        self._list = []

    @property
    def list(self):
        return self._list

    def __getitem__(self, index):
        """
        Gets the item that s on the position the index indicates to
        :param index: The position in the list (list starting from 0) (int)
        :return: The value in the list at the position indicated by the index
        """
        return self._list[index]

    def __setitem__(self, index, value):
        """
        Sets the item on the index indicated (if it's not outside the bounds of the list)
        :param index: The position in the list (list starting from 0) (int)
        :param value: The value that's going to be set on that position
        :return: -
        """
        self._list[index] = value

    def __delitem__(self, index):
        """
        Deletes the item from the specified index
        :param index: The position in the list (list starting from 0) (int)
        :return: -
        """
        del self._list[index]

    def __len__(self):
        """
        Returns the number of elements in the data instance
        :return: The number of elements in the iterable data structure
        """
        return len(self._list)

    def __iter__(self):
        """
        Creates a generator for iteration
        :return: A generator for the list
        """
        # yield implementation
        for elem in self._list:
            yield elem

        # "normal implementation"
        # self.index = 0
        # return self

    # !! uncomment this if you want to use the normal implementation
    # def __next__(self):
    #     """
    #     The function that will return the next element in the iteration
    #     :return: An element form the list (the next one )
    #     """
    #     try:
    #         item = self._list[self.index]
    #     except Exception:
    #         raise StopIteration()
    #     self.index += 1
    #     return item

    def append(self, value):
        """
        Adds a new value to the end of the list
        :param value: The value to be added
        :return: -
        """
        self._list.append(value)


def gnome_sort(list, function):
    """
    Implementing the Stupid sort (gnome sort/"Garden Gnome sorting his flowers") :))
    It sorts the list that you provide using the function passed (the one used to indicate the order between 2 elements)
    :param list: the list that s going to be sorted
    :param function: The function that indicates the order between 2 elements
    :return: -
    """

    index = 0
    length_of_list = len(list)

    while index < length_of_list:
        if index == 0:
            index += 1
        if function(list[index], list[index - 1]):
            index += 1
        else:
            list[index], list[index - 1] = list[index - 1], list[index]
            index -= 1


def filter_list(list, function):
    """
    Filters the elements in the list using the function given
    :param list: The list that's going to be filtered
    :param function: The function used in the decision making of the filtration
    :return: The resulted list after the filtration
    """
    new_list = []

    for elem in list:
        if function(elem):
            new_list.append(elem)

    return new_list


# data = IterableDataStructure()
# data.append(Client("123", "asd"))
# data.append(Client("122", "qwer"))
# data.append(Client("121", "rewd"))
# data.append(Client("11abf", "agfds"))

# print(str(data))
# print(str(data[1]))
# data[2] = Client("111", "rada")
# print(str(data[2]))
# del data[2]
# print(str(data[2]))
#
#
# for elem in data:
#     print(elem)
# gnome_sort(data.list, lambda a, b: a.client_id > b.client_id)
# for elem in data:
#     print(elem)
