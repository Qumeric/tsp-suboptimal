import networkx as nx
import numpy as np
import matplotlib.pyplot as plt
from subprocess import call
n = input("Enter the number of points: ")
call("make clean && make", shell=True)
call("./bin/salesman " + str(n), shell=True) # CARE no sanitization!

MAX_CORD = 1000 * 1.02

graph_desc = open("graph.txt").readlines()
i = 0
pos = []
while(graph_desc[i][0] != ';'):
    point = graph_desc[i].split()
    pos.append(np.array([float(point[0]), float(point[1])]))
    i += 1

i += 1

G = nx.Graph()
while(graph_desc[i][0] != ';'):
    edge = graph_desc[i].split()
    G.add_edge(int(edge[0]), int(edge[1]))
    i += 1

nx.draw_networkx_nodes(G, pos, node_size = 1000/(G.size() ** 0.5), cmap=plt.get_cmap('jet'))
nx.draw_networkx_edges(G, pos)
plt.xlim(0, MAX_CORD)
plt.ylim(0, MAX_CORD)
plt.tight_layout()
plt.show()
