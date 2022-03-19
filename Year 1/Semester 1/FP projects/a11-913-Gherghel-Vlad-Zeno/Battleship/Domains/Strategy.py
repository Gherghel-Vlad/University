import random

from Battleship.Domains.Point import Point


class Strategy:
    def __init__(self, options):
        self._options = options

        # shows the current number of moves that were made from the last successful hit
        self.current_number_of_moves_without_hit = self._options.max_computer_moves_before_sure_hit
        self.successful_hits_list = []  # list representing the successful hits that needs to have their surroundings checked

        self._on_which_axis_the_ship_is = None  # 1 for x and 2 for y

    def free_enemy_cells(self, enemy_board):
        """
        Creates a list with all the points that haven't been shot at before
        :param enemy_board: The enemy's (player's) board instance
        :return: A list of point instances
        """
        points_list = []

        for i in range(0, enemy_board.number_of_rows):
            for j in range(0, enemy_board.number_of_columns):
                if enemy_board.get(Point(i, j)) not in [1, 2]:  # if it s a free unhit cell
                    points_list.append(Point(i, j))

        return points_list

    def get_point_where_to_shoot_randomly(self, enemy_board):
        """
        Searches and returns a random cell where to shoot
        :param enemy_board: The enemy's (player's) board instance
        :return: A point instance indicating where to shoot
        """

        not_hit_points_list = self.free_enemy_cells(enemy_board)

        chosen_point = random.choice(not_hit_points_list)

        if enemy_board.get(chosen_point) in [-1, -2, -3, -4, -5]:  # restarting the counting for when to make a sure hit
            self.current_number_of_moves_without_hit = self._options.max_computer_moves_before_sure_hit
            self.successful_hits_list.append(chosen_point)

        return chosen_point

    def difficulty_case(self, enemy_board):
        """
        Makes the choice of where the computer shoots next on the player's board
        :param enemy_board: The enemy's (player's) board instance
        :return: A point instance indicating where the computer will shoot
        """
        points_list = [Point(1, 0), Point(-1, 0), Point(0, -1), Point(0, 1)]
        free_enemy_cells = self.free_enemy_cells(enemy_board)

        if self.current_number_of_moves_without_hit == 0:
            # case in which the computer makes a sure hit
            # restarting the iteration
            self.current_number_of_moves_without_hit = self._options.max_computer_moves_before_sure_hit
            chosen_point = random.choice(enemy_board.ships_coordinates)
            self.successful_hits_list.append(chosen_point)
            return chosen_point
        elif len(self.successful_hits_list) != 0:
            # case in which the computer doesnt need to make a sure hit but has points to check
            while len(self.successful_hits_list) != 0:
                point = self.successful_hits_list[0]
                random.shuffle(points_list)
                for index in range(0, 4):
                    # if it found on which horizontal or vertical position the ship is,
                    # it s only going in those directions
                    if self._on_which_axis_the_ship_is is not None:
                        # means that the computer knows on which part to shoot
                        if self._on_which_axis_the_ship_is == 1:  # it s going only vertically to check
                            points_list = [Point(0, 1), Point(0, -1)]
                        else:  # it s going horizontally
                            points_list = [Point(1, 0), Point(-1, 0)]

                        x_point = point.x + points_list[index % 2].x
                        y_point = point.y + points_list[index % 2].y
                    else:  # this means that there s only one cell found of a ship and none other of the ship was found
                        x_point = point.x + points_list[index].x
                        y_point = point.y + points_list[index].y

                    # checking if i am not outside of bounds
                    if enemy_board.isnt_in_board(Point(x_point, y_point)):
                        continue
                    if Point(x_point, y_point) in free_enemy_cells:
                        value = enemy_board.get(Point(x_point, y_point))

                        if value in [-1, -2, -3, -4, -5]:  # this checks if it's gonna hit a new part of a ship
                            self.successful_hits_list.append(Point(x_point, y_point))
                            if self.successful_hits_list[0].x == self.successful_hits_list[1].x:
                                self._on_which_axis_the_ship_is = 1
                            else:
                                self._on_which_axis_the_ship_is = 2

                        return Point(x_point, y_point)
                # it will reach here if the point has no positions to check anymore
                del self.successful_hits_list[0]

        # case in which there are no hits prior that are still unchecked and there s no need to make a sure hit
        self.current_number_of_moves_without_hit -= 1
        self._on_which_axis_the_ship_is = None
        return self.get_point_where_to_shoot_randomly(enemy_board)
