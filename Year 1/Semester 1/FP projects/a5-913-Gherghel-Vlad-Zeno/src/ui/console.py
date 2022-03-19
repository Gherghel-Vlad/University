"""
    UI class.

    Calls between program modules
    ui -> service -> entity
    ui -> entity
"""
from src.domain.BookException import BookException
from src.domain.entity import Book
from src.services.service import ListOfBooks


class Console:
    def __init__(self):
        self._listOfBooks = ListOfBooks()
        self._listOfBooks.init_list_of_books()

    @staticmethod
    def show_commands():
        print("1. Add book")
        print("2. Add random book")
        print("3. Show list")
        print("4. Filter list (deletes all the books that start with the words given)")
        print("5. Undo command")
        print("0. Exit")

    @staticmethod
    def read_book():
        """
        Reads a book given by the user
        :return: A book (instance of a Book class)
        """
        try:
            author = input("Author: ")
            if author.strip() == "":
                raise ValueError("You have to give values.")
            title = input("Title: ")
            if title.strip() == "":
                raise ValueError("You have to give values.")
            isbn = input("ISBN: ")
            if isbn.strip() == "":
                raise ValueError("You have to give values.")
            return Book(author, title, isbn)
        except BookException as msg:
            print(msg)

    def add_book_ui(self):
        self._listOfBooks.add_book(Console.read_book())

    def add_random_book_io(self):
        self._listOfBooks.add_book(Book())

    def show_list_ui(self):
        """
        Prints all the values in the list
        :return: -
        """
        if len(self._listOfBooks.get_formatted_list_of_books()) == 0:
            print("There are no books")
        else:
            for string in self._listOfBooks.get_formatted_list_of_books():
                print(string)

    def filter_list_ui(self):
        word = input("Word: ")
        if word == "":
            raise ValueError("You have to write a word boye")
        self._listOfBooks.filter_list(word)

    def undo_command_ui(self):
        self._listOfBooks.undo_last_operation()

    @staticmethod
    def read_command():
        """
        Reads the user's command
        :return: A string representing the user s command
        """
        return input("Give command masta: ")

    def start(self):
        done = False
        command_dict = {"1": self.add_book_ui, "2": self.add_random_book_io, "3": self.show_list_ui,
                        "4": self.filter_list_ui, "5": self.undo_command_ui}
        while not done:
            try:
                Console.show_commands()
                command = Console.read_command()
                if command == "0":
                    done = True
                elif command in command_dict:
                    command_dict[command]()
                else:
                    raise ValueError("Bad command")
            except (ValueError, BookException) as val:
                print(val)


console = Console()
console.start()