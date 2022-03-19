from datetime import datetime

from Library.domain.client import Client
from Library.domain.rental import Rental


class Helper:
    @staticmethod
    def add_clients(client_service):
        client_service.add_client("23", "Alex Tran")
        client_service.add_client("27", "Mar Car")
        client_service.add_client("30", "Sig Frei")
        client_service.add_client("43", "Saltra Mahak")
        client_service.add_client("50", "Reta DeMildo")
        client_service.add_client("65", "Frunza Macel")
        client_service.add_client("66", "Ale Crei")
        client_service.add_client("68", "Mira Trai")
        client_service.add_client("69", "Saral Mahalaji")
        client_service.add_client("71", "Sirun Safar")
        client_service.add_client("73", "Kimiko Yui")

    @staticmethod
    def add_clients_append(list):
        list.append(Client("23", "Alex Tran"))
        list.append(Client("27", "Mar Car"))
        list.append(Client("30", "Sig Frei"))
        list.append(Client("43", "Saltra Mahak"))
        list.append(Client("50", "Reta DeMildo"))
        list.append(Client("65", "Frunza Macel"))
        list.append(Client("66", "Ale Crei"))
        list.append(Client("68", "Mira Trai"))
        list.append(Client("69", "Saral Mahalaji"))
        list.append(Client("71", "Sirun Safar"))
        list.append(Client("73", "Kimiko Yui"))

    @staticmethod
    def add_books(_book_service):
        _book_service.add_book("23", "Ala", "Jiran")
        _book_service.add_book("44", "Ale", "Malane")
        _book_service.add_book("45", "Cala", "Rekurda")
        _book_service.add_book("64", "Sala", "Melon")
        _book_service.add_book("61", "Mahoi", "Majai")
        _book_service.add_book("53", "Frayte", "Recai")
        _book_service.add_book("2", "Sinampso", "Teresque")
        _book_service.add_book("22", "Kalei", "Opale")
        _book_service.add_book("11", "Hatete", "Ocuranez")
        _book_service.add_book("345", "Temow", "Kilmano")

    @staticmethod
    def rent_books(_rental_service):
        _rental_service.rent_book("10", "23", "50", datetime(2018, 11, 20, 12, 11), datetime(2018, 11, 22, 13, 5))
        _rental_service.rent_book("14", "23", "68", datetime(2019, 7, 22, 15, 22), datetime(2019, 7, 29, 16, 00))
        _rental_service.rent_book("115", "61", "43", datetime(2014, 11, 20, 12, 11), None)
        _rental_service.rent_book("16", "44", "50", datetime(2020, 2, 11, 10, 20), datetime(2020, 3, 21, 11, 30))
        _rental_service.rent_book("120", "45", "23", datetime(2020, 3, 20, 14, 22), datetime(2020, 4, 5, 15, 30))
        _rental_service.rent_book("22", "53", "69", datetime(2020, 3, 20, 14, 25), datetime(2020, 4, 7, 16, 00))
        _rental_service.rent_book("23", "53", "23", datetime(2020, 5, 23, 18, 25), datetime(2020, 6, 4, 22, 00))
        _rental_service.rent_book("24", "2", "71", datetime(2020, 6, 5, 15, 30), datetime(2020, 7, 10, 12, 00))
        _rental_service.rent_book("26", "11", "23", datetime(2020, 8, 20, 17, 30), datetime(2020, 8, 23, 18, 25))
        _rental_service.rent_book("44", "345", "73", datetime(2020, 10, 20, 19, 25), datetime(2020, 11, 1, 15, 00))
