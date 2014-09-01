import cgitb
cgitb.enable()

print("Content-Type: application/json")
print()

import cgi
form = cgi.FieldStorage()
if not "nodes" in form:
    print("Expected nodes GET parameter")

