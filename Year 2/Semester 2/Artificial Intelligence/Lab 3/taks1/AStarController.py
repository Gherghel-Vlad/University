import pickle,pygame,time
from pygame.locals import *
from random import random, randint
import numpy as np

from Cell import Cell

v = [[-1, 0], [1, 0], [0, 1], [0, -1]]

class AStar:

    def __init__(self, mapM, droneD, initialX, initialY, finalX, finalY):
        self.mapM = mapM
        self.droneD = droneD
        self.initialX = initialX
        self.initialY = initialY
        self.finalX = finalX
        self.finalY = finalY

    def astaralg(self):
        start_node = Cell(None, (self.initialX, self.initialY))
        start_node.g = start_node.h = start_node.f = 0

        end_node = Cell(None, (self.finalX, self.finalY))
        end_node.g = end_node.h = end_node.f = 0

        open_list = []
        closed_list = []

        open_list.append(start_node)

        while len(open_list) > 0:
            current_node = open_list[0]
            current_index = 0

            for (index, item) in open_list:
                if item.f < current_node.f:
                    current_node = item
                    current_index = index

            open_list.pop(current_index)
            closed_list.append(current_node)

            if current_node == end_node:
                path = []
                current = current_node
                while current is not None:
                    path.append(current.position)
                    current = current.parent
                return path[::-1]

            children = []

            for new_position in v:
                node_position = (current_node.position[0] + new_position[0], current_node.position[1] + new_position[1])

                if node_position[0] > (len(self.mapM) - 1) or node_position[0] < 0 or node_position[1] > (
                        len(self.mapM[len(self.mapM) - 1]) - 1) or node_position[1] < 0:
                    continue

                if self.mapM.isAvailablePosition(node_position[0], node_position[1]):
                    continue

                new_node = Cell(current_node, node_position)

                children.append(new_node)

            for child in children:

                for closed_child in closed_list:
                    if child == closed_child:
                        continue

                child.g = current_node.g + 1
                child.h = (abs(child.position[0] - end_node.position[0])) + (
                            abs(child.position[1] - end_node.position[1]))
                child.f = child.g + child.h

                for open_node in open_list:
                    if child == open_node and child.g > open_node.g:
                        continue

                open_list.append(child)
