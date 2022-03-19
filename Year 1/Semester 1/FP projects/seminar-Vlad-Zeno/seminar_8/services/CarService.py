"""
    Module for the car service
"""
from seminar_8.domain.car import Car


class CarRepoException(Exception):
    def __init__(self, error_message):
        self.__error_message = error_message

    def __str__(self):
        return self.__error_message


class CarService:
    def __init__(self, car_repo, car_validator):
        self.__car_repo = car_repo
        self.__car_validator = car_validator

    @property
    def car_repo(self):
        return self.__car_repo

    @car_repo.setter
    def car_repo(self, value):
        self.__car_repo = value

    @property
    def car_validator(self):
        return self.__car_validator

    @car_validator.setter
    def car_validator(self, value):
        self.__car_validator = value

    def create(self, car_id, car_license, car_model, car_make):
        new_car = Car(car_id, car_license, car_make, car_model)
        # self.car_validator.validate(new_car)
        self.car_repo.add(new_car)
        return Car(car_id, car_license, car_make, car_model)

    def remove(self, car_id):
        position = self.check_if_in_list(car_id)
        if position == -1:
            raise CarRepoException('Car ID not in list!')
        else:
            self.car_repo.remove(car_id)

    def check_if_in_list(self, car_id):
        for car_index in range(len(self.car_repo)):
            if self.car_repo[car_index].id == car_id:
                return car_index
        return -1

    def get_all(self):
        return self.car_repo.get_all()


# TODO implement test function
# I need the other classes for this to work
def test_car_service():
    pass
