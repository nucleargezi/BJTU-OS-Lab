# g++ -std=c++20 virtual_memory_manager.cpp -o tt
# g++ -std=c++20 virtual_memory_manager2.cpp -o tt
# ./tt addresses.txt BACKING_STORE.bin my_out
# ./tt addresses.txt BACKING_STORE.bin my_out fifo
./tt addresses.txt BACKING_STORE.bin my_out lru

# if ! diff -b -B my_out correct.txt > /dev/null; then
#     echo "wrong answer"
#     break
# else 
#     echo "accept"
# fi