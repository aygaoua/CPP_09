#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <string>
#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>

typedef std::vector<int>	vector_int;
typedef std::vector<int>::iterator	vector_int_it;

bool    is_number(std::string str);
void    merge_insert(int ac, char **av);
void    printo(int n);
void	mergeinsertionsortV(vector_int &vec_container, int unitSize);

template<typename T>
T advanceIter(T it, int steps)
{
	std::advance(it, steps);
	return (it);
}

template <typename T>
bool	compare(T left, T right)
{
	return (*left < *right);
}

#endif