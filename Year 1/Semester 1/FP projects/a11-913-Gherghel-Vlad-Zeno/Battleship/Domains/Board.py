from Battleship.Domains.Point import Point
from texttable import Texttable


class BoardException(Exception):
    def __init__(self, ms):
        self._ms = ms
        super().__init__(ms)

    @property
    def ms(self):
        return self._ms

    def __eq__(self, other):
        return self.ms == other.ms


class Board:
    def __init__(self, number_of_rows=10, number_of_columns=10):
        # The board is 10x10
        self._columns = number_of_rows
        self._rows = number_of_columns

        self._board = [[0 for j in range(self._columns)] for i in range(self._rows)]

        # self._destroyer_coordinates = []
        # self._submarine_coordinates = []
        # self._cruiser_coordinates = []
        # self._battleship_coordinates = []
        # self._carrier_coordinates = []

        self._ships_coordinates = []

    @property
    def board(self):
        return self._board

    @property
    def number_of_rows(self):
        return self._rows

    @property
    def number_of_columns(self):
        return self._columns

    @property
    def ships_coordinates(self):
        return self._ships_coordinates

    def get(self, point):
        """
        Returns the symbol from the (x,y) coordinates
        :param point: A point instance having the (x, y) coordinates
        :return: The symbol from the given point
        """
        return self._board[point.x][point.y]

    def set(self, point, value):
        """
        2 - hit
        1 - missed
        0 - empty (nothing happened to that cell)
        -1 - destroyer
        -2 - submarine
        -3 - cruiser
        -4 - battleship
        -5 - carrier
        :param point: The coordinates where the set the value
        :param value: The value to be set (it s one of the values from above)
        :return: -
        """
        self._board[point.x][point.y] = value

    def ship_value_type_to_name(self, ship_value_type):
        """
        Transforms the ship type value into it's ship's name
        :param ship_value_type: The ship type value (-1, -2, -3, -4, -5)
        :return: A string that represents the name of that ship
        """
        if ship_value_type == -1:
            return "Destroyer"
        elif ship_value_type == -2:
            return "Submarine"
        elif ship_value_type == -3:
            return "Cruiser"
        elif ship_value_type == -4:
            return "Battleship"
        elif ship_value_type == -5:
            return "Cruiser"
        else:
            raise BoardException("Ship type incorrect!")

    def isnt_in_board(self, point):
        """
        Checks if the point is inside the board
        :param point: A point instance
        :return: Returns false if it is, returns true if it isn't
        """
        if point.x < 0 or point.x > self._rows - 1 or point.y < 0 or point.y > self._columns - 1:
            return True
        return False

    def intersects_other_ships(self, start, end):
        """
        Checks if the new ship coordinates intersects with other coordinates from other ships
        :param start: The start point instance of the new ship
        :param end: The end point instance of the enw ship
        :return: -
        raises BoardException is it does intersect with other ships
        """
        # saving the coordinates of the destroyer
        if start.x == end.x:  # the case in which the ship is put horizontally
            if start.y > end.y:
                start.y, end.y = end.y, start.y

            for y in range(start.y, end.y + 1):
                if Point(start.x, y) in self._ships_coordinates:
                    raise BoardException("Can't put ship there! It intersects another ship!")

        else:  # the case in which the ship is put vertically
            if start.x > end.x:
                start.x, end.x = end.x, start.x

            for x in range(start.x, end.x + 1):
                if Point(x, start.y) in self._ships_coordinates:
                    raise BoardException("Can't put ship there! It intersects another ship!")

    def check_position_and_length(self, start, end, ship_value_type):
        """
        Checks if the new ship has been placed correctly
        :param start: The start point instance of the new ship
        :param end: The end point instance of the new ship
        :param ship_value_type: The value type that represents what type of new ship it is (integer)
        :return: -
        raises BoardException if the ship type is incorrect
        raises BoardException if the ship wasn't placed horizontally or vertically
        raises BoardException if the ship wasn't placed on the length it needs
        """
        if ship_value_type == -1:  # destroyers occupy 2 positions
            length = 1
        elif ship_value_type == -2 or ship_value_type == -3:  # submarines and cruisers 3 pos
            length = 2
        elif ship_value_type == -4:  # battleships 4 positions
            length = 3
        elif ship_value_type == -5:  # carrier 5 positions
            length = 4
        else:
            raise BoardException("Ship type incorrect!")
        # checking if the coordinates aren't outside the bounds
        if self.isnt_in_board(start) or self.isnt_in_board(end):
            raise BoardException("Invalid coordinates! Coordinates outside the bounds!")
        # Checking if it was put horizontally or vertically
        if start.x != end.x and start.y != end.y:
            raise BoardException("Ships can be placed only vertically or horizontally!")
        # Checking if the given coordinates have the right length
        if Point.distance(start, end) != length:
            raise BoardException("The " + self.ship_value_type_to_name(ship_value_type) +
                                 " needs to be placed on " + str(length + 1) + " positions!")

        self.intersects_other_ships(start, end)

    def set_ship(self, start, end, ship_value_type):
        """
        Sets the ship in between those coordinates
        :param start: The start point instance of the new ship
        :param end: The end point instance of the new ship
        :param ship_value_type: An integer that represent what type if ship to be put
        :return: -
        """
        self.check_position_and_length(start, end, ship_value_type)

        # saving the coordinates of the destroyer
        if start.x == end.x:  # the case in which the ship is put horizontally
            if start.y > end.y:
                start.y, end.y = end.y, start.y

            for index in range(start.y, end.y + 1):
                self._ships_coordinates.append(Point(start.x, index))
                self.set(Point(start.x, index), ship_value_type)
        else:  # the case in which the ship is put vertically
            if start.x > end.x:
                start.x, end.x = end.x, start.x

            for index in range(start.x, end.x + 1):
                self._ships_coordinates.append(Point(index, start.y))
                self.set(Point(index, start.y), ship_value_type)

    def delete_ship_coordinate(self, point):
        """
        Deletes the point from the ships coordinates
        :param point: A point instance
        :return: -
        """
        for index in range(0, len(self._ships_coordinates)):
            if self._ships_coordinates[index] == point:
                del self._ships_coordinates[index]
                return

    def shoot_at(self, point):
        """
        Represents the action in which someone shoots at that position
        :param point: A point instance representing where the shot is taken at
        :return: -
        raises BoardException if the position given is out of bounds
        raises BoardException if the position has already been hit before
        """
        # Check if the point is in bounds
        if self.isnt_in_board(point):
            raise BoardException("Position given is out of bounds!")

        # Check if it wasn't hit before
        if self.get(point) in [1, 2]:
            raise BoardException("Position already hit before! Try again.")

        if self.get(point) in [-1, -2, -3, -4, -5]:  # if it hit a ship
            ship_value_type = self.get(point)
            self.set(point, 2)  # set the point as a hit cell
            self.delete_ship_coordinate(point)
            # Check if I didnt finish the game
            if len(self._ships_coordinates) == 0:
                raise BoardException("You won!")
            raise BoardException(self.ship_value_type_to_name(ship_value_type) + " hit!")
        else:
            self.set(point, 1)  # set the coordinates as a miss cell
            raise BoardException("Miss!")

    def __str__(self):
        t = Texttable()
        t.header([" ", "1", "2", "3", "4", "5", "6", "7", "8", "9", "10"])
        letter_list = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j"]
        for row in range(self._rows):
            row_data = []

            for val in self._board[row]:
                if val == 2:
                    row_data.append("X")
                elif val == 1:
                    row_data.append("O")
                elif val in [-1, -2, -3, -4, -5]:
                    row_data.append("S")
                else:
                    row_data.append(" ")

            t.add_row([letter_list[row].upper()] + row_data)

        return t.draw()

#
# board = Board()
# board.set_ship(Point(0, 0), Point(1, 0), -1)
# board.set_ship(Point(2, 1), Point(2, 3), -2)
# board.set_ship(Point(2, 9), Point(4, 9), -3)
# board.set_ship(Point(5, 5), Point(5, 8), -4)
# board.set_ship(Point(7, 2), Point(7, 6), -5)
# print(str(board))
#
# while True:
#     x = input("X : ")
#     y = input("Y : ")
#
#     try:
#         board.shoot_at(Point(int(x.strip()), int(y.strip())))
#     except Exception as val:
#         print(val)
#         if val == BoardException("You won!"):
#             break
#
#     print(str(board))
