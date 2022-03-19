import copy

from Library.domain.client import Client
from Library.repository.ClientRepository import ClientRepository
from Library.service.UndoRedoFunctionality import FunctionCall, Operation, CascadedOperation


class ClientService:
    def __init__(self, client_repo, client_validator, rental_repo, undo_service):
        self._repo = client_repo
        self._validator = client_validator
        self._rental_repo = rental_repo
        self._undo_service = undo_service

    def add_client(self, client_id, name):
        """
        Validates the variables and adds the client to the repo
        :param client_id: The id of the client instance
        :param name: The name of the client instance
        :return: -
        """
        self._validator.validate_client(Client(client_id, name))

        undo = FunctionCall(self._repo.remove_client, client_id)
        redo = FunctionCall(self._repo.add_client, Client(client_id, name))

        self._undo_service.record(Operation(undo, redo))
        self._repo.add_client(Client(client_id, name))

    def remove_client(self, client_id):
        """
        Removes the client with the given id from the repo
        :param client_id: The id of the client object
        :return: -
        """
        cascadedOp = []

        # creates the undo/redo for the removing
        client_removed = self._repo.find_by_client_id(client_id)
        self._repo.remove_client(client_id)

        redo = FunctionCall(self._repo.remove_client, client_id)
        undo = FunctionCall(self._repo.add_client, client_removed)
        cascadedOp.append(Operation(undo, redo))

        rentals = self._rental_repo.filter_by_client_id(client_id)

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

    def update_client(self, client_id, name):
        """
        Updates the client with the given id
        :param client_id: The given id
        :param name: The new name
        :return: -
        """
        self._validator.validate_client_name(name)

        client_updated = copy.deepcopy(self._repo.find_by_client_id(client_id))
        self._repo.update_client(client_id, name)

        undo = FunctionCall(self._repo.update_client, client_updated.client_id, client_updated.name)
        redo = FunctionCall(self._repo.update_client, client_id, name)

        self._undo_service.record(Operation(undo, redo))

    def list_client(self):
        """
        :return: a string representation of all the clients
        """
        return str(self._repo)

    def client_exists(self, client_id):
        """
        Checks if a client with the given id exists
        :param client_id: The id to be checked
        :return: True if it exists, False otherwise
        """
        for client in self._repo.client_list:
            if client.client_id == client_id:
                return True
        return False

    def search_clients_by_id(self, value):
        """
        Searches if a client id contains the value by doing a substring case-insensitive search
        :param value: The value it searches
        :return: A string representing the list of clients found
        """
        self._validator.validate_client_id(value)

        client_list = self._repo.search_clients_by_id(value)
        string = ""

        if len(client_list) == 0:
            string = f"No clients were found with their id containing {value}\n"
        else:
            for client in client_list:
                string += str(client) + "\n"

        return string

    def search_clients_by_name(self, value):
        """
        Searches if a client name contains the value by doing a substring case-insensitive search
        :param value: The value it searches
        :return: A string representing the list of clients found
        """
        self._validator.validate_client_name(value)

        client_list = self._repo.search_clients_by_name(value)
        string = ""

        if len(client_list) == 0:
            string = f"No clients were found with their id containing {value}\n"
        else:
            for client in client_list:
                string += str(client) + "\n"

        return string

    def get_client_by_client_id(self, client_id):
        """
        Get s the client instance with the client id given
        :param client_id: The client id given (string)
        :return: The instance of the Client class that has the client id
        """
        self._validator.validate_client_id(client_id)
        return self._repo[client_id]
