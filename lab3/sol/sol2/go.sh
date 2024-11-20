cd "$(dirname "$0")" || exit 1
g++ -std=c++20 test2.cpp -o test2
# ./test2 ../../lab_data/ANNA_KARENINA.txt YOu out
./test2 ../../lab_data/big.txt the big_out