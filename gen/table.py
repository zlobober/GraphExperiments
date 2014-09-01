from sys import argv
from json import dumps
a, b = map(int, argv[1:])
nodes = [[i % b, i // b] for i in range(a * b)]
edges = [[i, i + b] for i in range(a * b - b)] + [[i, i + 1] for i in range(a * b) if i % b != b - 1]
D = {'nodes' : nodes, 'edges' : edges}
print(dumps(D))
