#include "PmergeMe.hpp"

#include <iostream>
#include <vector>
#include <list>




// void print(std::vector<int> v){
// 	std::vector<int>::iterator begin = v.begin();
// 	std::vector<int>::iterator end = v.end();

// 	std::cout << "[";
// 	while(begin != end){
// 		std::cout << " " << *begin;
// 		begin++;
// 	}
// 	std::cout << "] "<< v.size() << std::endl;

// }
void print(std::vector<int *> v){
	std::vector<int *>::iterator begin = v.begin();
	std::vector<int *>::iterator end = v.end();

	std::cout << "[";
	while(begin != end){
		std::cout << " " << *(*begin);
		begin++;
	}
	std::cout << "] "<< v.size() << std::endl;

}

void binary_insert(std::vector<int *> & input, std::vector<int *>::iterator begin,std::vector<int *>::iterator end, int *value){
	// (void)value;
	// (void)input;
	// std::cout << "aki"  <<std::endl;
	if (!value) return;

	if (end  - begin == 0) {input.insert(begin, value);return;}
	// print(input);
	// std::cout << **( begin +((end - 1 - begin) / 2))  << std::endl;
	
	std::vector<int *>::iterator middle = (begin +((end - 1 - begin) / 2));
	// std::cout << "size " << end  - begin << std::endl;
	// std::cout << "middle " << **middle << std::endl;
	// std::cout << "value " << *value << std::endl;


	if (**middle <= *value) begin = middle + 1;
	else end = middle;
	// std::cout << "aka" << std::endl;

	binary_insert(input,begin, end, value);


	// if (value) input.push_back(value);
}

void split(std::vector<int *> & larger, std::vector<std::pair<int *, int *> > & pending, std::vector<int *> & input){
	std::vector<int *>::iterator begin = input.begin();
	std::vector<int *>::iterator end = input.end();
	int *l;
	int *s;

	while(begin != end){
		if (**begin > **(begin + 1)){
			l =  *begin;
			s = (*(begin + 1));
		}
		else{
			l =  *(begin + 1);
			s = (*begin);
		}
		larger.insert(larger.end(), l);
		pending.insert(pending.end(), std::pair<int *, int *>(l,s));
		begin = begin + 2;
	}	
	// std::cout << "\n\n";

}

int **find_smaller(std::vector<std::pair<int *, int*> > &pending, int * larger_ptr){
	std::vector<std::pair<int *, int*> >::iterator begin = pending.begin();
	std::vector<std::pair<int *, int*> >::iterator end = pending.end();

	while(begin != end){
		// std::cout << "p = " << *begin->second << " l " << *larger_it << " " <<(begin->second == larger_it) << std::endl;
		if(begin->first == larger_ptr){
			return &begin->second;
		}
		begin++;
	}
	return NULL;
}

void print_info(std::vector<std::pair<int *, int *> > pending){
	std::vector<std::pair<int *, int* > >::iterator begin = pending.begin();
	std::vector<std::pair<int *, int *> >::iterator end = pending.end();
	
	while(begin != end){
		std::cout << "smaller " << *(begin->first) << " larger " << *begin->second << std::endl;
		begin++;
	}
}

std::vector<int *> insert(std::vector<int *> larger, std::vector<std::pair<int *, int * > > pending, int *odd){
	std::vector<int *>::iterator begin = larger.begin();
	std::vector<int *>::iterator end = larger.end();
	std::vector<int *> res(larger);

	int **smaller;
	smaller = find_smaller(pending, *begin);
	if (smaller)	binary_insert(res, res.begin(), res.end(), *smaller);
	begin++;
	while(begin != end){
		smaller = find_smaller(pending, *begin);
			if (smaller)	binary_insert(res, res.begin(), res.end(), *smaller);	
		begin++;
	}

	binary_insert(res,res.begin(), res.end(), odd);
	return res;
}

std::vector<int * > sort(std::vector<int *> input){
	std::vector<int *> larger;
	std::vector<std::pair<int *, int * > > pending;
	int *odd = NULL;

	if (input.size() == 1) return input;

	if (input.size() % 2 != 0){odd = input.back();	input.pop_back();}

	split(larger, pending, input);
	// print_info(pending);

	// print(larger);
	larger = sort(larger);

	return insert(larger, pending, odd);
}

int main(int argc, char **argv)
{
	(void) argc;
	(void) argv;

	// int * a[] = {new int(3),new int(4),new int(2),new int(1),new int(5),new int(9),new int(8),new int(7),new int(0),new int(6)};
	// int * a[] = {new int(3),new int(4),new int(2)	};
	// int * sorted[] = {new int(1),new int(2),new int(4),new int(5),new int(6)};
	int n = 1000;
	int value = n;
	std::vector<int *> input;

	for (int i = 0; i < n ; i++)
	{
		input.insert(input.begin(),new int(value));
		value--;

	}
	value = n;
	for (int i = 0; i < n ; i++)
	{
		input.insert(input.begin(),new int(value));
		value--;

	}
	std::cout << "start" << std::endl;
	

	// print(input);
	print(sort(input));

		// int * value = new int(0);
		// binary_insert(input,input.begin(), input.end(), value);
		// print(input);


	return 0;
}
