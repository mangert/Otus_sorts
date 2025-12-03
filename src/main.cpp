#include <iostream>
#include "generator.cpp"
#include "Sorter.h"

int main() {
	
	uint64_t rnd_arr[10];
	data_generator::fill_random(rnd_arr, 10, 20);
	data_generator::print_array(rnd_arr, 10);

	std::cout << std::endl;
	Sorter<uint64_t>::bubble_sort(rnd_arr, 10);

	data_generator::print_array(rnd_arr, 10);


	return 0; 
}