from unittest import TestCase


class CarException(Exception):
    def __init__(self, exception_message):
        self._exception_message = exception_message


class Car:
    def __init__(self, id_, license_, model, make):
        if not isinstance(license_, str):
            raise CarException('License must be a string!')
        if not isinstance(make, str):
            raise CarException('Make must be a string!')
        if not isinstance(model, str):
            raise CarException('Model must be a string!')
        self._id = id_
        self._license = license_
        self._make = make
        self._model = model

    @property
    def id(self):
        return self._license

    @property
    def make(self):
        return self._make

    @property
    def model(self):
        return self._model


class CarValidatorException(CarException):
    def __init__(self, exception_message):
        self._exception_message = exception_message


class CarValidatorUSA:
    # Return True or False
    @staticmethod
    def validate(car):
        if len(car.license) < 5:
            raise CarValidatorException('Not enough characters, must be over 5')
        if len(car.make) < 3:
            raise CarValidatorException('Car make must have over 3 letters')
        if len(car.model) < 3:
            raise CarValidatorException('Car model must be over 3')


def test_car():
    try:
        valid = CarValidatorUSA()
        valid.validate(Car('b', 'ford', 'focus'))

    except CarValidatorException as CVE:
        print(str(CVE))
