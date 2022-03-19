from datetime import datetime

from Library.domain.rental import Rental
from Library.service.UndoRedoFunctionality import FunctionCall, Operation


class RentalServiceException(Exception):
    def __init__(self, msg):
        super().__init__(msg)


class RentalService:
    def __init__(self, rental_repo, book_service, client_service, undo_service):
        self._repo = rental_repo
        self._book_service = book_service
        self._client_service = client_service
        self._undo_service = undo_service

    def rent_book(self, rental_id, book_id, client_id):
        """
        Rents the book with the given id by the client with the given client id
        :param rental_id: The rental id
        :param book_id: The id of the book object
        :param client_id: The id of the client object
        :return: -
        Raises RentalServiceException if there is no rental given (empty string)
        Raises RentalServiceException if there is no book with the given id
        Raises RentalServiceException if there is no client with the given id
        """
        if rental_id == "" or rental_id is None:
            raise RentalServiceException("Rental id cant be empty.")

        if not self._book_service.book_exists(book_id):
            raise RentalServiceException("There s no book with the id " + str(book_id))

        if not self._client_service.client_exists(client_id):
            raise RentalServiceException("There s no client with the id " + str(client_id))

        rental = Rental(rental_id, book_id, client_id, datetime.now(), None)

        redo = FunctionCall(self._repo.rent_book, rental)
        undo = FunctionCall(self._repo.delete_by_rental_id, rental_id)

        self._undo_service.record(Operation(undo, redo))
        self._repo.rent_book(rental)

    def return_book(self, book_id):
        """
        Returns the book with the book id given
        :param book_id: The id of the book returned
        :return: -
        Raises RentalServiceException if there is no book with the given id
        """
        if not self._book_service.book_exists(book_id):
            raise RentalServiceException("There s no book with the id " + str(book_id))

        index = self._repo.find_not_returned_rental_by_book_id(book_id)

        undo = FunctionCall(self._repo.remove_returned_date, self._repo.rental_list[index].rental_id)
        redo = FunctionCall(self._repo.return_book, book_id)

        self._undo_service.record(Operation(undo, redo))

        self._repo.return_book(book_id)

    def rental_list(self):
        """
        :return: A string representing all the rentals
        """
        return str(self._repo)

    def delete_rentals_by_client_id(self, client_id):
        """
        Deletes all the rentals that have the client id given
        :param client_id: The client id given
        :return: -
        """
        nr = len(self._repo.rental_list)
        index = 0
        while index < nr:
            if self._repo.rental_list[index].client_id == client_id:
                del self._repo.rental_list[index]
                nr -= 1
            else:
                index += 1

    def delete_rentals_by_book_id(self, book_id):
        """
        Deletes all the rentals that have the book id given
        :param book_id: The id of the book
        :return: -
        """
        nr = len(self._repo.rental_list)
        index = 0
        while index < nr:
            if self._repo.rental_list[index].book_id == book_id:
                del self._repo.rental_list[index]
                nr -= 1
            else:
                index += 1

    def most_rented_books(self):
        """
        This will provide the list of books, sorted in descending order of the number of times they were rented
        :return: A list of books with their rented number
        """
        result = []

        rental_dict = {}
        for rental in self._repo.rental_list:
            if rental.book_id not in rental_dict:
                rental_dict[rental.book_id] = 0
            rental_dict[rental.book_id] += 1

        for entry in rental_dict:
            result.append(BookRentedDays(self._book_service.get_book_by_book_id(entry), rental_dict[entry]))

        result.sort(key=lambda x: x.rented_times, reverse=True)

        return result

    def most_active_clients(self):
        """
        This will provide the list of clients, sorted in descending order of the number of book rental days they have
        :return: A list of clients and their rental days in descentind order
        """
        result = []

        rental_dict = {}
        for rental in self._repo.rental_list:
            if rental.client_id not in rental_dict:
                rental_dict[rental.client_id] = 0
            rental_dict[rental.client_id] += len(rental)

        for entry in rental_dict:
            result.append(ClientRentalDays(self._client_service.get_client_by_client_id(entry), rental_dict[entry]))

        result.sort(key=lambda x: x.rented_days, reverse=True)

        return result

    def most_rented_authors(self):
        """
        This will provide the list of books, sorted in descending order of the number of times they were rented
        :return: A list of books with their rented number
        """
        result = []

        rental_dict = {}
        for rental in self._repo.rental_list:
            book = self._book_service.get_book_by_book_id(rental.book_id)
            if book.author not in rental_dict:
                rental_dict[book.author] = 0
            rental_dict[book.author] += 1

        for entry in rental_dict:
            result.append(AuthorRentalNumber(entry, rental_dict[entry]))

        result.sort(key=lambda x: x.rental_number, reverse=True)

        return result


class BookRentedDays:
    def __init__(self, book, rented_days):
        self._book = book
        self._rented_times = rented_days

    @property
    def book(self):
        return self._book

    @property
    def rented_times(self):
        return self._rented_times

    def __str__(self):
        return str(self.book) + " Rented times: " + str(self.rented_times)


class ClientRentalDays:
    def __init__(self, client, rented_days):
        self._client = client
        self._rented_days = rented_days

    @property
    def client(self):
        return self._client

    @property
    def rented_days(self):
        return self._rented_days

    def __str__(self):
        return str(self.client) + " Rented days: " + str(self.rented_days)


class AuthorRentalNumber:
    def __init__(self, author, rental_number):
        self._author = author
        self._rental_number = rental_number

    @property
    def author(self):
        return self._author

    @property
    def rental_number(self):
        return self._rental_number

    def __str__(self):
        return str(self.author) + " Rental number: " + str(self.rental_number)
