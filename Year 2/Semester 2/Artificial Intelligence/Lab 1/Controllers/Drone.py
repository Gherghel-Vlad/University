
# import the pygame module, so you can use it
import pygame
from pygame.locals import *
from collections import deque

#Creating some colors
BLUE  = (0, 0, 255)
GRAYBLUE = (50,120,120)
RED   = (255, 0, 0)
GREEN = (0, 255, 0)
BLACK = (0, 0, 0)
WHITE = (255, 255, 255)

#define directions
UP = 0
DOWN = 2
LEFT = 1
RIGHT = 3

#define indexes variations
v = [[-1, 0], [1, 0], [0, 1], [0, -1]]

v_more = [[-1, 0], [1, 0], [0, 1], [0, -1], [1, 1], [-1, -1], [1, -1], [-1, 1]]
v_check = [[[0, 0], [0,0]], [[0, 0], [0,0]], [[0, 0], [0,0]], [[0, 0], [0,0]], [[1, 0], [0,1]], [[-1, 0], [0,-1]], [[1, 0], [0,-1]], [[-1, 0], [0,1]]]
class Drone():
    stack = deque()

    visited = []

    path = deque()

    elems_to_remove = deque()

    def __init__(self, x, y):
        self.x = x
        self.y = y

        self.stack.append((self.x, self.y))

    def move(self, detectedMap):
        pressed_keys = pygame.key.get_pressed()
        if self.x > 0:
            if pressed_keys[K_UP] and detectedMap.surface[self.x - 1][self.y] == 0:
                self.x = self.x - 1
        if self.x < 19:
            if pressed_keys[K_DOWN] and detectedMap.surface[self.x + 1][self.y] == 0:
                self.x = self.x + 1

        if self.y > 0:
            if pressed_keys[K_LEFT] and detectedMap.surface[self.x][self.y - 1] == 0:
                self.y = self.y - 1
        if self.y < 19:
            if pressed_keys[K_RIGHT] and detectedMap.surface[self.x][self.y + 1] == 0:
                self.y = self.y + 1

    def moveDSF(self, detectedMap):
        from_next = 0
        if len(self.stack) != 0:
            self.visited.append((self.x, self.y))
            print(len(self.stack))
            print(self.stack)
            for i in range(0, 4):
                x1 = self.x + v[i][0]
                y1 = self.y + v[i][1]

                if 0 <= x1 <= 19 and y1 >= 0 and y1 <= 19 and detectedMap.surface[x1][y1] == 0 and (
                x1, y1) not in self.visited:
                    self.stack.append((x1, y1))

            xbef = self.x
            ybef = self.y

            (self.x, self.y) = self.stack.pop()

            if 1 < abs(xbef - self.x) or 1 < abs(ybef - self.y) or (abs(xbef - self.x) == abs(ybef - self.y) and abs(xbef - self.x) == 1):
                self.stack.append((self.x, self.y))
                (self.x, self.y) = self.path.pop()
            else:
                self.path.append((xbef, ybef))

            for (xt, yt) in self.stack:
                ok = 1
                for i in range(0, 8):
                    x1 = xt + v_more[i][0]
                    y1 = yt + v_more[i][1]

                    [xc1, yc1] = v_check[i][0]
                    [xc2, yc2] = v_check[i][1]

                    if 0 <= x1 <= 19 and y1 >= 0 and y1 <= 19 and detectedMap.surface[x1][y1] == -1:
                        #if detectedMap.surface[xt + xc1][yt + yc1] != 1 and detectedMap.surface[xt + xc2][yt + yc2] != 1 and xc1 != 0 and yc1 != 0:
                        ok = 0

                if ok == 1:
                    self.elems_to_remove.append((xt, yt))

            while len(self.elems_to_remove) != 0:
                (xt, yt) = self.elems_to_remove.pop()
                self.stack.remove((xt, yt))

        else:
            self.x = None
            self.y = None



