import random
from random import seed
from random import random
class Star:
    def __init__(self, locX, locY, mass, planets):
        self.locX = locX
        self.locY = locY
        self.mass = mass
        self.planets = []
        #Defines a Star

    def setX(self, locX):
        self.locX = locX

    def setY(self, locY):
        self.locY = locY
