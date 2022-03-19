class CarRentalException(Exception):
    def __init__(self, msg):
        self._msg = msg
