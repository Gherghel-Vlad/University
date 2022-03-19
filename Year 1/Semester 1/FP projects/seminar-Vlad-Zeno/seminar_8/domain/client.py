class Client:
    def __init__(self, id=-1, name=-1, age=-1):
        self._id = id
        self._name = name
        self._age = age

    @property
    def id(self):
        return self._id

    @property
    def name(self):
        return self._name

    @property
    def age(self):
        return self._age

    @age.setter
    def age(self, val):
        self._age = val


def testclient():
    cl1 = Client('12', 'ion', 14)

    assert cl1.id == '12'
    assert cl1.name == 'ion'
    assert cl1.age == 14

    cl2 = Client('10000111', 'titel pop', 20)

    assert cl2.id == '10000111'
    assert cl2.name == 'titel pop'
    assert cl2.age == 20

    cl2.age = 20
    assert cl2.age == 20


testclient()
