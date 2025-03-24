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
	long	prev = 0, curr = 1;
	for (long i = 2; i <= n; i++)
	{
		long	next = curr + 2 * prev;
		prev = curr;
		curr = next;
	}
	return (curr);
}


void	swapUnits(vector_int_it firstUnit, int unitSize)
{
	vector_int_it	start = advanceIter(firstUnit, -unitSize + 1);
	vector_int_it	end = advanceIter(start, unitSize);
	while (start != end)
	{
		std::iter_swap(start, advanceIter(start, unitSize));
		start++;
	}
}

void	mergeinsertionsortV(vector_int &vec_container, int unitSize)
{
	int	numOfUnits = vec_container.size() / unitSize;
	if (numOfUnits < 2)
		return ;
	
	bool	hasStraggler = numOfUnits % 2 == 1;

	vector_int_it start = vec_container.begin();
	vector_int_it end = advanceIter(vec_container.begin(), numOfUnits * unitSize - (hasStraggler * unitSize));

	for (vector_int_it it = start; it != end; std::advance(it, 2 * unitSize))
	{
		vector_int_it	firstUnit = advanceIter(it, unitSize - 1);
		vector_int_it	secondUnit = advanceIter(it, unitSize * 2 - 1);
		std::cout << "`" << *firstUnit << "` compaired to `" << *secondUnit << "`\n";
		if (*firstUnit > *secondUnit)
			swapUnits(firstUnit, unitSize);
	}

	mergeinsertionsortV(vec_container, unitSize * 2);

	std::vector< vector_int_it>	main;
	std::vector< vector_int_it>	pend;
	main.insert(main.end(), advanceIter(vec_container.begin(), unitSize - 1));
	main.insert(main.end(), advanceIter(vec_container.begin(), (unitSize * 2) - 1));
	for (int i = 4; i <= numOfUnits; i += 2)
	{
		pend.insert(pend.end(), advanceIter(vec_container.begin(), unitSize * (i - 1) - 1));
		main.insert(main.end(), advanceIter(vec_container.begin(), unitSize * i - 1));
	}

	if (hasStraggler)
		pend.insert(pend.end(), advanceIter(vec_container.begin(), unitSize * numOfUnits - 1));

	long	prevJacobsthal = jacobsthalGenerator(2);
	int		insertedNums = 0;
	for (int k = 3; 0 == 0; k++)
	{
		long	currJacobsthal = jacobsthalGenerator(k);
		long	jacobsthalDiff = currJacobsthal - prevJacobsthal;
		int		offset = 0;
		if (jacobsthalDiff > static_cast<long>(pend.size()))
			break ;
		long	numOfUnitInsertions = jacobsthalDiff;

		std::vector< vector_int_it>::iterator	pendIt = pend.begin() + jacobsthalDiff - 1;
		long int	boundIndex = currJacobsthal + insertedNums;
		while (numOfUnitInsertions--)
		{
			std::vector< vector_int_it>::iterator boundIt = main.begin() + boundIndex - offset;
			std::vector< vector_int_it>::iterator idx = std::lower_bound(main.begin(), boundIt, *pendIt, compare<vector_int_it>);
			std::vector< vector_int_it>::iterator inserted = main.insert(idx, *pendIt);
			pendIt = pend.erase(pendIt);
			if (pendIt != pend.begin())
				pendIt--;
			offset += ((inserted - main.begin()) == boundIndex);
		}
		prevJacobsthal = currJacobsthal;
		insertedNums += jacobsthalDiff;
		offset = 0;
	}

	for (long unsigned int i = 0; i < pend.size(); i++)
	{
		std::vector< vector_int_it>::iterator	currPend = pend.begin() + i;
		std::vector< vector_int_it>::iterator	currBound = advanceIter(main.begin(), main.size() - pend.size() + i + hasStraggler);
		std::vector< vector_int_it>::iterator	idx = std::lower_bound(main.begin(), currBound, *currPend, compare<vector_int_it>);
		main.insert(idx, *currPend);
	}

	vector_int	copy;
	copy.reserve(vec_container.size());
	for (std::vector< vector_int_it>::iterator it = main.begin(); it != main.end(); it++)
	{
		for (int i = 0; i < unitSize; i++)
		{
			vector_int_it	unitStart = *it;
			std::advance(unitStart, -unitSize + i + 1);
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


void merge_insert(int ac, char **av) {
    vector_int vectorContainer;
    std::deque<int> dequeContainer;
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
                dequeContainer.push_back(value);
                vectorContainer.push_back(value);
        } else {
            std::cerr << "Invalid value: `" << str << "`" <<  std::endl;
            exit (1);
        }

    }
    std::cout << "Before:" << std::endl;
    std::for_each(vectorContainer.begin(), vectorContainer.end(), printo);
    std::cout << std::endl;


    mergeinsertionsortV(vectorContainer, 1);


    std::cout << "After:" << std::endl;
    std::for_each(vectorContainer.begin(), vectorContainer.end(), printo);
    std::cout << std::endl;
}

