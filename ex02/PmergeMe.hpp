#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <string>
#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <sys/time.h>

typedef std::vector<int>			vector_int;
typedef std::vector<int>::iterator	vector_int_it;
typedef std::deque<int>				deque_int;
typedef std::deque<int>::iterator	deque_int_it;

bool		is_number			(std::string str);
void		printo				(int n);
size_t		j_s_generator		(size_t n);
void		swap_pairs			(vector_int_it first, int pair_size);
void		swap_pairs			(deque_int_it first, int pair_size);
void		mergeinsertionsortV	(vector_int &vec_container, int pair_size);
void		mergeinsertionsortD	(deque_int &dq_container, int pair_size);
void		merge_insert_global	(int ac, char **av);

template<typename T>
T			steps_it(T it, int steps) {
	std::advance(it, steps);
	return (it);
}

template <typename T>
bool		compare(T left, T right) {

	return (*left < *right);
}

#endif