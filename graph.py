import subprocess as sb
from time import time
import matplotlib.pyplot as plt
import sys
import numpy as np

legend = []
lower_y_lim = 1e9
higher_y_lim = -1e9
for index in range(1, len(sys.argv)):
    file_name = sys.argv[index]
    f = open(file_name, "r")
    try:
        parser_type = f.readline()
    except StopIteration:
        parser_type = "Undefined parser"
    legend.append(parser_type)
    
    x_axis = []
    y_axis = []
    for line in f:
        try:
            w, h = [float(x) for x in next(f).split()] 
        except StopIteration:
            break
        x_axis.append(w)
        y_axis.append(h)
    plt.xlabel("Длина выражения", size = 22)
    plt.ylabel("Время", size = 22)
    p = np.polyfit(x_axis, y_axis, 1)
    for i in range(len(x_axis)):
       y_axis[i] = p[0] * x_axis[i] + p[1]
    plt.plot(x_axis, y_axis)
    lower_y_lim = min(lower_y_lim, y_axis[0])
    higher_y_lim = max(higher_y_lim, y_axis[len(y_axis) - 1])
plt.xlim(x_axis[0], x_axis[len(x_axis) - 1])
plt.ylim(lower_y_lim / 10, higher_y_lim * 10)
plt.rcParams.update({'font.size': 18})
plt.yscale("log")
plt.grid(True) 
plt.legend(legend, loc="lower right")
plt.show()
