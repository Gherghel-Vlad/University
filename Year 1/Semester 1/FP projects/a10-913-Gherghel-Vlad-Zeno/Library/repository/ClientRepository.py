from Library.data_structures.IterableDataStructure import IterableDataStructure, filter_list
from Library.domain.client import Client


class ClientRepositoryException(Exception):
    def __init__(self, msg):
        super().__init__(msg)


class ClientRepository:
    def __init__(self):
        self._client_list = IterableDataStructure()

    @property
    def client_list(self):
        """
        Returns the whole list of clients
        :return: THe list of clients (list of Client objects)
        """
        return self._client_list.list

    def add_client(self, client):
        """
        Adds a Client instance to the list of clients
        :param client: The instance of the client (Client object)
        :return: -
        Raises ClientRepositoryException if there is already a client with that id
        """
        if self.find(client.client_id) != -1:
            raise ClientRepositoryException("There s already a client with the same id " + str(client.client_id))

        self._client_list.append(client)

    def remove_client(self, id_):
        """
        Deletes the client with the given id
        :param id_: The given id of the client to be deleted
        :return: -
        Raises ClientRepositoryException if there is no cleint with the given id
        """
        index = self.find(id_)

        if index == -1:
            raise ClientRepositoryException("There s no client with the given id: " + str(id_))

        del self._client_list[index]

    def update_client(self, id_, new_name):
        """
        Updates the client with the given id
        :param id_: The id that will show which client to be updated
        :param new_name: The new name of the client
        :return: -
        Raises ClientRepositoryException if the client with the given id does not exist
        """
        index = self.find(id_)
        if index == -1:
            raise ClientRepositoryException("There s no client with the given id: " + str(id_))
        if self._client_list[index].name == new_name:
            raise ClientRepositoryException("The client already has this name")

        self._client_list[index].name = new_name

    def find(self, id_):
        """
        Searches for the index of the Client with the given id
        :param id_: The id of the client
        :return: The index or -1 if it isn't found
        """
        for index in range(0, len(self._client_list)):
            if id_ == self._client_list[index].client_id:
                return index
        return -1

    def find_by_client_id(self, id_):
        """
        Searches for the client with the given id
        :param id_: The id of the client
        :return: The client object or None if it wasn't found
        """
        for index in range(0, len(self._client_list)):
            if id_ == self._client_list[index].client_id:
                return self._client_list[index]
        return None

    def search_clients_by_id(self, value):
        """
        Searches if a client id contains the value by doing a substring case-insensitive search
        :param value: The value it searches
        :return: A list containing all the clients found
        """
        return filter_list(self.client_list, lambda x: str(value).lower() in str(x.client_id).lower())

    def search_clients_by_name(self, value):
        """
        Searches if a client name contains the value by doing a substring case-insensitive search
        :param value: The value it searches
        :return: A list containing all the clients found
        """
        return filter_list(self.client_list, lambda x: str(value).lower() in str(x.name).lower())

    def __getitem__(self, client_id):
        """
        Returns the client with the given id
        :param client_id: The given id (string)
        :return: A client instance that has the given id
        Raises ClientRepositoryException if the client with the given id does not exist
        """
        for client in self.client_list:
            if client.client_id == client_id:
                return client
        raise ClientRepositoryException("There is no client with the given id")

    def __str__(self):
        """
        Creates a string representation of the repository
        :return: A string representation of the repository
        """
        representation = "Library Clients: \n"
        for client in self._client_list:
            representation += str(client) + "\n"
        if len(self._client_list) == 0:
            representation += "There are no clients yet."
        return representation

    def __len__(self):
        return len(self._client_list)
