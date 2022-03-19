from seminar_6.car_rental.UI.ui import UI

# Car stuff
car_repo = CarRepo()
car_validator = CarValidator()
car_service = CarService(car_repo)

# Client stuff
client_repo = ClientRepo()
client_service = ClienService(client_repo)

# Rental stuff
rental_repo = RentalRepo()
rental_service = RentalService(rental_repo, car_repo, client_repo)


ui = UI()
ui.start()