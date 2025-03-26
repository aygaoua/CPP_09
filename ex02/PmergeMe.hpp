#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <string>
#include <iostream>
#include <deque>
#include <vector>
#include <algorithm>
#include <ctime>

typedef std::vector<int>			vector_int;
typedef std::vector<int>::iterator	vector_int_it;
typedef std::deque<int>				deque_int;
typedef std::deque<int>::iterator	deque_int_it;

bool    is_number(std::string str);
void    merge_insert_global(int ac, char **av);
void    printo(int n);
void	mergeinsertionsortV(vector_int &vec_container, int pair_size);

template<typename T>
T stepsIt(T it, int steps)
{
	std::advance(it, steps);
	return (it);
}

template <typename T>
bool	compare(T left, T right)
{
	static int g;

	g++;
	return (*left < *right);
}

#endif