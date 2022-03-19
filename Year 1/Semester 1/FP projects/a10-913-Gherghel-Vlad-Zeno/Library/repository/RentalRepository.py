from datetime import datetime

from Library.data_structures.IterableDataStructure import IterableDataStructure, filter_list
from Library.domain.rental import Rental


class RentalRepositoryException(Exception):
    def __init__(self, msg):
        super().__init__(msg)


class RentalRepository:
    def __init__(self):
        self._rental_list = IterableDataStructure()

    @property
    def rental_list(self):
        return self._rental_list.list

    def is_book_available(self, book_id):
        """
        Checks if a book is available
        :param book_id: The id of the book object that s going to search for
        :return: True if it is available, False otherwise
        """
        for rental in self._rental_list:
            if rental.book_id == book_id:
                if rental.returned_date == "" or rental.returned_date is None:
                    return False
        return True

    def find_not_returned_rental_by_book_id(self, book_id):
        """
        Finds the rental that was not returned for the book id
        :param book_id: The id of the book that s going to use in the search
        :return: Index of rental in the list of rentals or -1 if it isnt found
        """
        for index in range(0, len(self._rental_list)):
            if self._rental_list[index].book_id == book_id:
                if self._rental_list[index].returned_date is None:
                    return index
        return -1

    def rent_book(self, new_rental):
        """
        Rents an available book
        :param new_rental: The new rental
        :return: -
        Raises RentalRepositoryException if there's already a rental with the same id
        Raises RentalRepositoryException if the book was rented already
        """
        for rental in self._rental_list:
            if rental.rental_id == new_rental.rental_id:
                raise RentalRepositoryException("There s already a rental with this id " + str(new_rental.rental_id))

        if self.is_book_available(new_rental.book_id):
            self._rental_list.append(new_rental)
        else:
            raise RentalRepositoryException("The book was rented already.")

    def return_book(self, book_id, returned_date_time_now=None):
        """
        Returns a rented book
        :param book_id: The id of the book returned
        :return: -
        """
        index = self.find_not_returned_rental_by_book_id(book_id)

        if index == -1:
            raise RentalRepositoryException("The book with id " + str(book_id) + " is not rented.")

        if returned_date_time_now is None:
            returned_date = datetime.now()
        else:
            returned_date = returned_date_time_now

        self._rental_list[index].returned_date = returned_date

    def filter_by_book_id(self, book_id):
        """
        Filters all the rentals by the book_id given
        :param book_id: The book_id given
        :return: A list containing all the rentals with the book_id
        """
        return filter_list(self.rental_list, lambda x: str(book_id).lower() in str(x.book_id).lower())

    def find_rental_by_rental_id(self, id_):
        """
        Finds the rental with the given id
        :param id_: The given id
        :return: The index of that rental, or -1 if it wasnt found
        """
        for index in range(0, len(self.rental_list)):
            if id_ == self.rental_list[index].rental_id:
                return index
        return -1


    def filter_by_client_id(self, client_id):
        """
        Filters all the rentals by the client_id given
        :param client_id: The client_id given
        :return: A list containing all the rentals with the client_id
        """
        return filter_list(self.rental_list, lambda x: str(client_id).lower() in str(x.client_id).lower())

    def delete_by_rental_id(self, rental_id):
        """
        Deletes the rental with the given rental id
        :param rental_id: The given rental id
        :return: -
        """
        for index in range(0, len(self._rental_list)):
            if self._rental_list[index].rental_id == rental_id:
                del self._rental_list[index]
                break

    def remove_returned_date(self, rental_id):
        """
        Sets the returned date property of the rental with the given id to None
        :param rental_id: The rental id that the rental instance will have
        :return: -
        """
        for rental in self._rental_list:
            if rental.rental_id == rental_id:
                rental.returned_date = None
                break

    def __str__(self):
        """
        :return: The string representation of the repo list
        """
        representation = "Rentals: \n"
        for rental in self._rental_list:
            representation += str(rental) + "\n"
        if len(self._rental_list) == 0:
            representation += "There are no rentals yet \n"

        return representation

    def add_dummy_data(self):
        self._rental_list.append(Rental("10", "23", "50", datetime(2018, 11, 20, 12, 11), datetime(2018, 11, 22, 13, 5)))
        self._rental_list.append(Rental("14", "23", "68", datetime(2019, 7, 22, 15, 22), datetime(2019, 7, 29, 16, 00)))
        self._rental_list.append(Rental("115", "61", "43", datetime(2014, 11, 20, 12, 11), None))
        self._rental_list.append(Rental("16", "44", "50", datetime(2020, 2, 11, 10, 20), datetime(2020, 3, 21, 11, 30)))
        self._rental_list.append(Rental("120", "45", "23", datetime(2020, 3, 20, 14, 22), datetime(2020, 4, 5, 15, 30)))
        self._rental_list.append(Rental("22", "53", "69", datetime(2020, 3, 20, 14, 25), datetime(2020, 4, 7, 16, 00)))
        self._rental_list.append(Rental("23", "53", "23", datetime(2020, 5, 23, 18, 25), datetime(2020, 6, 4, 22, 00)))
        self._rental_list.append(Rental("24", "2", "71", datetime(2020, 6, 5, 15, 30), datetime(2020, 7, 10, 12, 00)))
        self._rental_list.append(Rental("26", "11", "23", datetime(2020, 8, 20, 17, 30), datetime(2020, 8, 23, 18, 25)))
        self._rental_list.append(Rental("44", "345", "73", datetime(2020, 10, 20, 19, 25), datetime(2020, 11, 1, 15, 00)))
