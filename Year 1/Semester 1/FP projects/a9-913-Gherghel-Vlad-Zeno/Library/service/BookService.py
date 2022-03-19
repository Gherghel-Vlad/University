import copy

from Library.Validators.BookValidator import BookValidator
from Library.domain.book import Book
from Library.domain.rental import Rental
from Library.repository.BookRepository import BookRepository
from Library.service.UndoRedoFunctionality import Operation, FunctionCall, CascadedOperation


class BookService:
    def __init__(self, book_repo, book_validator, rental_repo, undo_service):
        self._repo = book_repo
        self._validator = book_validator
        self._rental_repo = rental_repo
        self._undo_service = undo_service

    def add_book(self, book_id, title, author):
        """
        Validates the variables and adds the book to the repo
        :param book_id: The id of the book instance
        :param title: The title of the book instance
        :param author: The author of the book instance
        :return: -
        """
        self._validator.validate_book(Book(book_id, title, author))

        # creates the undo/redo for the adding
        op_undo = FunctionCall(self._repo.remove_book, book_id)
        op_redo = FunctionCall(self._repo.add_book, Book(book_id, title, author))

        op = Operation(op_undo, op_redo)

        self._undo_service.record(op)
        self._repo.add_book(Book(book_id, title, author))

    def remove_book(self, book_id):
        """
        Removes the book with the given id from the repo
        :param book_id: The id of the book object
        :return: -
        """
        cascadedOp = []

        # creates the undo/redo for the removing
        book_removed = self._repo.find_book(book_id)
        self._repo.remove_book(book_id)

        redo = FunctionCall(self._repo.remove_book, book_id)
        undo = FunctionCall(self._repo.add_book, Book(book_id, book_removed.title, book_removed.author))
        cascadedOp.append(Operation(undo, redo))

        rentals = self._rental_repo.filter_by_book_id(book_id)

        # deleting the rentals from the rental repo
        for rental in rentals:
            self._rental_repo.delete_by_rental_id(rental.rental_id)

        # creating the undo/redo for the deletion of rentals as well
        for rental in rentals:
            undo = FunctionCall(self._rental_repo.rent_book, rental)
            redo = FunctionCall(self._rental_repo.delete_by_rental_id, rental.rental_id)
            cascadedOp.append(Operation(undo, redo))

        cop = CascadedOperation(*cascadedOp)

        self._undo_service.record(cop)

    def update_book(self, book_id, new_title, new_author):
        """
        Updates the book with the given id
        :param book_id: The given id
        :param new_title: The new title ( empty string "" for no modifications)
        :param new_author: The new author ( empty string "" for no modifications)
        :return: -
        """
        if new_title != "":
            self._validator.validate_book_title(new_title)
        if new_author != "":
            self._validator.validate_book_author(new_author)

        book_updated = copy.deepcopy(self._repo.find_book(book_id))
        self._repo.update_book(book_id, new_title, new_author)

        undo = FunctionCall(self._repo.update_book, book_updated.book_id, book_updated.title, book_updated.author)
        redo = FunctionCall(self._repo.update_book, book_id, new_title, new_author)

        self._undo_service.record(Operation(undo, redo))

    def list_books(self):
        """
        :return: a string representation of all the books
        """
        return str(self._repo)

    def book_exists(self, book_id):
        """
        Checks if the book with the given id exists
        :param book_id: The given id
        :return: True if it exists and False if it isnt
        """
        if self._repo.find(book_id) == -1:
            return False
        return True

    def search_books_by_id(self, value):
        """
        Searches if a book id contains the value by doing a substring case-insensitive search
        :param value: The value it searches
        :return: A string representing the list of books found
        """
        self._validator.validate_book_id(value)
        books_list = self._repo.search_books_by_id(value)
        string = ""

        if len(books_list) == 0:
            string = f"No books were found with their id containing {value}\n"
        else:
            for book in books_list:
                string += str(book) + "\n"

        return string

    def search_books_by_title(self, value):
        """
        Searches if a book title contains the value by doing a substring case-insensitive search
        :param value: The value it searches
        :return: A string representing the list of books found
        """
        self._validator.validate_book_title(value)

        books_list = self._repo.search_books_by_title(value)
        string = ""

        if len(books_list) == 0:
            string = f"No books were found with their title containing {value}\n"
        else:
            for book in books_list:
                string += str(book) + "\n"

        return string

    def search_books_by_author(self, value):
        """
        Searches if a book author contains the value by doing a substring case-insensitive search
        :param value: The value it searches
        :return: A string representing the list of books found
        """
        self._validator.validate_book_author(value)

        books_list = self._repo.search_books_by_author(value)
        string = ""

        if len(books_list) == 0:
            string = f"No books were found with their author containing {value}\n"
        else:
            for book in books_list:
                string += str(book) + "\n"

        return string

    def get_book_by_book_id(self, book_id):
        """
        Get s the book with the given id
        :param book_id: The book id given
        :return: The book instance with the given id
        """
        self._validator.validate_book_id(book_id)
        return self._repo.book_list[self._repo.find(book_id)]
