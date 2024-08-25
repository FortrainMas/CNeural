cd ..
sh ./build.sh
cd mnist
gcc -c ./mnist.c -o ./build/mnist.o -I../math -I../dataframe
gcc ./build/mnist.o  ../build/math/Matrix.o ../build/dataframe/Dataframe.o -o ./build/build
./build/build