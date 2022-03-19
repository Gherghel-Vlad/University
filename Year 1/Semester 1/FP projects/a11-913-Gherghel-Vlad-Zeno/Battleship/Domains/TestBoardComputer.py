import unittest

from Battleship.Domains.Board import BoardException, Board
from Battleship.Domains.BoardComputer import BoardComputer
from Battleship.Domains.Options import Options
from Battleship.Domains.Strategy import Strategy


class TestBoardComputerClass(unittest.TestCase):
    def setUp(self):
        self.board = Board(10, 10)
        options = Options()
        strategy = Strategy(options)

        self.computer_board = BoardComputer(10, 10, strategy)

    def test_get_length_ship(self):
        self.assertEqual(self.computer_board.get_length_ship(-1), 1)
        self.assertEqual(self.computer_board.get_length_ship(-2), 2)
        self.assertEqual(self.computer_board.get_length_ship(-3), 2)
        self.assertEqual(self.computer_board.get_length_ship(-4), 3)
        self.assertEqual(self.computer_board.get_length_ship(-5), 4)

    def test_get_point_where_to_shoot(self):
        chosen_point = self.computer_board.get_point_where_to_shoot(self.board)

        with self.assertRaises(BoardException):
            self.board.shoot_at(chosen_point)
        self.assertIn(self.board.get(chosen_point), [1, 2])

    def test_str(self):
        self.assertEqual(str(self.computer_board), str(self.computer_board))
