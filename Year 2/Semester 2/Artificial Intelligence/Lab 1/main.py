import pygame
from random import randint
import time
from tkinter import *
from tkinter import messagebox
from Controllers.Drone import Drone
from Models.DMap import DMap
from Models.Enviroment import Environment

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

def main():
    # we create the environment
    e = Environment()
    e.loadEnvironment("test2.map")
    # print(str(e))

    # we create the map
    m = DMap()

    # initialize the pygame module
    pygame.init()
    # load and set the logo
    logo = pygame.image.load("logo32x32.png")
    pygame.display.set_icon(logo)
    pygame.display.set_caption("drone exploration")

    # we position the drone somewhere in the area
    x = randint(0, 19)
    y = randint(0, 19)
    #while e.checkCorrectPosition(x, y):
    #    x = randint(0, 19)
    #    y = randint(0, 19)

    # cream drona
    d = Drone(x, y)

    # create a surface on screen that has the size of 800 x 480
    screen = pygame.display.set_mode((800, 400))
    screen.fill(WHITE)
    screen.blit(e.image(), (0, 0))

    # define a variable to control the main loop
    running = True
    d.move(m)

    m.markDetectedWalls(e, d.x, d.y)
    screen.blit(m.image(d.x, d.y), (400, 0))
    pygame.display.flip()

    # main loop
    while running:
        # event handling, gets all event from the event queue
        for event in pygame.event.get():
            # only do something if the event is of type QUIT
            if event.type == pygame.QUIT:
                # change the value to False, to exit the main loop
                running = False
            # if event.type == KEYDOWN:
            # use this function instead of move

            # d.moveDSF(m)
            # time.sleep(0.1)
            # d.move(m)

        d.moveDSF(m)
        time.sleep(0.1)
        if d.x == None and d.y == None:
            break
        m.markDetectedWalls(e, d.x, d.y)
        screen.blit(m.image(d.x, d.y), (400, 0))
        pygame.display.flip()

    Tk().wm_withdraw()
    messagebox.showinfo('Done', 'OK')
    pygame.quit()


# run the main function only if this module is executed as the main script
# (if you import this as a module then nothing is executed)
if __name__ == "__main__":
    # call the main function
    main()