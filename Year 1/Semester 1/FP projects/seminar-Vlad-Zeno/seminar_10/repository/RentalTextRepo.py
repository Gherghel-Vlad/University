from Tools.scripts.ndiff import fopen

from seminar_10.domain.Rental import Rental
from seminar_10.repository.FileRepo import FileRepo


class RentalTextRepo(FileRepo):
    def __init__(self, file_name, car_repo, client_repo):
        super().__init__(file_name)
        self._car_repo = car_repo
        self._client_repo = client_repo

    def _load_file(self):
        #  def __init__(self, rentalId, start, end, client, car):
        file = open(self.file_name, "r")
        for line in file:
            list_strings = line.strip().split(",")
            self.store(Rental(list_strings[0], list_strings[1], list_strings[2], self._client_repo.find(list_strings[3]), self._car_repo.find(list_strings[4])))
        file.close()

    def _save_file(self):
        file = open(self.file_name, "w")
        rentals = self.getAll()
        for rental in rentals:
            file.write(str(rental.id) + "," + str(rental.start) + "," + str(rental.end) + "," + str(rental.client.id) + "," + str(rental.car.id))
        file.close()
