import unittest

from Battleship.Domains.Options import Options, OptionsException


class TestOptionsClass(unittest.TestCase):
    def setUp(self):
        self.options = Options()

    def test_properties(self):
        self.assertEqual(self.options.easy_value_of_moves, 10)
        self.assertEqual(self.options.normal_value_of_moves, 7)
        self.assertEqual(self.options.hard_value_of_moves, 3)
        self.assertEqual(self.options.max_computer_moves_before_sure_hit, 10)
        self.options.max_computer_moves_before_sure_hit = 5
        self.assertEqual(self.options.max_computer_moves_before_sure_hit, 5)
        self.assertEqual(self.options.difficulty, "easy")
        self.options.difficulty = "hard"
        self.assertEqual(self.options.difficulty, "hard")

    def test_set_difficulty(self):
        with self.assertRaises(OptionsException):
            self.options.set_difficulty("asd")
        self.options.set_difficulty("hard")
        self.assertEqual(self.options.max_computer_moves_before_sure_hit, 3)
        self.assertEqual(self.options.difficulty, "hard")

        self.options.set_difficulty("easy")
        self.assertEqual(self.options.max_computer_moves_before_sure_hit, 10)
        self.assertEqual(self.options.difficulty, "easy")

        self.options.set_difficulty("normal")
        self.assertEqual(self.options.max_computer_moves_before_sure_hit, 7)
        self.assertEqual(self.options.difficulty, "normal")