import unittest

from Battleship.Domains.Board import Board, BoardException
from Battleship.Domains.Point import Point


class TestBoardClass(unittest.TestCase):
    def setUp(self):
        self.board = Board(10, 10)

    def set_ships(self):
        self.board.set_ship(Point(0, 0), Point(1, 0), -1)
        self.board.set_ship(Point(2, 1), Point(2, 3), -2)
        self.board.set_ship(Point(2, 9), Point(4, 9), -3)
        self.board.set_ship(Point(5, 5), Point(5, 8), -4)
        self.board.set_ship(Point(7, 2), Point(7, 6), -5)

    def test_properties(self):
        self.assertEqual(self.board.board, [[0 for j in range(10)] for i in range(10)])
        self.assertEqual(self.board.number_of_rows, 10)
        self.assertEqual(self.board.number_of_columns, 10)
        self.assertEqual(self.board.ships_coordinates, [])

    def test_get(self):
        self.set_ships()
        self.assertEqual(self.board.get(Point(0, 0)), -1)
        self.assertEqual(self.board.get(Point(7, 2)), -5)

    def test_set(self):
        self.board.set(Point(0, 0), 2)
        self.assertEqual(self.board.board[0][0], 2)

    def test_ship_value_type_to_name(self):
        self.assertEqual(self.board.ship_value_type_to_name(-1), "Destroyer")
        self.assertEqual(self.board.ship_value_type_to_name(-2), "Submarine")
        self.assertEqual(self.board.ship_value_type_to_name(-3), "Cruiser")
        self.assertEqual(self.board.ship_value_type_to_name(-4), "Battleship")
        self.assertEqual(self.board.ship_value_type_to_name(-5), "Cruiser")

        with self.assertRaises(BoardException):
            self.board.ship_value_type_to_name(-6)

    def test_isnt_in_board(self):
        self.assertEqual(self.board.isnt_in_board(Point(-1,-1)), True)
        self.assertEqual(self.board.isnt_in_board(Point(1,1)), False)

    def test_intersects_other_ships(self):
        self.set_ships()
        with self.assertRaises(BoardException):
            self.board.intersects_other_ships(Point(0, 0), Point(2, 0))
        with self.assertRaises(BoardException):
            self.board.intersects_other_ships(Point(2, 0), Point(0, 0))
        with self.assertRaises(BoardException):
            self.board.intersects_other_ships(Point(0, 0), Point(0, 2))
        with self.assertRaises(BoardException):
            self.board.intersects_other_ships(Point(0, 2), Point(0, 0))

    def test_check_position_and_length(self):
        self.set_ships()
        with self.assertRaises(BoardException):
            self.board.check_position_and_length(Point(0, 2), Point(0, 0), -8)
        with self.assertRaises(BoardException):
            self.board.check_position_and_length(Point(-1, 2), Point(0, 0), -1)
        with self.assertRaises(BoardException):
            self.board.check_position_and_length(Point(0, 2), Point(0, -1), -1)
        with self.assertRaises(BoardException):
            self.board.check_position_and_length(Point(0, 0), Point(1, 1), -1)
        with self.assertRaises(BoardException):
            self.board.check_position_and_length(Point(0, 0), Point(5, 0), -1)

    def test_set_ship(self):
        self.set_ships()
        with self.assertRaises(BoardException):
            self.board.set_ship(Point(1, 1), Point(4, 2), -1)

        self.board.set_ship(Point(1, 1), Point(1, 2), -1)
        self.assertEqual(self.board.board[1][1], -1)
        self.assertEqual(self.board.board[1][2], -1)
        self.board.set_ship(Point(4, 2), Point(4, 1), -1)
        self.assertEqual(self.board.board[4][2], -1)
        self.assertEqual(self.board.board[4][1], -1)
        self.board.set_ship(Point(3, 3), Point(4, 3), -1)
        self.assertEqual(self.board.board[3][3], -1)
        self.assertEqual(self.board.board[4][3], -1)
        self.board.set_ship(Point(9, 8), Point(8, 8), -1)
        self.assertEqual(self.board.board[8][8], -1)
        self.assertEqual(self.board.board[9][8], -1)

    def test_delete_ship_coordinate(self):
        self.set_ships()
        self.board.delete_ship_coordinate(Point(0, 0))
        self.assertNotIn(Point(0, 0), self.board.ships_coordinates)

    def test_shoot_at(self):
        self.set_ships()
        with self.assertRaises(BoardException):
            self.board.shoot_at(Point(0, -5))
        with self.assertRaises(BoardException):
            self.board.shoot_at(Point(0, 0))
        self.assertEqual(self.board.get(Point(0, 0)), 2)
        with self.assertRaises(BoardException):
            self.board.shoot_at(Point(0, 0))

        with self.assertRaises(BoardException):
            self.board.shoot_at(Point(9, 9))
        self.assertEqual(self.board.get(Point(9, 9)), 1)

    def test_str(self):
        self.set_ships()
        self.assertEqual(str(self.board), str(self.board))




