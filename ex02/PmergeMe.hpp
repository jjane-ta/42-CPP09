#pragma once

#include <iostream>

class PmergeMe{
	public:
		virtual ~PmergeMe();

		static void sort(int * input);

	private:
		PmergeMe(void);
		PmergeMe(PmergeMe const & cv);
		PmergeMe operator+(PmergeMe const & cv);



};