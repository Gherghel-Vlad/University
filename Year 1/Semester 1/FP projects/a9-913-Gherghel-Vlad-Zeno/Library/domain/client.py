class ClientException(Exception):
    def __init__(self, msg):
        super().__init__(msg)


class ClientValidator:
    pass


class Client:
    def __init__(self, client_id, name):
        self._client_id = client_id
        self.name = name

    @property
    def client_id(self):
        return self._client_id

    @property
    def name(self):
        return self._name

    @name.setter
    def name(self, value):
        self._name = value

    def __str__(self):
        return "Id: " + str(self.client_id) + " Name: " + str(self.name)

