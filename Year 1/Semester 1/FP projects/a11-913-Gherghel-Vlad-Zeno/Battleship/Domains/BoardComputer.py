from texttable import Texttable
import random
from Battleship.Domains.Board import Board, BoardException
from Battleship.Domains.Options import Options
from Battleship.Domains.Point import Point
from Battleship.Domains.Strategy import Strategy


class BoardComputer(Board):
    def __init__(self, number_of_rows, number_of_columns, strategy):
        super().__init__(number_of_rows, number_of_columns)
        self._strategy = strategy
        self.set_ships()

    def get_length_ship(self, ship_value_type):
        """
        Gets the length of the ship by it's ship value type
        :param ship_value_type: The value representing the type of the ship [-1, -2, -3, -4, -5]
        :return: An integer representing the length of the ship
        """
        if ship_value_type == -1:
            return 1
        if ship_value_type == -2:
            return 2
        if ship_value_type == -3:
            return 2
        if ship_value_type == -4:
            return 3
        if ship_value_type == -5:
            return 4

    def set_ships(self):
        """
        Sets the ships of the computer's board
        :return: -
        """
        ship_value_type = -1
        points_list = [Point(1, 0), Point(-1, 0), Point(0, -1), Point(0, 1)]
        while ship_value_type > -6:
            try:
                start_point = Point(random.randint(0, 9), random.randint(0, 9))
                nr = random.randint(0, 3)
                end_point = start_point
                for i in range(0, self.get_length_ship(ship_value_type)):
                    end_point = points_list[nr] + end_point
                self.set_ship(start_point, end_point, ship_value_type)
                ship_value_type -= 1
            except Exception:
                continue


    def get_point_where_to_shoot(self, enemy_board):
        """
        Gets the point to which the computer shoots
        :param enemy_board: The player's board
        :return: A point instance indicating where the computer will shoot next
        """
        return self._strategy.difficulty_case(enemy_board)

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

# options = Options()
# options.set_difficulty("normal")
#
# strategy = Strategy(options)
#
# computer_board = BoardComputer(10, 10, strategy)
# print(str(computer_board))
#
# while True:
#     x = input("Next ")
#     point = computer_board.get_point_where_to_shoot(board)
#     try:
#         board.shoot_at(point)
#     except Exception as val:
#         print(val)
#         if val == BoardException("You won!"):
#             break
#
#     print(str(board))
