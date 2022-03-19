from datetime import datetime

from Library.domain.rental import Rental
from Library.repository.RentalRepository import RentalRepository


class RentalTextFileRepositoryException(Exception):
    def __init__(self, msg):
        super().__init__(msg)


class RentalTextFileRepository(RentalRepository):
    def __init__(self, file_name):
        super().__init__()
        self._file_name = file_name

        # loads the data if it can or creates a new file with that name
        try:
            self._load_data()
        except FileNotFoundError as e:
            f = open(file_name, "wb")
            f.close()

    @property
    def file_name(self):
        return self._file_name

    def _save_data(self):
        rental_list = super().rental_list

        f = open(self.file_name, "w")
        try:
            for rental in rental_list:
                rental_str = str(rental.rental_id) + "*" + str(rental.book_id) + "*" + str(
                    rental.client_id) + "*" + str(rental.rented_date) + "*" + str(rental.returned_date) + "\n"
                f.write(rental_str)

            f.close()
        except Exception:
            raise RentalTextFileRepositoryException(
                "Something went wrong with the writing in the file. Please check that the file is okay.")

    def _load_data(self):
        rental_list = []

        try:
            f = open(self.file_name, "r")

            line = f.readline().strip()

            while len(line) > 0:
                line = line.split("*")
                try:
                    rented_date = datetime.strptime(line[3], '%Y-%m-%d %H:%M:%S.%f')
                except ValueError:
                    rented_date = datetime.strptime(line[3], '%Y-%m-%d %H:%M:%S')

                if line[4] != "None":
                    try:
                        returned_date = datetime.strptime(line[4], '%Y-%m-%d %H:%M:%S.%f')
                    except ValueError:
                        returned_date = datetime.strptime(line[4], '%Y-%m-%d %H:%M:%S')
                else:
                    returned_date = None
                rental_list.append(Rental(line[0], line[1], line[2], rented_date, returned_date))
                line = f.readline().strip()

            for rental in rental_list:
                self.rent_book(rental)

            f.close()
        except FileNotFoundError as e:
            raise FileNotFoundError()
        except IOError as e:
            raise RentalTextFileRepositoryException(
                "File " + str(self.file_name) + " could not be opened. Check if everything is alright.")

    def rent_book(self, new_rental):
        super().rent_book(new_rental)
        self._save_data()

    def return_book(self, book_id):
        super().return_book(book_id)
        self._save_data()

    def delete_by_rental_id(self, rental_id):
        super().delete_by_rental_id(rental_id)
        self._save_data()

    def remove_returned_date(self, rental_id):
        super().remove_returned_date(rental_id)
        self._save_data()
