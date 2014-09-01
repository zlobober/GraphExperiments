import cgitb
import sys
from json import dumps
from os import popen
from time import time
cgitb.enable()

print("Content-Type: application/json")
print()

import cgi
form = cgi.FieldStorage()

bad = False

result = dict()
error = ''

if not "nodes" in form:
    error += "Expected nodes GET parameter\n"
else:
    nodes = int(form["nodes"].value)

if not "bombs" in form:
    error += "Expected bombs GET parameter\n";
else:
    bombs = int(form["bombs"].value)

if not "edges" in form:
    error += "Expected edges GET parameter\n";
else:
    edges = int(form["edges"].value)

if not "maxc" in form:
    error += "Expected maxc GET parameter\n";
else:
    maxc = int(form["maxc"].value)

if not "seed" in form:
    seed = int(time())
else:
    seed = int(form["seed"].value)

if error != '':
    result["error"] = error
    print(dumps(result))
else:
    bashCommand = "/var/www/akhmedov.org/bomboleo/gen/delaunay/gen.sh %d %d %d %d %d" % (nodes, bombs, edges, maxc, seed)
    output = os.popen(bashCommand).read()
    print(output)
