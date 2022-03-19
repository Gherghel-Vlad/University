
class Client:
    def __init__(self, id, name, age):
        self.id = id
        self.name = name
        self.age = age

    @property
    def id(self):
        return self._id

    @property
    def name(self):
        return self._name

    @property
    def age(self):
        return self._age

    @id.setter
    def id(self, value):
        self._id = value

    @name.setter
    def name(self, value):
        self._name = value

    @age.setter
    def age(self, value):
        self._age = value

    def to_str(self):
        return "ID: " + str(self.id) + " Name: " + str(self.name) + " Age: " + str(self.age)


def test_client_class():
    c1 = Client("1234", "4325", 18)

    c1.id = "1"
    assert c1.id == "1"

    c1.name = "2"
    assert c1.name == "2"

    c1.age = 4
    assert c1.age == 4

test_client_class()









