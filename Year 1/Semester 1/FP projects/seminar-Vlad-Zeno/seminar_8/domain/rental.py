from datetime import date


class RentalException(Exception):
    def __init__(self, msg=''):
        self._msg = msg

    def __str__(self):
        return self._msg


class RentalValidationException(RentalException):
    def __init__(self, error_list):
        self._errors = error_list

    @property
    def errors(self):
        # Gives access to the list of errors
        return self._errors

    def __str__(self):
        # str representation
        result = ''
        for e in self.errors:
            result += e
            result += '\n'
        return result


class Rental:
    def __init__(self, rental_id, client, car, start_date, end_date):
        self._rental_id = rental_id
        self._client = client
        self._car = car
        self._start_date = start_date
        self._end_date = end_date

    @property
    def id(self):
        return self._rental_id

    @property
    def client(self):
        return self._client

    @property
    def car(self):
        return self._car

    @property
    def start_date(self):
        return self._start_date

    @property
    def end_date(self):
        return self._end_date

    def __len__(self):
        if self._end_date is None:
            return abs(self._start_date.day + 1)
        else:
            return abs(self._end_date.day - self._start_date.day)


class RentalValidator:
    """
    Generic validator for car instance
    """

    def validate(self, rental):
        """
        Validate given car
        @param car:
        @return: Raise CarValidationException if car instance is not valid
        """
        errors = []
        if rental.rental_id == 0:
            errors.append("Error! invalid rental id ")
        if len(rental.client) == 0:
            errors.append("Error! invalid rental client")
        if len(rental.car) == 0:
            errors.append("Error! invalid rental car ")
        if rental.start_date == date(1, 1, 1):
            errors.append("Invalid start date, default value provided (1, 1, 1)")
        if rental.end_date == date(1, 1, 1):
            errors.append("Invalid end date, default value provided (1, 1, 1)")
        if rental.start_date > rental.end_date:
            errors.append("Start date is bigger than end date")
        if len(errors) != 0:
            raise RentalValidationException(errors)
