import unittest

from Battleship.Domains.Board import Board, BoardException
from Battleship.Domains.Options import Options
from Battleship.Domains.Point import Point
from Battleship.Domains.Strategy import Strategy


class TestStrategy(unittest.TestCase):
    def setUp(self):
        self.board = Board(10, 10)

        options = Options()
        self.strategy = Strategy(options)

    def set_ships(self):
        self.board.set_ship(Point(0, 0), Point(1, 0), -1)
        self.board.set_ship(Point(2, 1), Point(2, 3), -2)
        self.board.set_ship(Point(2, 9), Point(4, 9), -3)
        self.board.set_ship(Point(5, 5), Point(5, 8), -4)
        self.board.set_ship(Point(7, 2), Point(7, 6), -5)

    def test_free_enemy_cells(self):
        list = self.strategy.free_enemy_cells(self.board)

        self.assertEqual(len(list), 100)

    def test_get_point_where_to_shoot_randomly(self):
        list = self.strategy.free_enemy_cells(self.board)
        chosen_point = self.strategy.get_point_where_to_shoot_randomly(self.board)
        self.assertIn(chosen_point, list)

    def test_difficulty_case(self):
        self.set_ships()

        chosen_point = self.strategy.difficulty_case(self.board)
        with self.assertRaises(BoardException):
            self.board.shoot_at(chosen_point)
        self.assertIn(self.board.get(chosen_point), [1, 2])

        with self.assertRaises(BoardException):
            self.board.shoot_at(Point(0, 0))
        self.strategy.successful_hits_list = [Point(0, 0)]

        chosen_point = self.strategy.difficulty_case(self.board)
        with self.assertRaises(BoardException):
            self.board.shoot_at(chosen_point)
        self.assertIn(self.board.get(chosen_point), [1, 2])

        self.strategy._on_which_axis_the_ship_is = 1

        chosen_point = self.strategy.difficulty_case(self.board)
        with self.assertRaises(BoardException):
            self.board.shoot_at(chosen_point)
        self.assertIn(self.board.get(chosen_point), [1, 2])

        self.strategy._on_which_axis_the_ship_is = 2

        chosen_point = self.strategy.difficulty_case(self.board)
        with self.assertRaises(BoardException):
            self.board.shoot_at(chosen_point)
        self.assertIn(self.board.get(chosen_point), [1, 2])

        self.strategy.current_number_of_moves_without_hit = 0

        chosen_point = self.strategy.difficulty_case(self.board)
        with self.assertRaises(BoardException):
            self.board.shoot_at(chosen_point)
        self.assertIn(self.board.get(chosen_point), [1, 2])
