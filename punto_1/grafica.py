#!/usr/bin/env python2
# -*- coding: utf-8 -*-
import numpy as np
import matplotlib.pyplot as plt
import matplotlib.animation as animation
data =np.loadtxt('initial_conds.dat', delimiter=' ', dtype=float)

plt.imshow(data)
plt.gcf()
plt.savefig('init.png')

fig = plt.figure()
string_history = np.loadtxt('Pcosa.dat', delimiter = ' ', dtype=float)

''' 
history = []
for i in range(5):
    this_plot = plt.plot(np.linspace(0,100, len(string_history[0,:])),string_history[i,:], animated=True)
    this_plot.gca().set_ylim(0,1)
    history.append(this_plot)
gif = animation.ArtistAnimation(fig, history, interval=50, blit=True,
                                repeat_delay=10)
gif.save('string.mp4')
'''

plt.plot(string_history[6,:])
