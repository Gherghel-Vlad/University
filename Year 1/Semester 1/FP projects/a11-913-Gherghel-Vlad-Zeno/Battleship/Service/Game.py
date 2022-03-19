from Battleship.Domains.Board import BoardException
from Battleship.Domains.Point import Point


class GameException(Exception):
    def __init__(self, ms):
        self._ms = ms
        super().__init__(ms)

    @property
    def ms(self):
        return self._ms

    def __eq__(self, other):
        return other.ms == self._ms


class Game:
    def __init__(self, player_board, computer_board):
        self._player_board = player_board
        self._computer_board = computer_board

    def convert_coordinates_to_point(self, coordinates):
        """
        Converts the given string that contains the the coordinates (ex: A8, B7) into its respective point instance
        :param coordinates: A string representing the coordinates given by the player
        :return: A point instance representing the point to which the player refers to
        raises GameException if the given coordinates are invalid
        """
        if coordinates == "":
            raise GameException("Invalid coordinates!")
        letter_list = ["a", "b", "c", "d", "e", "f", "g", "h", "i", "j"]
        number_list = ["1", "2", "3", "4", "5", "6", "7", "8", "9", "10"]
        coordinates = str(coordinates).strip()
        letter = coordinates[0].lower()
        coordinates = coordinates[1:]
        number = coordinates.strip()
        if letter not in letter_list or number not in number_list:
            raise GameException("Invalid coordinates!")
        return Point(letter_list.index(letter), number_list.index(number))

    def set_player_ship(self, start, end, ship_value_type):
        """
        Sets the one of the ships of the player
        :param start: The start position of the ship
        :param end: The end position of the ship
        :param ship_value_type: The ship type value {-1, -2, -3, -4, -5}
        :return: -
        """
        self._player_board.set_ship(self.convert_coordinates_to_point(start), self.convert_coordinates_to_point(end),
                                    ship_value_type)

    def player_shoot(self, coordinates):
        """
        Shoots at the computer's board point location
        :param coordinates: The coordinates given by the player (ex: A8, B7)
        :return: -
        """
        try:
            self._computer_board.shoot_at(self.convert_coordinates_to_point(coordinates))
        except Exception as val:
            if val == BoardException("You won!"):
                raise GameException("Lucky bastard... you won...")
            else:
                raise val

    def computer_shoot(self):
        """
        Makes the computer to take a shot
        :return: -
        """
        try:
            point = self._computer_board.get_point_where_to_shoot(self._player_board)
            self._player_board.shoot_at(point)
        except Exception as val:
            if val == BoardException("You won!"):
                raise GameException("Computer won! Loser :)")
            else:
                raise val

    def get_computer_board_string(self):
        """
        Prints the game's boards
        :return: A string representing the player's and the computer's board
        """
        return str(self._computer_board)

    def get_player_board_string(self):
        """
        Gets the representation as a string of the player's table
        :return: A string representing the player's board
        """
        return str(self._player_board)

# game = Game([], [])
# point = game.convert_coordinates_to_point("3g")
# print(str(point.x))
# print(str(point.y))
