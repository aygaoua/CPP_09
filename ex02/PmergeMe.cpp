#include "PmergeMe.hpp"

bool is_number(std::string str) {
	if (str[0] == '+' || str == "-0")
		str.erase(0, 1);
	if (!std::isdigit(str[0]))
		return false;
	for (unsigned long i = 0; i < str.length(); i++) {
		if (!std::isdigit(str[i]))
			return false;
	}
	return true;
}

void printo(int n) {
    std::cout << n << " ";
}

long	jacobsthalGenerator(long n)
{
	if (n == 0)
		return (0);
	if (n == 1)
		return (1);
	return((pow(2, n) - pow(-1, n)) / 3);
}


void	swap_pairs(vector_int_it first, int pair_size)
{
	vector_int_it	start = stepsIt(first, -pair_size + 1);
	vector_int_it	end = stepsIt(start, pair_size);
	while (start != end)
	{
		std::iter_swap(start, stepsIt(start, pair_size));
		start++;
	}
}

void	mergeinsertionsortV(vector_int &vec_container, int pair_size)
{
	int	pairs_num = vec_container.size() / pair_size;
	if (pairs_num < 2)
		return ;
	
	bool	stragller = (pairs_num % 2);

	vector_int_it start = vec_container.begin();
	vector_int_it end = stepsIt(vec_container.begin(), \
										pairs_num * pair_size - (stragller * pair_size));

	std::cout << "end: " << std::endl;
	for (vector_int_it it = start; it != end; std::advance(it, 2 * pair_size))
	{
		vector_int_it	first = stepsIt(it, pair_size - 1);
		vector_int_it	second = stepsIt(it, pair_size * 2 - 1);
		std::cout << "`" << pair_size - 1 << "` compaired to `" << pair_size * 2 - 1 << "`\n";
		if (*first > *second)
			swap_pairs(first, pair_size);
	}
	std::cout << std::endl;

	mergeinsertionsortV(vec_container, pair_size * 2);

	std::vector< vector_int_it>	main;
	std::vector< vector_int_it>	pend;
	main.insert(main.end(), stepsIt(vec_container.begin(), pair_size - 1));
	main.insert(main.end(), stepsIt(vec_container.begin(), (pair_size * 2) - 1));
	// std::cout << "maino: " << *stepsIt(vec_container.begin(), pair_size - 1) << std::endl;
	// std::cout << "maino: " << *stepsIt(vec_container.begin(), (pair_size * 2) - 1) << std::endl;
	for (int i = 4; i <= pairs_num; i += 2)
	{
		// std::cout << "maino: " << *stepsIt(vec_container.begin(), pair_size * i - 1) << std::endl;
		// std::cout << "pendo: " << *stepsIt(vec_container.begin(), pair_size * (i - 1) - 1) << std::endl;
		pend.insert(pend.end(), stepsIt(vec_container.begin(), (pair_size * (i - 1)) - 1));
		main.insert(main.end(), stepsIt(vec_container.begin(), (pair_size * i) - 1));
	}
	if (stragller)
		pend.insert(pend.end(), stepsIt(vec_container.begin(), pair_size * pairs_num - 1));
	std::cout << "main: ";
	for(size_t i = 0; i != main.size(); ++i)
	{
		std::cout << *main[i] << " ";
	}
	std::cout << std::endl;
	std::cout << "pend: ";
	for(size_t i = 0; i != pend.size(); ++i)
	{
		std::cout << *pend[i] << " ";
	}
	std::cout << std::endl;
	std::cout << std::endl;
	long	prev_j_s = jacobsthalGenerator(2);
	int		inserted_nbs = 0;
	for (int k = 3; 0 == 0; k++)
	{
		long	curr_j_s = jacobsthalGenerator(k);
		long	diff_j_s = curr_j_s - prev_j_s;
		int		offset = 0;
		if (diff_j_s > static_cast<long>(pend.size()))
			break ;
		long	nb_pairs_isrt = diff_j_s;

		std::vector< vector_int_it>::iterator	pend_it = pend.begin() + diff_j_s - 1;
		long int	bound_ndx = curr_j_s + inserted_nbs;
		while (nb_pairs_isrt--)
		{
			std::vector< vector_int_it>::iterator bound_it = main.begin() + bound_ndx - offset;
			std::cout << "idx: " << nb_pairs_isrt + prev_j_s + 1 << " | " << static_cast<long>(pend.size()) << std::endl;
			std::vector< vector_int_it>::iterator idx = std::lower_bound(main.begin(), \
																			bound_it, \
																			*pend_it, \
																			compare<vector_int_it>);
			std::vector< vector_int_it>::iterator inserted = main.insert(idx, *pend_it);
			pend_it = pend.erase(pend_it);
			if (pend_it != pend.begin())
				pend_it--;
			offset += ((inserted - main.begin()) == bound_ndx);
		}
		prev_j_s = curr_j_s;
		inserted_nbs += diff_j_s;
		offset = 0;
	}

	for (size_t i = 0; i < pend.size(); i++)
	{
		std::vector< vector_int_it>::iterator	currPend = pend.begin() + i;
		std::vector< vector_int_it>::iterator	currBound = stepsIt(main.begin(), \
																		main.size() - pend.size() + i + stragller);
		std::vector< vector_int_it>::iterator	idx = std::lower_bound(main.begin(), \
																		currBound, \
																		*currPend, \
																		compare<vector_int_it>);
		std::cout << "***********" << pair_size / 2 + 1 << " ||| " << **currPend << "\n";
		main.insert(idx, *currPend);
	}

	vector_int	copy;
	copy.reserve(vec_container.size());
	for (std::vector< vector_int_it>::iterator it = main.begin(); it != main.end(); it++)
	{
		for (int i = 0; i < pair_size; i++)
		{
			vector_int_it	unitStart = *it;
			std::advance(unitStart, -pair_size + i + 1);
			copy.insert(copy.end(), *unitStart);
		}
	}

	vector_int_it containerIt = vec_container.begin();
	vector_int_it copyIt = copy.begin();
	while (copyIt != copy.end())
	{
		*containerIt = *copyIt;
		containerIt++;
		copyIt++;
	}
	std::cout << std::endl;
	std::cout << "my sec: ";
	std::for_each(vec_container.begin(), vec_container.end(), printo);
	std::cout << std::endl;
	std::cout << std::endl;
}


void merge_insert_global(int ac, char **av) {
    vector_int vec_container;
    deque_int dq_container;
    for (int i = 1; i < ac; i++) {
        std::string str(av[i]);
        if (is_number(str)) {
                char *end_ptr;
                double value = strtod(str.c_str(), &end_ptr);
                if (value > std::numeric_limits<int>::max() || value < std::numeric_limits<int>::min())
                {
                    std::cerr << "Error: not an positive integer" << std::endl;
                    exit(1);
                }
                dq_container.push_back(value);
                vec_container.push_back(value);
        } else {
            std::cerr << "Invalid value: `" << str << "`" <<  std::endl;
            exit (1);
        }

    }
    std::cout << "Before:" << std::endl;
    std::for_each(vec_container.begin(), vec_container.end(), printo);
    std::cout << std::endl;


    mergeinsertionsortV(vec_container, 1);


    std::cout << "After:" << std::endl;
    std::for_each(vec_container.begin(), vec_container.end(), printo);
    std::cout << std::endl;
}

