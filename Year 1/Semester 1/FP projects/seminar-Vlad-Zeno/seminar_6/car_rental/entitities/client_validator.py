from seminar_6.car_rental.entitities.car_rental_exception import CarRentalException
from seminar_6.car_rental.entitities.client import Client


class ClientValidator:

    @staticmethod
    def validate_client(client):
        """
        Validates a if a client instance is valid
        :param client: The instance of the Client class that s going to be validated
        :return: -
        Raises CarRentalException if it s not
        """
        if not isinstance(client, Client):
            raise CarRentalException("Client is not an instance of the client class")
        if client.id == "" or client.name == "" or client.age == "":
            raise CarRentalException("One of the fields is empty. Please try again")

        if not isinstance(client.age, int) or client.age <= 0:
            raise CarRentalException("Age should be a valid number")
        if not isinstance(client.name, str):
            raise CarRentalException("Name should be a string")
        if not isinstance(client.id, str):
            raise CarRentalException("Id should be a string")


def test_client_validator_class():
    c1 = Client("1234", "4325", 18)
    ClientValidator.validate_client(c1)

    try:
        c2 = Client(123, "432", 18)
        ClientValidator.validate_client(c2)
        assert False
    except CarRentalException:
        assert True

    try:
        c2 = Client("123", 432, 18)
        ClientValidator.validate_client(c2)
        assert False
    except CarRentalException:
        assert True

    try:
        c2 = Client("123", "432", "18")
        ClientValidator.validate_client(c2)
        assert False
    except CarRentalException:
        assert True
    try:
        c2 = Client("123", "432", -1)
        ClientValidator.validate_client(c2)
        assert False
    except CarRentalException:
        assert True

test_client_validator_class()