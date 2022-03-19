# Here i will start the program
from PyQt5 import QtWidgets
from Library.Helpers import Helper
from Library.Validators.BookValidator import BookValidator
from Library.Validators.ClientValidator import ClientValidator
from Library.domain.book import Book
from Library.domain.client import Client
from Library.first_version import Ui_MainWindow
from Library.repository.BookRepository import BookRepository
from Library.repository.ClientRepository import ClientRepository
from Library.repository.RentalRepository import RentalRepository
from Library.service.BookService import BookService
from Library.service.ClientService import ClientService
from Library.service.RentalService import RentalService
from Library.service.UndoRedoFunctionality import UndoService
from Library.ui.menu_ui import UI


undo_service = UndoService()

book_validator = BookValidator()

book_repo = BookRepository()

client_repo = ClientRepository()

client_validator = ClientValidator()

rental_repo = RentalRepository()
rental_repo.add_dummy_data()

client_service = ClientService(client_repo, client_validator, rental_repo, undo_service)
book_service = BookService(book_repo, book_validator, rental_repo, undo_service)
rental_service = RentalService(rental_repo, book_service, client_service, undo_service)

Helper.add_clients(client_service)
Helper.add_books(book_service)
undo_service.restart()


print("1. UI\n")
print("2. GUI\n")
command = input("Which one do you want to use? Answer: ")
if command.strip() == "1":
    ui = UI(book_service, client_service, rental_service, undo_service)
    ui.start()
elif command.strip() == "2":
    import sys

    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow)
    MainWindow.show()
    sys.exit(app.exec_())

else:
    print("No no, someone doesnt know how to read or write.")
