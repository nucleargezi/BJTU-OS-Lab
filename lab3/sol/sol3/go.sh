cd "$(dirname "$0")" || exit 1
g++ -std=c++20 test3.cpp -o test3
# ./test3 ../../lab_data/ANNA_KARENINA.txt you out
./test3 ../../lab_data/big.txt the big_out