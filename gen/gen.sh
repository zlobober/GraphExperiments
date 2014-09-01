if [ ! -f ./gen_rand ]; then
    g++ gen_rand.cpp -o gen_rand -O2
fi
if [ ! -f ./triang ]; then
    g++ triang.cpp -o triang -O2
fi

if (( $# < 4 )); then
    echo "./gen.sh <number of nodes> <number of bombs> <number of edges> <maximal coordinates>"
    exit 1
fi

./gen_rand $1 $4 | ./triang $3 $2
