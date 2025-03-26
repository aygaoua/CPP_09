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

size_t	jacobsthalGenerator(size_t n)
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
void	swap_pairs(deque_int_it first, int pair_size)
{
	deque_int_it	start = stepsIt(first, -pair_size + 1);
	deque_int_it	end = stepsIt(start, pair_size);
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

	for (vector_int_it it = start; it != end; std::advance(it, 2 * pair_size))
	{
		vector_int_it	first = stepsIt(it, pair_size - 1);
		vector_int_it	second = stepsIt(it, pair_size * 2 - 1);
		if (compare(second, first))
			swap_pairs(first, pair_size);
	}

	mergeinsertionsortV(vec_container, pair_size * 2);

	std::vector< vector_int_it>	main;
	std::vector< vector_int_it>	pend;
	main.insert(main.end(), stepsIt(vec_container.begin(), pair_size - 1));
	main.insert(main.end(), stepsIt(vec_container.begin(), (pair_size * 2) - 1));
	for (int i = 4; i <= pairs_num; i += 2)
	{
		pend.insert(pend.end(), stepsIt(vec_container.begin(), (pair_size * (i - 1)) - 1));
		main.insert(main.end(), stepsIt(vec_container.begin(), (pair_size * i) - 1));
	}
	if (stragller)
		pend.insert(pend.end(), stepsIt(vec_container.begin(), pair_size * pairs_num - 1));
	size_t	prev_j_s = jacobsthalGenerator(2);
	int		inserted_nbs = 0;
	for (int k = 3; 0 == 0; k++)
	{
		size_t	curr_j_s = jacobsthalGenerator(k);
		size_t	diff_j_s = curr_j_s - prev_j_s;
		int		offset = 0;
		if (diff_j_s > pend.size())
			break ;
		size_t	nb_pairs_isrt = diff_j_s;
		std::vector< vector_int_it>::iterator	b_i_pend = pend.begin() + diff_j_s - 1;
		size_t	a_i_ndx = curr_j_s + inserted_nbs;
		while (nb_pairs_isrt--)
		{
			std::vector< vector_int_it>::iterator a_i_main = main.begin() + a_i_ndx - offset;
			std::vector< vector_int_it>::iterator ndx = std::lower_bound(main.begin(), \
																			a_i_main, \
																			*b_i_pend, \
																			compare<vector_int_it>);
			std::vector< vector_int_it>::iterator inserted = main.insert(ndx, *b_i_pend);
			b_i_pend = pend.erase(b_i_pend);
			if (b_i_pend != pend.begin())
				b_i_pend--;
			if ((inserted - main.begin()) == static_cast<long>(a_i_ndx))
				offset++;
		}
		prev_j_s = curr_j_s;
		inserted_nbs += diff_j_s;
		offset = 0;
	}

	for (size_t i = 0; i < pend.size(); i++)
	{
		std::vector< vector_int_it>::iterator	curr_p = pend.begin() + i;
		std::vector< vector_int_it>::iterator	curr_a_i = stepsIt(main.begin(), \
																		main.size() - pend.size() + i + stragller);
		std::vector< vector_int_it>::iterator	ndx = std::lower_bound(main.begin(), \
																		curr_a_i, \
																		*curr_p, \
																		compare<vector_int_it>);
		main.insert(ndx, *curr_p);
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
}


void	mergeinsertionsortD(deque_int &dq_container, int pair_size)
{
	int	pairs_num = dq_container.size() / pair_size;
	if (pairs_num < 2)
		return ;

	bool	stragller = (pairs_num % 2);

	deque_int_it start = dq_container.begin();
	deque_int_it end = stepsIt(dq_container.begin(), \
										pairs_num * pair_size - (stragller * pair_size));

	for (deque_int_it it = start; it != end; std::advance(it, 2 * pair_size))
	{
		deque_int_it	first = stepsIt(it, pair_size - 1);
		deque_int_it	second = stepsIt(it, pair_size * 2 - 1);
		if (compare(second, first))
			swap_pairs(first, pair_size);
	}

	mergeinsertionsortD(dq_container, pair_size * 2);

	std::deque< deque_int_it>	main;
	std::deque< deque_int_it>	pend;
	main.insert(main.end(), stepsIt(dq_container.begin(), pair_size - 1));
	main.insert(main.end(), stepsIt(dq_container.begin(), (pair_size * 2) - 1));
	for (int i = 4; i <= pairs_num; i += 2)
	{
		pend.insert(pend.end(), stepsIt(dq_container.begin(), (pair_size * (i - 1)) - 1));
		main.insert(main.end(), stepsIt(dq_container.begin(), (pair_size * i) - 1));
	}
	if (stragller)
		pend.insert(pend.end(), stepsIt(dq_container.begin(), pair_size * pairs_num - 1));
	size_t	prev_j_s = jacobsthalGenerator(2);
	int		inserted_nbs = 0;
	for (int k = 3; 0 == 0; k++)
	{
		size_t	curr_j_s = jacobsthalGenerator(k);
		size_t	diff_j_s = curr_j_s - prev_j_s;
		int		offset = 0;
		if (diff_j_s > (pend.size()))
			break ;
		size_t	nb_pairs_isrt = diff_j_s;
		std::deque< deque_int_it>::iterator	b_i_pend = pend.begin() + diff_j_s - 1;
		size_t	a_i_ndx = curr_j_s + inserted_nbs;
		while (nb_pairs_isrt--)
		{
			std::deque< deque_int_it>::iterator a_i_main = main.begin() + a_i_ndx - offset;
			std::deque< deque_int_it>::iterator ndx = std::lower_bound(main.begin(), \
																			a_i_main, \
																			*b_i_pend, \
																			compare<deque_int_it>);
			std::deque< deque_int_it>::iterator inserted = main.insert(ndx, *b_i_pend);
			b_i_pend = pend.erase(b_i_pend);
			if (b_i_pend != pend.begin())
				b_i_pend--;
			if ((inserted - main.begin()) == static_cast<long>(a_i_ndx))
				offset++;
		}
		prev_j_s = curr_j_s;
		inserted_nbs += diff_j_s;
		offset = 0;
	}

	for (size_t i = 0; i < pend.size(); i++)
	{
		std::deque< deque_int_it>::iterator	curr_p = pend.begin() + i;
		std::deque< deque_int_it>::iterator	curr_a_i = stepsIt(main.begin(), \
																		main.size() - pend.size() + i + stragller);
		std::deque< deque_int_it>::iterator	ndx = std::lower_bound(main.begin(), \
																		curr_a_i, \
																		*curr_p, \
																		compare<deque_int_it>);
		main.insert(ndx, *curr_p);
	}

	deque_int	copy;
	for (std::deque< deque_int_it>::iterator it = main.begin(); it != main.end(); it++)
	{
		for (int i = 0; i < pair_size; i++)
		{
			deque_int_it	unitStart = *it;
			std::advance(unitStart, -pair_size + i + 1);
			copy.insert(copy.end(), *unitStart);
		}
	}

	deque_int_it containerIt = dq_container.begin();
	deque_int_it copyIt = copy.begin();
	while (copyIt != copy.end())
	{
		*containerIt = *copyIt;
		containerIt++;
		copyIt++;
	}
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
	std::cout << "Before:" << std::endl;
    std::for_each(dq_container.begin(), dq_container.end(), printo);
    std::cout << std::endl;

	clock_t start;
	clock_t end;

	start = clock();
    mergeinsertionsortV(vec_container, 1);
	end = clock();
	double time_v = static_cast<double>((end - start) * 1000000.0) / CLOCKS_PER_SEC;
    mergeinsertionsortD(dq_container, 1);

    std::cout << "After: " << std::fixed << time_v << " us" << std::endl;
    std::for_each(vec_container.begin(), vec_container.end(), printo);
    std::cout << std::endl;
	std::cout << "After:" << std::endl;
    std::for_each(dq_container.begin(), dq_container.end(), printo);
    std::cout << std::endl;
}

