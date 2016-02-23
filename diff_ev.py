import numpy as np
from scipy import optimize
from math import sin, exp
from matplotlib.pyplot import *
from random import randrange
import subprocess

def f(x):
    seed = randrange(1000000)
    r = randrange(100, 1000)
    args = ""
    for i in x:
        args += " " + str(i)
    return float(subprocess.check_output("./salesman 50" + args, shell=True))
    

#init = np.array([1, 5, 3000, 0.05, 5])
print(optimize.differential_evolution(f, [(0.1, 10), (0.1, 20), (1000, 10000), (0.01, 0.99), (1.5, 10), (0.05, 0.4)], disp=True, recombination=0.75, popsize=10, maxiter=30))

