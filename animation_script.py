import csv
import time

import numpy as np
import matplotlib.pyplot as plt
from matplotlib.animation import FuncAnimation


particle_history = []
particles = []

file = "build/results.csv"
# file = "results/n20_T0-2.csv"

with open(file, newline='') as csvfile:
    spamreader = csv.reader(csvfile, delimiter=',')
    for row in spamreader:
        particle = []
        for i, coord in enumerate(row):
            if (i%2 == 0 and i != 0):
                particle.append(float(coord))
                particles.append(particle)
                particle = []
            else:
                particle.append(float(coord))
        particle_history.append(particles)
        particles = []


def animate(i):
    particles = particle_history[i]
    ax.clear()

    ax.set_xlim([0,3])
    ax.set_ylim([0,3])

    for particle in particles:
        ax.plot(particle[0], particle[1], '.b')
    ax.grid()

fig, ax = plt.subplots()

ani = FuncAnimation(fig, animate, frames=len(particle_history), interval=1)
plt.show()