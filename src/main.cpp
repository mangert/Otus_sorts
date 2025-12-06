#include <iostream>
#include "generator.cpp"
#include "Sorter.h"

int main() {
	
	uint64_t rnd_arr[10];
	data_generator::fill_random<uint64_t>(rnd_arr, 10, 20);
	data_generator::print_array<uint64_t>(rnd_arr, 10);

	std::cout << std::endl;	
	Sorter<uint64_t>::shell_sort_sedgewick(rnd_arr, 2500000000);

	data_generator::print_array<uint64_t>(rnd_arr, 10);


	return 0; 
}