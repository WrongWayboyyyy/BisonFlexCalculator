import subprocess as sb
from time import time
import matplotlib.pyplot as plt
import sys

legend = []
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
    plt.xlabel("Length")
    plt.ylabel("Time")
    plt.plot(x_axis, y_axis)
    
plt.yscale("log")
plt.grid(True) 
plt.legend(legend, loc="lower right")
plt.show()


