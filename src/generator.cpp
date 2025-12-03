#pragma once
#include <iostream>
#include <concepts>
#include <random>

namespace data_generator {	
	
	void fill_sequenced(uint64_t* const array, size_t n) {
		
		for (size_t i = 0; i != n; ++i) {
			array[i] = i;
		};		
	};

	void fill_random(uint64_t* const array, size_t n, uint64_t max_val) {
		std::random_device rd;
		std::mt19937_64 gen(rd());  // 64-битная версия
		std::uniform_int_distribution<uint64_t> distrib;
		
		for (size_t i = 0; i != n; ++i) {
			array[i] = distrib(gen) % max_val;
		};		
	};

	void print_array(uint64_t* const array, size_t n) {
		for (size_t i = 0; i != n; ++i)
			std::cout << array[i] << " ";
		std::cout << "\n";
	};
}