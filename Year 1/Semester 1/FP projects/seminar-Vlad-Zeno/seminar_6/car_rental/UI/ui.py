from seminar_6.car_rental.entitities.car_rental_exception import CarRentalException
from seminar_6.car_rental.entitities.customer_base import CustomerBase


class UI:

    @staticmethod
    def show_menu():
        print("1. Show customer list")
        print("2. Search for clients")
        print("3. Remove client by id")
        print("0. Exit")

    @staticmethod
    def read_user_command():
        return input("Give command masta: ")

    @staticmethod
    def read_user_search_word():
        return input("Give word sir: ")

    @staticmethod
    def read_user_id():
        return input("Give id m'lady: ")

    def __init__(self):
        self.customer_base = CustomerBase()
        self.customer_base.test_init()

    def show_list_customer(self):
        for client in self.customer_base.client_list:
            print(client.to_str())

    def search_clients(self):
        new_list = []
        word = UI.read_user_search_word()
        word = word.strip()
        new_list = self.customer_base.search(word)

        for client in new_list:
            print(client.to_str())

    def remove_client_by_id(self):
        id = UI.read_user_id()
        self.customer_base.remove(id)

    def start(self):
        done = False

        command_dict = {"1": self.show_list_customer, "2": self.search_clients, "3": self.remove_client_by_id}

        while not done:
            try:
                UI.show_menu()
                command = UI.read_user_command()
                if command == "0":
                    done = True
                elif command in command_dict:
                    command_dict[command]()
                else:
                    print("Bad commando")
            except CarRentalException as msg:
                print(msg)


console = UI()
console.start()
