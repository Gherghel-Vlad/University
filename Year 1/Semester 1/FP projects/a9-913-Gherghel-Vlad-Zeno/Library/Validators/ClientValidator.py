from Library.domain.client import Client


class ClientValidatorException(Exception):
    def __init__(self, msg):
        super().__init__(msg)


class ClientValidator:
    @staticmethod
    def validate_client(client):
        if not isinstance(client, Client):
            raise ClientValidatorException("Variable needs to be an instance of Client class")

        ClientValidator.validate_client_id(client.client_id)
        ClientValidator.validate_client_name(client.name)

    @staticmethod
    def validate_client_name(name):
        if not isinstance(name, str):
            raise ClientValidatorException("Client name must be string types.")

        if name == "" or len(name) == 0:
            raise ClientValidatorException("Client name must not be empty.")

    @staticmethod
    def validate_client_id(id_):
        if not isinstance(id_, str):
            raise ClientValidatorException("Client id must be string types.")

        if id_ == "" or len(id_) < 0:
            raise ClientValidatorException("Client id incorrect. It must have at least a character.")


