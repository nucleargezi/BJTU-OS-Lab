cd "$(dirname "$0")" || exit 1
g++ -std=c++20 test1.cpp -o test1
# ./test1 ../../lab_data/ANNA_KARENINA.txt you out
./test1 ../../lab_data/big.txt the big_out
# ./test1 ../../lab_data/tt.txt yOU out