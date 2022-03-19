import unittest

from Battleship.Domains.Point import Point


class TestPoint(unittest.TestCase):
    def setUp(self):
        self.point1 = Point(2, 2)
        self.point2 = Point(3, 3)

    def test_properties(self):
        self.assertEqual(self.point1.x, 2)
        self.assertEqual(self.point1.y, 2)

        self.point1.x = 4
        self.point1.y = 4

        self.assertEqual(self.point1.x, 4)
        self.assertEqual(self.point1.y, 4)

    def test_eq(self):
        self.assertEqual(Point(2,2), Point(2, 2))

    def test_add(self):
        self.assertEqual(Point(2, 2) + Point(1, 1), Point(3, 3))

    def test_distance(self):
        self.assertEqual(Point.distance(Point(2, 2), Point(2, 4)), 2)








