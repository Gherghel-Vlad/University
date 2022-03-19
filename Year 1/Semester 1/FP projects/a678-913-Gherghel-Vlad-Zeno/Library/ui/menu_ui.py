class UI:
    def __init__(self, book_service, client_service, rental_service, undo_service):
        self._book_service = book_service
        self._client_service = client_service
        self._rental_service = rental_service
        self._undo_service = undo_service

    @staticmethod
    def show_menu_commands():
        print("Books commands:\n")
        print("1 Show all the books")
        print("2 Add a new book")
        print("3 Delete a book")
        print("4 Update a book \n")

        print("Client commands: \n")
        print("5 Show all clients")
        print("6 Add a new client")
        print("7 Delete a client")
        print("8 Update a client \n")

        print("Rental commands: \n")
        print("9 Show rentals")
        print("10 Rent book")
        print("11 Return book \n")

        print("Searches: \n")
        print("12 Search books")
        print("13 Search clients\n")

        print("Statistics: \n")
        print("14 Most rented books")
        print("15 Most active clients")
        print("16 Most rented author")
        print("17 Undo last operation")
        print("18 Redo last operation")

        print("0 Exit\n")

    @staticmethod
    def read_user_command():
        """
        Reads the user's command number
        :return: The user's command number
        """
        return input("Give a command master: ").strip().lower()

    def show_books_ui(self):
        print(self._book_service.list_books())

    def add_book_ui(self):
        book_id = input("Book id: ").strip()
        title = input("Book title: ").strip()
        author = input("Book author: ").strip()
        self._book_service.add_book(book_id, title, author)
        print("Book was added.")

    def delete_book_ui(self):
        book_id = input("Book id: ").strip()
        self._book_service.remove_book(book_id)
        self._rental_service.delete_rentals_by_book_id(book_id)
        print("Successfully deleted the book. (rentals as well)")

    def update_book_ui(self):
        book_id = input("Book id: ").strip()
        print("Leave empty if you dont want to update that part.")
        new_title = input("New title: ").strip()
        new_author = input("New author: ").strip()
        self._book_service.update_book(book_id, new_title, new_author)
        print("Book updated.")

    def show_clients_ui(self):
        print(self._client_service.list_client())

    def add_client_ui(self):
        client_id = input("Client id: ").strip()
        name = input("Name: ").strip()
        self._client_service.add_client(client_id, name)
        print("Added client successfully.")

    def delete_client_ui(self):
        client_id = input("Client id: ").strip()
        self._client_service.remove_client(client_id)
        self._rental_service.delete_rentals_by_client_id(client_id)
        print("Deleted client successfully (rentals as well)")

    def update_client_ui(self):
        client_id = input("Client id: ").strip()
        name = input("Name: ").strip()
        self._client_service.update_client(client_id, name)
        print("Updated client successfully.")

    def show_rentals(self):
        print(self._rental_service.rental_list())

    def rent_book_ui(self):
        rental_id = input("Rental id: ")
        book_id = input("Book id: ")
        client_id = input("Client id: ")
        self._rental_service.rent_book(rental_id, book_id, client_id)
        print("Rented successfully.")

    def return_book_ui(self):
        book_id = input("Book id: ")
        self._rental_service.return_book(book_id)
        print("Returned successfully.")

    def search_books_ui(self):
        number = input("Where do you want to search? \n1 Book id\n2 Title\n3 Author\nNumber: ")
        number = number.strip().lower()
        if number == "1":
            value = input("Substring book id to search for: ")
            value = value.strip().lower()
            print(self._book_service.search_books_by_id(value))
        elif number == "2":
            value = input("Substring book title to search for: ")
            value = value.strip().lower()
            print(self._book_service.search_books_by_title(value))
        elif number == "3":
            value = input("Substring book author to search for: ")
            value = value.strip().lower()
            print(self._book_service.search_books_by_author(value))
        else:
            print("Wrong number.")

    def search_clients_ui(self):
        number = input("Where do you want to search? \n1 Client id\n2 Name\nNumber: ")
        number = number.strip().lower()
        if number == "1":
            value = input("Substring client id to search for: ")
            value = value.strip().lower()
            print(self._client_service.search_clients_by_id(value))
        elif number == "2":
            value = input("Substring client name to search for: ")
            value = value.strip().lower()
            print(self._client_service.search_clients_by_name(value))
        else:
            print("Wrong number.")

    def most_rented_books_ui(self):
        result = self._rental_service.most_rented_books()
        for r in result:
            print(r)

    def most_active_clients_ui(self):
        result = self._rental_service.most_active_clients()
        for r in result:
            print(r)

    def most_rented_authors_ui(self):
        result = self._rental_service.most_rented_authors()
        for r in result:
            print(r)

    def undo(self):
        result = self._undo_service.undo()
        if result is True:
            print("Successful undo")
        else:
            print("There are no undoes to be made")

    def redo(self):
        result = self._undo_service.redo()
        if result is True:
            print("Successful redo")
        else:
            print("There are no redoes to be made")

    def start(self):
        done = False

        command_dict = {"1": self.show_books_ui, "2": self.add_book_ui, "3": self.delete_book_ui,
                        "4": self.update_book_ui, "5": self.show_clients_ui, "6": self.add_client_ui,
                        "7": self.delete_client_ui, "8": self.update_client_ui, "9": self.show_rentals,
                        "10": self.rent_book_ui, "11": self.return_book_ui, "12": self.search_books_ui,
                        "13": self.search_clients_ui, "14": self.most_rented_books_ui,
                        "15": self.most_active_clients_ui, "16": self.most_rented_authors_ui, "17": self.undo,
                        "18": self.redo}

        while not done:
            try:
                self.show_menu_commands()
                command = self.read_user_command()
                if command == "0":
                    done = True
                elif command in command_dict:
                    command_dict[command]()
                else:
                    print("No such command exists. Try again.")
            except ValueError as msg:
                print(msg)
