# Here i will start the program
from PyQt5 import QtWidgets
from Library.Helpers import Helper
from Library.Settings import Settings
from Library.Validators.BookValidator import BookValidator
from Library.Validators.ClientValidator import ClientValidator
from Library.domain.book import Book
from Library.domain.client import Client
from Library.first_version import Ui_MainWindow
from Library.repository.BookJSONFileRepository import BookJSONFileRepository
from Library.repository.BookPickleFileRepository import BookPickleFileRepository
from Library.repository.BookRepository import BookRepository
from Library.repository.BookTextFileRepository import BookTextFileRepository
from Library.repository.ClientJSONFileRepository import ClientJSONFileRepository
from Library.repository.ClientPickleFileRepository import ClientPickleFileRepository
from Library.repository.ClientRepository import ClientRepository
from Library.repository.ClientTextFileRepository import ClientTextFileRepository
from Library.repository.RentalJSONFileRepository import RentalJSONFileRepository
from Library.repository.RentalPickleFileRepository import RentalPickleFileRepository
from Library.repository.RentalRepository import RentalRepository
from Library.repository.RentalTextFileRepository import RentalTextFileRepository
from Library.service.BookService import BookService
from Library.service.ClientService import ClientService
from Library.service.RentalService import RentalService
from Library.service.UndoRedoFunctionality import UndoService
from Library.ui.menu_ui import UI

undo_service = UndoService()

book_validator = BookValidator()

client_validator = ClientValidator()

settings = Settings()

# Here i choose which types of repos i use
if settings.get_repository_type() == "inmemory":
    book_repo = BookRepository()
    client_repo = ClientRepository()
    rental_repo = RentalRepository()
    rental_repo.add_dummy_data()
elif settings.get_repository_type() == "textfiles":
    book_repo = BookTextFileRepository(settings.get_books_file_name())
    client_repo = ClientTextFileRepository(settings.get_clients_file_name())
    rental_repo = RentalTextFileRepository(settings.get_rentals_file_name())
elif settings.get_repository_type() == "picklefiles":
    book_repo = BookPickleFileRepository(settings.get_books_file_name())
    client_repo = ClientPickleFileRepository(settings.get_clients_file_name())
    rental_repo = RentalPickleFileRepository(settings.get_rentals_file_name())
elif settings.get_repository_type() == "jsonfiles":
    book_repo = BookJSONFileRepository(settings.get_books_file_name())
    client_repo = ClientJSONFileRepository(settings.get_clients_file_name())
    rental_repo = RentalJSONFileRepository(settings.get_rentals_file_name())

else:
    raise ValueError("We dont know which repo to use. :(")

client_service = ClientService(client_repo, client_validator, rental_repo, undo_service)
book_service = BookService(book_repo, book_validator, rental_repo, undo_service)
rental_service = RentalService(rental_repo, book_service, client_service, undo_service)

# i do this because i need the services to exist to add the dummy data
if settings.get_repository_type() == "inmemory":
    Helper.add_books(book_service)
    Helper.add_clients(client_service)

# Helper.add_books(book_service)
# Helper.add_clients(client_service)
# rental_repo.add_dummy_data()
undo_service.restart()

ui_type = settings.get_ui_type().lower().strip()
if ui_type == "ui":
    ui = UI(book_service, client_service, rental_service, undo_service)
    ui.start()
elif ui_type == "gui":
    import sys

    app = QtWidgets.QApplication(sys.argv)
    MainWindow = QtWidgets.QMainWindow()
    ui = Ui_MainWindow()
    ui.setupUi(MainWindow, book_repo, client_repo, rental_repo)
    MainWindow.show()
    sys.exit(app.exec_())
else:
    print("UI or GUI, nothing else!")
#
# print("1. UI\n")
# print("2. GUI\n")
# command = input("Which one do you want to use? Answer: ")
# if command.strip() == "1":
#     ui = UI(book_service, client_service, rental_service, undo_service)
#     ui.start()
# elif command.strip() == "2":
#     import sys
#
#     app = QtWidgets.QApplication(sys.argv)
#     MainWindow = QtWidgets.QMainWindow()
#     ui = Ui_MainWindow()
#     ui.setupUi(MainWindow)
#     MainWindow.show()
#     sys.exit(app.exec_())
#
# else:
#     print("No no, someone doesnt know how to read or write.")
