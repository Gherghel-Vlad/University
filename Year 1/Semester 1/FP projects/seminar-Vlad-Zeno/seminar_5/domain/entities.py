class Cat:
    # Common to all cats
    _count = 0

    def __init__(self, id_,  name, breed, age, is_vaccinated):
        # These dont change 0 > read only attributes
        self._name = name
        self._id = id_
        self._breed = breed
        # These below might change
        self._age = age
        self._is_vaccinated = is_vaccinated
        Cat._count += 1

    @property
    def id(self):
        return self._id

    @property
    def name(self):
        return self._name

    @property
    def breed(self):
        return self._breed

    @property
    def age(self):
        return self._age

    @property
    def vaccinated(self):
        return self._is_vaccinated

    @age.setter
    def age(self, value):
        self._age = value

    @vaccinated.setter
    def vaccinated(self, value):
        self.vaccinated = value

    def __add__(self, other):
        return Cat(self.id, self.name, self.breed, self.age + other, self.vaccinated)
        #self.age += other
        #return self

    @staticmethod
    def cat_count():
        return Cat._count

    def __eq__(self, other):
        # only compare cats to other cats
        if not isinstance(other, Cat):
            raise TypeError("Cannot compare cats to non-cats")
        return self.id == other.id


class Stay:
    def __init__(self, cat, arrival, departure=None):
        self._cat = cat
        self._arrival = arrival
        self._departure = departure

    @property
    def cat(self):
        return self._cat

    @property
    def arrival(self):
        return self._arrival


if __name__ == "__main__":
    c1 = Cat(100, 'Tobby', "domestic short-hair", 8, False)
    c2 = Cat(101, 'Garfield', "domestic short-hair", 8, False)
    print(c1.name)

    c1 + 1 + 1 + 1 + 1
    c1.age += 1
    print(Cat.cat_count())
    print(c1.age)

    print(Cat.cat_count())
