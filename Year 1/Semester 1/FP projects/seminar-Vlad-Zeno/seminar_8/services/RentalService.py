# marc

"""
RentalService
        __init__(rental_repo, client_repo, car_repo, rental_validator)
        add(self, <list of rental attributes>)
        remove(self, rental_id)
        get_all(self) [return all rental instasnces]
    + test_rental_service
"""
from seminar_8.domain.rental import Rental


class RentalService:
    def __init__(self, rental_repo, client_repo, car_repo, rental_validator):
        self._rental_repo = rental_repo
        self._client_repo = client_repo
        self._car_repo = car_repo
        self._rental_validator = rental_validator

    def create_rental(self, id_, car, client, start_date, end_date):
        rental = Rental(id_, car, client, start_date, end_date)
        # self._rental_validator(rental)

        self._rental_repo.add(rental)

    def remove(self, rental_id):
        """
        # depends on the implementation but

        # make car available for future rentals
        car_id = self._rental_repo.get_rental(rental_id).car.car_id
        self._car_repo.make_car_available(car_id)

        also maybe do the same for client? if we decide to store his current rentals
        """
        self._rental_repo.remove(rental_id)

    def get_all(self):
        response = self._rental_repo.get_all()
        if len(response) > 0:
            return response
        raise ValueError("There are no rentals")

    def filter_rentals(self, client, car):
        """
        Return a list of rentals performed by the provided client for the provided car
        client - The client performing the rental. None means all clients
        cars - The rented car. None means all cars
        """
        result = []
        for rental in self._repository.get_all():
            if client is not None and rental.getClient() != client:
                continue
            if car is not None and rental.car != car:
                continue
            result.append(rental)
        return result

    def most_often_rented_car_make(self):
        """
        The list of car makes, sorted by the number of rental days
        """
        result = []
        # Compute stat using an interim dictionary
        rentals_dict = {}
        for rental in self._rental_repo.get_all():
            if rental.car.make not in rentals_dict:
                rentals_dict[rental.car.make] = 0
            rentals_dict[rental.car.make] += len(rental)
        # Move data to sorted list of values
        for entry in rentals_dict:
            result.append(CarMakeRentalDays(entry, rentals_dict[entry]))
        # Sort the list
        # lambda <parameter list> : <function body>
        result.sort(key=lambda x: x.rental_days, reverse=True)
        return result


class CarMakeRentalDays:
    """
    Data Transfer Object for statistics
    SRP: Move data between application layers
    """

    def __init__(self, car_make, car_make_rental_days):
        self._car_make = car_make
        self._car_make_rental_days = car_make_rental_days

    @property
    def make(self):
        return self._car_make

    @property
    def rental_days(self):
        return self._car_make_rental_days

    def __str__(self):
        return self.make + ' - ' + str(self.rental_days)
