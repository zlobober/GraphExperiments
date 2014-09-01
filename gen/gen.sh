if [ ! -f ./gen_rand ]; then
    g++ gen_rand.cpp -o gen_rand -O2
fi
if [ ! -f ./triang ]; then
    g++ delaunay.cpp -o delaunay -O2
fi
if [ ! -f ./del ]; then
    g++ del.cpp -o del -O2
fi

if (( $# < 4 )); then
    echo "./gen.sh <number of nodes> <number of bombs> <number of edges> <maximal coordinates>"
    exit 1
fi

./gen_rand $1 $4 > del_nodes.txt
tac del_nodes.txt | head -n -1 | tac >del2_nodes.txt
./delaunay del2
./del $3 $2 del_nodes.txt del2_elements.txt
