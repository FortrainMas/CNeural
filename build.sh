mkdir ./build
mkdir ./build/math
gcc -c Network.c -o ./build/Network.o -I./math -I./dataframe
gcc -c ./math/Random.c -o ./build/math/Random.o -I./math
gcc -c ./math/Matrix.c -o ./build/math/Matrix.o -I./math
gcc -c ./dataframe/Dataframe.c -o ./build/dataframe/Dataframe.o -I./math -I./dataframe
gcc -c ./math/Sigmoid.c ./build/math/Matrix.o -o ./build/math/Sigmoid.o -I./math
gcc ./build/Network.o ./build/math/Random.o ./build/math/Sigmoid.o ./build/math/Matrix.o ./build/dataframe/Dataframe.o -o ./build/build
./build/build