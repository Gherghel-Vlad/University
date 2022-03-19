"""
    ClientService
        __init__(client_repo, client_validator)
        add(self, <list of client attributes>)
        remove(self, client_id)
        get_all(self) [return all client instasnces]
    + test_client_service



    ClientValidatorRO
        validate(self, client) function
            no Client field is empty
            age >= 18
            driver license is 10 char str
            -> raise ValueError in case of problems [all validators]

      ClientRepositoryWithList
        add(self,client)
        remove(self, client_id)
        get_all(self) [return all client instasnces]

    ClientRepositoryWithDict
        add(self,client)
        remove(self, client_id)
        get_all(self) [return all client instasnces]
    """
from seminar_8.domain.client import Client

"""
car_repo = CarRepositoryWithList()
car_valid_us = CarValidatorUSA()
car_valid_ro = CarValidatorRO()
car_service = CarService(car_repo, car_valid_ro)

ui = MenuUI(car_service, bla bla)
ui.start()

"""


class ClientService:

    def __init__(self, client_repo, client_validator):
        self.client = client_repo
        self.valid = client_validator

    def create(self, client_id, client_name, client_age):
        client = Client(client_id, client_name, client_age)
        # self.valid.validate(client)
        self.client.add(client)

    def remove(self, client_id):
        self.client.remove(client_id)

    def get_all(self):
        self.client.get_all()
