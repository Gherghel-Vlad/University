from datetime import date

from seminar_5.domain.entities import Cat, Stay


class ShelterException(Exception):
    def __init__(self, msg):
        self._msg = msg



class Shelter:
    def __init__(self):
        # Lsit of stays for cats in shelter
        self._stays = []
        # List of all cats known to the shelter
        self._cats = []

    def add_cat(self, cat):
        pass

    def add_stay(self, cat, arrival, departure):
        """
        Add a shelter stay for a given cat
        :param cat: the cat
        :param arrival: date of arrival
        :param departure: date of departure
        :return: -
        Raises shelterException if:
            - arrival date > departure date
        """
        if arrival > departure:
            raise ShelterException("Arrival must take place before the departure")
        self._stays.append(Stay(cat, arrival, departure))

    def __len__(self):
        return self.occupancy()

    def occupancy(self):
        """
        Number of shelter occupants today
        :return:
        """
        return len(self._stays)

    def find(self):
        pass

    def adopt(self, cat):
        """
        Adopt a cat from the shelter
        :param cat: the cat
        :return: -
        Raises shelterException if a cat is not in shelter
        """
        for stay in self._stays:
            if stay.cat == cat:
                self._stays.remove(stay)
                return
        raise ShelterException("Cat not found")


def test_shelter():
    c1 = Cat(100, 'Tobby', "domestic short-hair", 8, False)
    c2 = Cat(101, 'Garfield', "domestic short-hair", 8, False)

    s = Shelter()
    assert len(s) == 0
    s.add_stay(c1, date(2020, 10, 28), date(2020, 11, 4))
    assert len(s) == 1

    try:
        s.add_stay(c1, date(2020, 12, 28), date(2020, 11, 4))
        assert False
    except ShelterException:
        assert True

    assert len(s) == 1

    s.adopt(c1)
    assert len(s) == 0


test_shelter()

