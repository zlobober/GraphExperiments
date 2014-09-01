if [ ! -f ./gen_rand ]; then
    g++ gen_rand.cpp -o gen_rand -O2
fi
if [ ! -f ./delaunay ]; then
    g++ delaunay.cpp -o delaunay -O2
fi
if [ ! -f ./del ]; then
    g++ del.cpp -o del -O2
fi

if (( $# < 5 )); then
    echo "./gen.sh <number of nodes> <number of bombs> <number of edges> <maximal coordinates> <seed>"
    exit 1
fi

timeout 5.0 ./gen_rand $1 $4 $5 > del_nodes.txt
tail -n $1 del_nodes.txt > del2_nodes.txt
timeout 5.0 ./delaunay del2 > /dev/null
timeout 5.0 ./del $3 $2 del_nodes.txt del2_elements.txt $5
