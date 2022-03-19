from Library.Validators.BookValidator import BookValidator, BookValidatorException
from Library.Validators.ClientValidator import ClientValidator, ClientValidatorException
from Library.domain.rental import Rental


class RentalValidatorException(Exception):
    def __init__(self, msg):
        super().__init__(msg)


class RentalValidator:
    @staticmethod
    def validate_rental_id(rental_id):
        if rental_id == "" or rental_id is None:
            raise RentalValidatorException("Rental is has to have a value")

    @staticmethod
    def validate_book_id(book_id):
        try:
            BookValidator.validate_book_id(book_id)
        except BookValidatorException as msg:
            raise RentalValidatorException(msg)

    @staticmethod
    def validate_client_id(client_id):
        try:
            ClientValidator.validate_client_id(client_id)
        except ClientValidatorException as msg:
            raise RentalValidatorException(msg)

    @staticmethod
    def validate_rental(rental):
        if not isinstance(rental, Rental):
            raise RentalValidatorException("Rental validator needs to het a rental instance")

        RentalValidator.validate_client_id(rental.client_id)
        RentalValidator.validate_client_id(rental.book_id)
        RentalValidator.validate_client_id(rental.rental_id)

