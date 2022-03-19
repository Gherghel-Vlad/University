import unittest

from Battleship.Domains.Board import Board, BoardException
from Battleship.Domains.BoardComputer import BoardComputer
from Battleship.Domains.Options import Options
from Battleship.Domains.Point import Point
from Battleship.Domains.Strategy import Strategy
from Battleship.Service.Game import Game, GameException


class TestGameClass(unittest.TestCase):
    def setUp(self):
        self.board = Board(10, 10)

        options = Options()

        strategy = Strategy(options)

        self.computer_board = BoardComputer(10, 10, strategy)

        self.game = Game(self.board, self.computer_board)

    def test_convert_coordinates_to_point(self):
        with self.assertRaises(GameException):
            self.game.convert_coordinates_to_point("asd")
        with self.assertRaises(GameException):
            self.game.convert_coordinates_to_point("A")
        with self.assertRaises(GameException):
            self.game.convert_coordinates_to_point("")

        self.assertEqual(Point(0, 0), self.game.convert_coordinates_to_point("A1"))

    def test_set_player_ship(self):
        self.game.set_player_ship("a1", "b1", -1)
        self.assertEqual(self.board.get(Point(0, 0)), -1)
        self.assertEqual(self.board.get(Point(1, 0)), -1)

    def test_player_shoot(self):
        self.computer_board.set_ship(Point(0, 0), Point(1, 0), -1)
        with self.assertRaises(BoardException):
            self.game.player_shoot("A1")

        self.assertEqual(self.computer_board.get(Point(0, 0)), 2)

    def test_computer_shoot(self):
        self.game.set_player_ship("a1", "b1", -1)
        with self.assertRaises(BoardException):
            self.game.computer_shoot()

    def test_get_computer_board_string(self):
        self.assertEqual(str(self.computer_board), self.game.get_computer_board_string())

    def test_get_player_board_string(self):
        self.assertEqual(str(self.board), self.game.get_player_board_string())












