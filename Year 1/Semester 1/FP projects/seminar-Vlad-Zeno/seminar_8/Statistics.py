from datetime import date

from seminar_6.car_rental.entitities.client_validator import ClientValidator
from seminar_8.domain.rental import RentalValidator
from seminar_8.repository.repository import Repository
from seminar_8.services.CarService import CarService
from seminar_8.services.ClientService import ClientService
from seminar_8.services.RentalService import RentalService


class CarValidatorRO:
    pass


def statistics_example():
    """
    An example for the creation of statistics.
    Several cars, clients and rentals are created and then statistics are calculated over them.

    Implement the following statistics:
        - "Most rented cars". The list of cars, sorted by the number of times they were rented
        - "Most rented cars". The list of cars, sorted by the number of days they were rented
        - "Most rented car make". The list of car makes, sorted by the number of rentals

    Follow the code below and figure out how it works!
    """

    """
        1. We initialize the required layers of the application
    """

    '''
    Start client Controller
    '''
    client_repo = Repository()
    client_validator = ClientValidator()
    client_service = ClientService(client_repo, client_validator)

    aaron = client_service.create(100, "1820203556699", "Aaron")
    bob = client_service.create(101, "2750102885566", "Bob")
    carol = client_service.create(102, "1820604536579", "Carol")

    '''
    Start car Controller
    '''
    car_repo = Repository()
    car_validator = CarValidatorRO()
    car_service = CarService(car_repo, car_validator)

    audi_a3 = car_service.create(200, "CJ 01 AAA", "Audi", "A3")
    audi_a4 = car_service.create(201, "CJ 01 BBB", "Audi", "A4")
    audi_a5 = car_service.create(202, "CJ 01 CCC", "Audi", "A5")
    audi_a6 = car_service.create(203, "CJ 01 DDD", "Audi", "A6")
    audi_a7 = car_service.create(204, "CJ 01 EEE", "Audi", "A7")
    vw_polo = car_service.create(205, "CJ 01 FFF", "VW", "Polo")
    vw_passat = car_service.create(206, "CJ 01 GGG", "VW", "Passat")
    vw_golf = car_service.create(207, "CJ 01 HHH", "VW", "Golf")
    dacia_lodgy = car_service.create(208, "CJ 01 ERT", "Dacia", "Lodgy")
    dacia_duster = car_service.create(209, "CJ 01 YTH", "Dacia", "Duster")

    '''
    Start rental Controller
    '''
    rent_repo = Repository()
    rent_validator = RentalValidator()
    rent_service = RentalService( rent_repo, car_repo, client_repo, rent_validator)

    rent_service.create_rental(300, aaron, audi_a3, date(2015, 11, 20), date(2015, 11, 22))
    rent_service.create_rental(301, carol, audi_a5, date(2015, 11, 24), date(2015, 11, 25))
    rent_service.create_rental(302, carol, audi_a6, date(2015, 12, 10), date(2015, 12, 12))
    rent_service.create_rental(303, aaron, audi_a4, date(2015, 11, 21), date(2015, 11, 25))
    rent_service.create_rental(304, aaron, audi_a3, date(2015, 11, 24), date(2015, 11, 27))
    rent_service.create_rental(305, bob, audi_a5, date(2015, 11, 26), date(2015, 11, 27))
    rent_service.create_rental(306, carol, audi_a6, date(2015, 12, 15), date(2015, 12, 20))
    rent_service.create_rental(307, bob, audi_a4, date(2015, 12, 1), date(2015, 12, 10))
    rent_service.create_rental(308, carol, audi_a4, date(2015, 12, 11), date(2015, 12, 15))
    rent_service.create_rental(309, aaron, audi_a5, date(2015, 11, 28), date(2015, 12, 2))

    rent_service.create_rental(310, aaron, vw_polo, date(2015, 11, 20), date(2015, 11, 22))
    rent_service.create_rental(311, carol, vw_golf, date(2015, 11, 24), date(2015, 11, 25))
    rent_service.create_rental(312, carol, vw_passat, date(2015, 12, 10), date(2015, 12, 12))
    rent_service.create_rental(313, aaron, dacia_lodgy, date(2015, 11, 21), date(2015, 11, 25))
    rent_service.create_rental(314, aaron, vw_polo, date(2015, 11, 24), date(2015, 11, 27))
    rent_service.create_rental(315, bob, vw_golf, date(2015, 11, 26), date(2015, 11, 27))
    rent_service.create_rental(316, carol, vw_golf, date(2015, 12, 15), date(2015, 12, 20))
    rent_service.create_rental(317, bob, dacia_duster, date(2015, 12, 1), date(2015, 12, 10))
    rent_service.create_rental(318, carol, dacia_duster, date(2015, 12, 11), date(2015, 12, 15))
    rent_service.create_rental(319, aaron, vw_passat, date(2015, 11, 28), date(2015, 12, 2))

    """
    Statistic 1:
        - "Most rented cars". The list of cars, sorted by the number of times they were rented
    """
    #print("Most rented cars. The list of cars, sorted by the number of times they were rented")
    #print("Times".ljust(10) + " Car".ljust(40))
    #for cr in rent_service.most_often_rented_cars():
    #    print(cr)

    #print("-" * 70)

    """
    Statistic 2:
        - "Most rented cars". The list of cars, sorted by the number of days they were rented
    """
    #print("Most rented cars. The list of cars, sorted by the number of days they were rented")
    #print("Days".ljust(10) + " Car".ljust(40))
    #for cr in rent_service.most_rented_cars():
     #   print(cr)

    #print("-" * 70)

    """
    Statistic 3:
        - "Most rented car make". The list of car makes, sorted by the number of rentals
    """
    print("Most rented car make. The list of car makes, sorted by the number of rentals")
    print("Times".ljust(10) + " Car make".ljust(40))
    for cr in rent_service.most_often_rented_car_make():
        print(cr)


statistics_example()