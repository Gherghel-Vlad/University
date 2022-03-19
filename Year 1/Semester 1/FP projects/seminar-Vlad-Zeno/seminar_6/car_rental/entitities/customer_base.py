from seminar_6.car_rental.entitities.car_rental_exception import CarRentalException
from seminar_6.car_rental.entitities.client import Client


class CustomerBase:
    def __init__(self):
        self._client_list = []

    @property
    def client_list(self):
        return self._client_list

    def test_init(self):
        self._client_list.append(Client("12345", "Ana", 18))
        self._client_list.append(Client("5435432", "Mihail", 30))
        self._client_list.append(Client("1654367345", "Dragos", 54))
        self._client_list.append(Client("123345445", "Vivi", 18))
        self._client_list.append(Client("1232142145", "Salah", 34))
        self._client_list.append(Client("6543", "Muhammad", 23))
        self._client_list.append(Client("463256", "Ali", 47))

    def remove(self, customer_id):
        """
        Removes the customer with the given id
        :param customer_id: The given id
        :return: -
        Raises CarRentalException if the customer wasn't found
        """
        for client in self._client_list:
            if client.id == customer_id:
                self._client_list.remove(client)
                return

        raise CarRentalException("There is no customer with the given id")

    def search(self, search_word=""):
        """
        Searches if a client has that substring in it s name or id
        :param search_word: The substring that s going to search with
        :return: A list containing all the clients that contain that substring in their names or ids
        """
        new_list = []

        for client in self._client_list:
            if search_word in client.id or search_word in client.name:
                new_list.append(client)

        return new_list

    def __len__(self):
        return len(self._client_list)

def test_customer_base():
    cb = CustomerBase()
    cb.test_init()

    assert len(cb) == 7

    new_list = cb.search("12345")

    assert len(new_list) == 1

    new_list = cb.search("123456789")

    assert len(new_list) == 0

    cb.remove("12345")

    assert len(cb) == 6

test_customer_base()