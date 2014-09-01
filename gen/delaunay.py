import cgitb
import sys
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
    bombs = int(form["nodes"].value)

if not "edges" in form:
    error += "Expected edges GET parameter\n";
else:
    edges = int(form["nodes"].value)

if not "maxc" in form:
    error += "Expected maxc GET parameter\n";
else:
    maxc = int(form["nodes"].value)

if not "seed" in form:
    seed = int(time())
else:
    seed = int(form["seed"].value)

bashCommand = "/var/www/akhmedov.org/bomboleo/gen/delaunay/gen.sh %d %d %d %d %d" % (nodes, bombs, edges, maxc, seed)
import subprocess
process = subprocess.Popen(bashCommand.split(), stdout=subprocess.PIPE)
output = process.communicate()[0]
print(output)
