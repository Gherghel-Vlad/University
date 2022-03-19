"""
    Service class includes functionalities for implementing program features
"""
import copy

from src.domain.entity import Book


class ListOfBooks:
    def __init__(self):
        self._listOfBooks = []
        self._listOfBooksHistoryList = []

    def add_book(self, book):
        """
        Adds a Book instance to the list of books
        :param book: The book that s going to be added
        :return:-
        Raises ValueError if the book given is not an instance of the Book
        Raises ValueError if the book given doesnt have an unique ISBN
        """
        if not isinstance(book, Book):
            raise ValueError("The book must be a Book class")
        if not self.check_isbn_unique(book.isbn):
            raise ValueError("ISBN is not unique")
        self._listOfBooksHistoryList.append(copy.deepcopy(self._listOfBooks))
        self._listOfBooks.append(book)

    def get_list_of_books(self):
        return self._listOfBooks

    def get_formatted_list_of_books(self):
        """
        Creates a list with the formatted Books in the list of books
        :return: A list containing formatted strings that represent the books from list of books
        """
        formatted_list = []

        for book in self._listOfBooks:
            formatted_list.append(book.to_string_format())

        return formatted_list

    def filter_list(self, word):
        """
        Deletes all the books that start with a given word
        :return: -
        """
        word = word.strip()
        new_list = []
        for book in self._listOfBooks:
            if str(book.title).find(word) == -1:
                new_list.append(book)
        self._listOfBooksHistoryList.append(copy.deepcopy(self._listOfBooks))
        self._listOfBooks = new_list

    def undo_last_operation(self):
        """
        Undos the last operation that changed the list of books
        :return: -
        Raises ValueError if the are no more undoes to be made
        """
        if len(self._listOfBooksHistoryList) == 0:
            raise ValueError("There are no more undoes to be made")
        self._listOfBooks = copy.deepcopy(self._listOfBooksHistoryList[-1])
        self._listOfBooksHistoryList = self._listOfBooksHistoryList[:-1]

    def init_list_of_books(self):
        for index in range(0, 10):
            self._listOfBooks.append(Book())

    def check_isbn_unique(self, new_isbn):
        """
        Checks if the given isbn is unique or not
        :param new_isbn: The isbn that s going to be searched for
        :return: True if it is unique, False otherwise
        """
        for book in self._listOfBooks:
            if book.isbn == new_isbn:
                return False
        return True

    def __len__(self):
        return len(self._listOfBooks)


def test_list_of_books_class():
    list_of_books = ListOfBooks()
    book = Book("Angel", "I am sorry for leaving you suddenly", "4-543-678-45612-3")
    assert len(list_of_books) == 0

    # Add function test

    list_of_books.add_book(book)

    assert len(list_of_books) == 1

    # Get list of books test

    list = list_of_books.get_list_of_books()

    assert len(list) == 1 and list[0].author == "Angel"

    # Get formatted list of books test

    formatted_list = list_of_books.get_formatted_list_of_books()

    assert len(formatted_list) == 1 and formatted_list[0] == book.to_string_format()

    # Filter list text

    list_of_books.filter_list("I")

    assert len(list_of_books) == 0

    # Undo test

    list_of_books.undo_last_operation()

    assert len(list_of_books) == 1

    list_of_books.add_book(Book())
    list_of_books.add_book(Book())

    assert len(list_of_books) == 3

    list_of_books.undo_last_operation()

    assert len(list_of_books) == 2

    list_of_books.undo_last_operation()
    list_of_books.undo_last_operation()
    try:
        list_of_books.undo_last_operation()
        assert False
    except ValueError:
        assert True


test_list_of_books_class()
