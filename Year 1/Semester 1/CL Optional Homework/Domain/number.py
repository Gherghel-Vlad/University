class Number:
    def __init__(self, number, base):
        self._number = str(number)
        self._base = base

    @property
    def number(self):
        return self._number

    @number.setter
    def number(self, value):
        self._number = value

    @property
    def base(self):
        return self._base

    @base.setter
    def base(self, value):
        self._base = value

    def __str__(self):
        return "Number: " + str(self.number) + "  Base: " + str(self.base)


