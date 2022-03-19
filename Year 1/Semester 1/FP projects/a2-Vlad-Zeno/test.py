class BagIterator:

    def __init__(self, bag):
        self.__bag = bag
        self.__current = 0

    def first(self):
        self.__current = 0

    def valid(self):
        return self.__current < self.__bag.size()

    def getCurrent(self):
        if self.valid():
            raise ValueError()

        return self.__bag._Bag__elems[self.__current]

    def next(self):
        if self.__current == self.__bag.size():
            raise ValueError()

        Self.__current += 1
