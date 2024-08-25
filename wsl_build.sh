mkdir ./build_wsl
mkdir ./build_wsl/math
mkdir ./build_wsl/dataframe
gcc -c Network.c -o ./build_wsl/Network.so -I./math -I./dataframe -lm
gcc -c ./math/Random.c -o ./build_wsl/math/Random.so -I./math -lm
gcc -c ./math/Matrix.c -o ./build_wsl/math/Matrix.so -I./math -lm
gcc -c ./dataframe/Dataframe.c -o ./build_wsl/dataframe/Dataframe.so -I./math -I./dataframe -lm
gcc -c ./math/Sigmoid.c ./build_wsl/math/Matrix.so -o ./build_wsl/math/Sigmoid.so -I./math -lm
gcc ./build_wsl/Network.so ./build_wsl/math/Random.so ./build_wsl/math/Sigmoid.so ./build_wsl/math/Matrix.so ./build_wsl/dataframe/Dataframe.so -o ./build_wsl/build_wsl.out -lm
# ./build_wsl/build_wsl